#include <DxLib.h>
#include <vector>
#include <iterator>
#include "Common.h"
#include "Sys_Input.h"
#include "Sys_Font.h"
#include "Sys_DataLoader.h"
#include "Game_Score.h"
#include "Game_Field.h"
#include "Gama_ActiveBlock.h"

//CBlockのコンストラク
CActiveBlock::CActiveBlock(): input(0), font(0), data(0), field(0), score(0), nextBlock(){

	//インスタンス取得
	input = CInput::GetInstance();
	font = CFontHandle::GetInstance();
	data = CDataLoader::GetInstance();
	score = CScore::GetInstance();
	field = CField::GetInstance();	
}

//CBlockのインスタンスのポインタを返す関数
CActiveBlock* CActiveBlock::GetInstance() {

	//インスタンス生成
	static CActiveBlock *instance = new CActiveBlock;

	return instance;
}

//アクティブブロック関係の状態推移関数
void CActiveBlock::UpDate(int* status, int timeNow) {
	
	//新規アクティブブロック作成状態
	if (*status == GS_NewActiveBlock) {
		MakeNewBlock();
		waitTime = 0;
		flag_BlockStop = false;
		*status = GS_ActiveBlockMove;
	}
	//アクティブブロック操作状態
	else if (*status == GS_ActiveBlockMove) {
		//アクティブブロックの移動
		MoveBlock(timeNow);
		//ブロックが落下不可の場合,アクティブブロックをフィールドブロックの対応位置に変換
		if (waitTime >= WAIT_TIME_NUM) {
			for (int i = 0; i < ACTIVEBLOCK_HEIGHT; i++) {
				for (int j = 0; j < ACTIVEBLOCK_WIDTH; j++) {
					field->Active2FieldBlock(pos.x, pos.y + i, activeBlock[i][j]);
					activeBlock[i][j] = -1;
				}
			}
			//フィールドブロックチェック状態に移行
			*status = GS_CheckFieldBlocks;
		}
	}
}

//アクティブブロック関係の描画関数
void CActiveBlock::Draw() {
	
	//次のブロックを描画するための枠の描画
	DrawBox(FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH * 2, MARGIN_HEIGHT, SCREEN_WIDTH - MARGIN_WIDTH, MARGIN_HEIGHT + 200, CR_Black, TRUE);
	DrawStringToHandle(FIELD_WIDTH * BLOCK_SIZE + 140, MARGIN_HEIGHT + 10, "Next", CR_White, font->GetFont_M());
	//activeBlockの各要素に対応した色のブロック描画
	for (int i = 0; i < ACTIVEBLOCK_HEIGHT; i++) {
		for (int j = 0; j < ACTIVEBLOCK_WIDTH; j++) {
			//アクティブブロックの描画(枠外は描画しない)
			if (BLOCK_SIZE * (i + pos.y) >= 0) {
				switch (activeBlock[i][j]) {
				case BlockType_Red:
					DrawGraph(BLOCK_SIZE * (j + pos.x) + MARGIN_WIDTH, BLOCK_SIZE * (i + pos.y) + MARGIN_HEIGHT, data->GetImg_BlockRed(), TRUE);
					break;
				case BlockType_Blue:
					DrawGraph(BLOCK_SIZE * (j + pos.x) + MARGIN_WIDTH, BLOCK_SIZE * (i + pos.y) + MARGIN_HEIGHT, data->GetImg_BlockBlue(), TRUE);
					break;
				case BlockType_Green:
					DrawGraph(BLOCK_SIZE * (j + pos.x) + MARGIN_WIDTH, BLOCK_SIZE * (i + pos.y) + MARGIN_HEIGHT, data->GetImg_BlockGreen(), TRUE);
					break;
				case BlockType_Yellow:
					DrawGraph(BLOCK_SIZE * (j + pos.x) + MARGIN_WIDTH, BLOCK_SIZE * (i + pos.y) + MARGIN_HEIGHT, data->GetImg_BlockYellow(), TRUE);
					break;
				default:
					break;
				}
			}
			//次のブロックを描画
			switch (nextBlock[i][j]){
			case BlockType_Red:
				DrawGraph(BLOCK_SIZE * j + NEXTBLOCK_X, BLOCK_SIZE * i + NEXTBLOCK_Y, data->GetImg_BlockRed(), TRUE);
				break;
			case BlockType_Blue:
				DrawGraph(BLOCK_SIZE * j + NEXTBLOCK_X, BLOCK_SIZE * i + NEXTBLOCK_Y, data->GetImg_BlockBlue(), TRUE);
				break;
			case BlockType_Green:
				DrawGraph(BLOCK_SIZE * j + NEXTBLOCK_X, BLOCK_SIZE * i + NEXTBLOCK_Y, data->GetImg_BlockGreen(), TRUE);
				break;
			case BlockType_Yellow:
				DrawGraph(BLOCK_SIZE * j + NEXTBLOCK_X, BLOCK_SIZE * i + NEXTBLOCK_Y, data->GetImg_BlockYellow(), TRUE);
				break;
			default:
				break;
			}
		}
	}
}

