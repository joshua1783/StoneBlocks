#include <DxLib.h>
#include "Common.h"
#include "Sys_Input.h"
#include "Sys_DataLoader.h"
#include "Game_Field.h"
#include "Gama_ActiveBlock.h"

//CFieldのコンストラクタ
CField::CField() : flag_Grid(false), lineUpTime(0), topDrowLineNow(0), bufferBlocks(), input(0), data(0), newLineBlocks(FIELD_WIDTH, -1) {

	//インスタンス取得
	input = CInput::GetInstance();
	data  = CDataLoader::GetInstance();

	fieldBlocks.reserve(VECTOR_CAPACITY_NUM);
	fieldBlocks = vector<vector<short>>(FIELD_HEIGHT, vector<short>(FIELD_WIDTH, -1));
	MakeNewLine();
}

//CFieldのデストラクタ
CField::~CField(){
}

//CFieldのインスタンスのポインタを返す関数
CField* CField::GetInstance() {

	//インスタンス生成
	static CField instance;

	return &instance;
}

//フィールド関係の状態推移関数
void CField::UpData(int* status,int timeNow) {

	lineUpTime += timeNow;
	
	//Tabキーが押されたらグリッド線表示のフラグ反転
	if (input->CheckKey(KEY_INPUT_TAB) == 1)
		flag_Grid = !flag_Grid;

	//ゲーム状態がフィールドブロックのライン上昇且つ猶予時間に達しているならばラインを上昇
	//そうでなければ次のゲーム状態に移行
	if (*status == GS_FieldLineUp && lineUpTime >= LINEUP_TIME_NUM) {
		LineUp();
		lineUpTime = 0;
	}else {
		*status = GS_CheckFieldBlock;
	}

	if (*status == GS_CheckFieldBlock)
		*status = CheckFieldBlocks();
	if (*status == GS_DropBlocks)
		*status = GS_ActiveBlockMove;
}

//フィールド関係の描画関数
void CField::Draw() {

	//フィールドの黒枠描画
	DrawBox(MARGIN_WIDTH, MARGIN_HEIGHT, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, FIELD_HEIGHT * BLOCK_SIZE + MARGIN_HEIGHT, CR_Black, TRUE);
	DrawBox(MARGIN_WIDTH, MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 10, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, BLOCK_SIZE + MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 10, CR_Black, TRUE);
	//flag_Gridがtrueならばグリッド線描画
	if (flag_Grid == true) {
		for (int i = 1; i < FIELD_HEIGHT; i++) {
			DrawLine(MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, CR_White);
		}
		for (int j = 1; j < FIELD_WIDTH; j++) {
			DrawLine(BLOCK_SIZE * j + MARGIN_WIDTH, MARGIN_HEIGHT, BLOCK_SIZE * j + MARGIN_WIDTH, FIELD_HEIGHT * BLOCK_SIZE + MARGIN_HEIGHT, CR_White);
		}
	}
	//fieldBlocksの各要素に対応した色のブロック描画
	for (int i = 0; i < FIELD_HEIGHT; i++){
		for (int j = 0; j < FIELD_WIDTH; j++){
			//フィールドのブロック描画
			switch (fieldBlocks[i + topDrowLineNow][j]){
				case BlockType_Red:
					DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, data->GetImg_BlockRed(), TRUE);
					break;
				case BlockType_Blue:
					DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, data->GetImg_BlockBlue(), TRUE);
					break;
				case BlockType_Green:
					DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, data->GetImg_BlockGreen(), TRUE);
					break;
				case BlockType_Yellow:
					DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, data->GetImg_BlockYellow(), TRUE);
					break;
				default:
					break;
			}
			//次のラインのブロック描画
			switch (newLineBlocks[j]) {
			case BlockType_Red:
				DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 10, data->GetImg_BlockRed(), TRUE);
				break;
			case BlockType_Blue:
				DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 10, data->GetImg_BlockBlue(), TRUE);
				break;
			case BlockType_Green:
				DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 10, data->GetImg_BlockGreen(), TRUE);
				break;
			case BlockType_Yellow:
				DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 10, data->GetImg_BlockYellow(), TRUE);
				break;
			default:
				break;
			}
		}
	}
}

