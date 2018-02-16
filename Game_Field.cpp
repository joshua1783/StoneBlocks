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
	//フィールドブロック初期化
	fieldBlocks.reserve(VECTOR_CAPACITY_NUM);
	fieldBlocks = vector<vector<short>>(FIELD_HEIGHT, vector<short>(FIELD_WIDTH, -1));
	//次のライン生成
	MakeNewLine();
}

//CFieldのデストラクタ
CField::~CField(){
}

//CFieldのインスタンスのポインタを返す関数
CField* CField::GetInstance() {

	//インスタンス生成
	static CField *instance = new CField;

	return instance;
}

//フィールド関係の状態推移関数
void CField::UpData(int* status,int timeNow) {
		
	//Tabキーが押されたらグリッド線表示のフラグ反転
	if (input->CheckKey(KEY_INPUT_TAB) == 1)
		flag_Grid = !flag_Grid;

	if (*status == GS_ActiveBlockMove) {
		lineUpTime += timeNow;
	}else if (*status == GS_CheckFieldBlocks) {
		if (lineUpTime >= LINEUP_TIME_NUM) {
			LineUp();
			lineUpTime = 0;
		}
		CheckFieldBlocks();
		count = 0;
		*status = GS_VanishFieldBlocks;
	}else if (*status == GS_VanishFieldBlocks) {
		count += timeNow;
		if (count >= 300) {
			*status = VanishFieldBlocks();
			count = 0;
		}
	}else if (*status == GS_FallBlocks) {
		count += timeNow;
		if (count >= 500) {
			if (FallBlocks()) {
				*status = GS_FallBlocks;
			}
			else {
				*status = GS_CheckFieldBlocks;
			}
			count = 0;
		}
	}
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
void CField::Active2FieldBlock(int x, int y, short blockType) {

	fieldBlocks[y + topDrowLineNow][x] = blockType;
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
void CField::CheckFieldBlocks() {

	//一時保存用データの初期化
	// 0:空白または消えないブロック
	// 1:消えるブロック
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int j = 0; j < FIELD_WIDTH; j++) {
			bufferBlocks[i][j] = 0;
		}
	}
	//同色のブロックがつながっているかを探索
	for (int i = 0; i < FIELD_HEIGHT; i++){
		for (int j = 0; j < FIELD_WIDTH; j++) {
			//空白ならば次へ
			if (GetFieldBlockType(j, i) == -1)	continue;
			//同色ブロック探索関数へ
			CountSameBlock(j, i);
		}
	}
}

//同じ色のブロックを数える関数
void CField::CountSameBlock(int x, int y) {

	//探索元の色を保存
	int color = GetFieldBlockType(x, y);
	
	//左から右にかけて同色ブロックを探索,指定数以上なら該当ブロックに消去フラグを立てる
	int num = 0;
	for (int i = 0; x + i < FIELD_WIDTH && color == GetFieldBlockType(x + i, y); i++, num++){}
	if (num >= VANISH_MIN_MUN) {
		for (int j = 0; j < num; j++) {
			bufferBlocks[y][x + j] = 1;
		}
	}
	//上から下にかけて同色ブロックを探索,指定数以上なら該当ブロックに消去フラグを立てる
	num = 0;
	for (int i = 0; y + i < FIELD_HEIGHT && color == GetFieldBlockType(x, y + i); i++, num++) {}
	if (num >= VANISH_MIN_MUN) {
		for (int j = 0; j < num; j++) {
			bufferBlocks[y + j][x] = 1;
		}
	}
	//左上から右下にかけて同色ブロックを探索,指定数以上なら該当ブロックに消去フラグを立てる
	num = 0;
	for (int i = 0; x + i < FIELD_WIDTH && y + i < FIELD_HEIGHT && color == GetFieldBlockType(x + i, y + i); i++, num++) {}
	if (num >= VANISH_MIN_MUN) {
		for (int j = 0; j < num; j++) {
			bufferBlocks[y + j][x + j] = 1;
		}
	}
	//右上から左下にかけて同色ブロックを探索,指定数以上なら該当ブロックに消去フラグを立てる
	num = 0;
	for (int i = 0; x - i >= 0 && y + i < FIELD_HEIGHT && color == GetFieldBlockType(x - i, y + i); i++, num++) {}
	if (num >= VANISH_MIN_MUN) {
		for (int j = 0; j < num; j++) {
			bufferBlocks[y + j][x - j] = 1;
		}
	}
}

//消去フラグが経っているブロックを消す
int CField::VanishFieldBlocks() {
	
	bool flag_Vanish = false;
	
	//消去フラグが立っているブロックがあれば該当ブロックを消去
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int j = 0; j < FIELD_WIDTH; j++) {
			if (bufferBlocks[i][j] == 1) {
				flag_Vanish = true;
				fieldBlocks[i + topDrowLineNow][j] = -1;
			}
		}
	}
	//一つでも消えるブロックがあったならGS_FallBlocksに移動
	//そうでなければ次のアクティブブロックを生成
	if (flag_Vanish == true) {
		return GS_FallBlocks;
	}
	else {
		return GS_NewActiveBlock;
	}
}


//下に空白ができたブロックを落とす関数
bool CField::FallBlocks() {

	int line;
	bool flag_Fall = false;

	for (int j = 0; j < FIELD_WIDTH; j++) {
		for (int i = FIELD_HEIGHT -1; i >= 0; i--){
			if (GetFieldBlockType(j, i) == -1) {
				for (line = i - 1; line >= 0 && GetFieldBlockType(j, line) == -1; line--) {};
				if (line < 0) break;

				flag_Fall = true;
				for (line = i; line >= 0; line--){
					if (line - 1 >= 0) 
						fieldBlocks[line + topDrowLineNow][j] = fieldBlocks[(line - 1) + topDrowLineNow][j];
				}
			}
		}
	}
	
	return flag_Fall;
}