//ゲーム開始時の初期化を行う関数
void CActiveBlock::SetUp() {
	downTime = 0;			//落下猶予時間初期化
	waitTime = 0;			//固定猶予時間初期化
	flag_BlockStop = false;	//ブロック停止フラグ初期化
	//アクティブブロック初期化
	activeBlock = vector<vector<short>>(ACTIVEBLOCK_HEIGHT, vector<short>(ACTIVEBLOCK_WIDTH, -1));
	MakeNewBlock();
}

//アクティブブロック移動関係の関数
void CActiveBlock::MoveBlock(int timeNow) {
	
	Pos movePos;
	//移動量の初期化及び落下猶予時間を加算
	movePos.x = 0;
	movePos.y = 0;
	downTime += timeNow;

	//アクティブブロック回転
	if (input->CheckKey(KEY_INPUT_W) == 1 || input->CheckKey(KEY_INPUT_UP) == 1) {
		ChangeBlock();
	}
	//x座標移動入力
	if ((input->CheckKey(KEY_INPUT_A) % 8) == 1 || (input->CheckKey(KEY_INPUT_LEFT) % 8) == 1) {
		PlaySoundMem(data->GetSe_Move(), DX_PLAYTYPE_BACK);
		movePos.x = -1;
	}else if ((input->CheckKey(KEY_INPUT_D) % 8) == 1 || (input->CheckKey(KEY_INPUT_RIGHT) % 8) == 1) {
		PlaySoundMem(data->GetSe_Move(), DX_PLAYTYPE_BACK);
		movePos.x = 1;
	}
	//y座標移動入力
	if ((input->CheckKey(KEY_INPUT_S) % 8) == 1 || (input->CheckKey(KEY_INPUT_DOWN) % 8) == 1) {
		movePos.y = 1;
		downTime = 0;
		flag_BlockStop = true;
		//スコア加算
		score->ScoreAdd_Move();
	}else if (downTime >= DOWN_TIME_NUM) {
		movePos.y = 1;
		downTime = 0;
	}

	//移動先に壁や他のブロックがなければ移動量を加算
	pos.x = CheckHitBlock_X(movePos.x) ? pos.x : pos.x + movePos.x;
	pos.y = CheckHitBlock_Y()		   ? pos.y : pos.y + movePos.y;

	//ブロックが下に落ちれないときにした入力があった場合即固定
	//そうでなければ固定猶予時間を加算
	if (CheckHitBlock_Y() && flag_BlockStop == true) {
		waitTime = WAIT_TIME_NUM;
	}else if (CheckHitBlock_Y() && flag_BlockStop == false) {
		waitTime += timeNow;
	}	
}

//アクティブブロックの色の順番を変える関数
void CActiveBlock::ChangeBlock() {
	iter_swap(activeBlock[0].begin(),activeBlock[ACTIVEBLOCK_HEIGHT - 1].begin());
}

//新しいブロックを作成する関数
void CActiveBlock::MakeNewBlock() {

	//位置を初期化
	pos.x = FIELD_WIDTH / 2;
	pos.y = -1;
	//次のブロックだったものをアクティブブロックに代入
	for (int i = 0; i < ACTIVEBLOCK_HEIGHT; i++) {
		for (int j = 0; j < ACTIVEBLOCK_WIDTH; j++) {
			activeBlock[i][j] = nextBlock[i][j];
		}
	}
	//次のネクストブロックにランダムに色を格納
	for (int i = 0; i < ACTIVEBLOCK_HEIGHT; i++){
		for (int j = 0; j < ACTIVEBLOCK_WIDTH; j++){
			nextBlock[i][j] = GetRand(BlockType_Num - 1);
		}
	}
}

//アクティブブロックと壁やフィールドブロックとの当たり判定関数
bool CActiveBlock::CheckHitBlock_X(int x) {

	//アクティブブロックが壁に衝突していればtrue
	if (pos.x == 0 && x == -1) {
		return true;
	}else if (pos.x == FIELD_WIDTH - 1 && x == 1) {
		return true;
	}

	//アクティブブロックがフィールドブロックと衝突していればtrue
	if (field->GetFieldBlockType(pos.x + x, pos.y + ACTIVEBLOCK_HEIGHT - 1) != -1) {
		return true;
	}

	return false;
}

bool CActiveBlock::CheckHitBlock_Y() {

	//アクティブブロックが壁に衝突していればtrue
	if (pos.y == FIELD_HEIGHT - ACTIVEBLOCK_HEIGHT) {
		return true;
	}

	//アクティブブロックがフィールドブロックと衝突していればtrue
	if (field->GetFieldBlockType(pos.x, pos.y + ACTIVEBLOCK_HEIGHT) != -1) {
		return true;
	}
	//ここまでくると移動先に障害物なし(移動可)
	waitTime = 0;
	flag_BlockStop = false;

	return false;
}