//引数座標のフィールド上ブロックの種類を返す関数
int CField::GetFieldBlockType(int x, int y) {

	return fieldBlocks[y + topDrowLineNow][x];
}

//落下したアクティブブロックをフィールドブロックに変更する関数
void CField::Active2FieldBlock(int i, int j, short blockType) {

	fieldBlocks[j + topDrowLineNow][i] = blockType;
}

//次に出現するラインのブロックを作成する関数
void CField::MakeNewLine() {
		
	for (int i = 0; i < FIELD_WIDTH; i++) {
		newLineBlocks[i] = GetRand(BlockType_Num - 1);
	}
}

//フィールドブロックのラインを増やす関数
void CField::LineUp() {

	//フィールドブロックの末尾に新しいラインを追加
	fieldBlocks.emplace_back(newLineBlocks);

	//フィールドブロックの現在の描画する最大ラインをずらす
	topDrowLineNow++;

	//次の新しいラインブロックを作成
	MakeNewLine();
}

//フィールドブロックに消えるブロックがないかをチェックする関数
int CField::CheckFieldBlocks() {

	bool flag_Vanish = false;

	//一時保存用データの初期化
	// 0:空白または消えないブロック
	// 1:消えるブロック
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int j = 0; j < FIELD_WIDTH; j++) {
			bufferBlocks[i][j] = 0;
		}
	}

	for (int i = 0; i < FIELD_HEIGHT; i++){
		for (int j = 0; j < FIELD_WIDTH; j++) {

			if (GetFieldBlockType(j, i) == -1)	continue;
			CountSameBlock(j, i);

		}
	}

	for (int i = 0; i < FIELD_HEIGHT; i++){
		for (int j = 0; j < FIELD_WIDTH; j++){
			if (bufferBlocks[i][j] == 1){
				flag_Vanish = true;
				fieldBlocks[i + topDrowLineNow][j] = -1;
			}
		}
	}
	
	if (flag_Vanish == true) {
		return GS_DropBlocks;
	}else {
		return GS_ActiveBlockMove;
	}
}

//同じ色のブロックを数える関数
void CField::CountSameBlock(int x, int y) {

	int color = GetFieldBlockType(x, y);
	int count = 0;

	for (int i = 0; x + i < FIELD_WIDTH && color == GetFieldBlockType(x + i, y); i++, count++){}
	if (count >= VANISH_MIN_MUN) {
		for (int j = 0; j < count; j++) {
			bufferBlocks[y][x + j] = 1;
		}
	}

	count = 0;
	for (int i = 0; y + i < FIELD_HEIGHT && color == GetFieldBlockType(x, y + i); i++, count++) {}
	if (count >= VANISH_MIN_MUN) {
		for (int j = 0; j < count; j++) {
			bufferBlocks[y + j][x] = 1;
		}
	}
	
	count = 0;
	for (int i = 0; x + i < FIELD_WIDTH && y + i < FIELD_HEIGHT && color == GetFieldBlockType(x + i, y + i); i++, count++) {}
	if (count >= VANISH_MIN_MUN) {
		for (int j = 0; j < count; j++) {
			bufferBlocks[y + j][x + j] = 1;
		}
	}
	
	count = 0;
	for (int i = 0; x - i >= 0 && y + i < FIELD_HEIGHT && color == GetFieldBlockType(x - i, y + i); i++, count++) {}
	if (count >= VANISH_MIN_MUN) {
		for (int j = 0; j < count; j++) {
			bufferBlocks[y + j][x - j] = 1;
		}
	}
}


//下に空白ができたブロックを落とす関数
void CField::DropBlocks() {

}