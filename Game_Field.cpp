#include <DxLib.h>
#include "Common.h"
#include "Sys_DataLoader.h"
#include "Game_Field.h"

//CFieldのコンストラクタ
CField::CField(): flag_Grid(false), data(0){

	data = CDataLoader::GetInstance();

	fieldBlocks.reserve(VECTOR_CAPACITY_NUM);
	fieldBlocks = vector<vector<short>>(FIELD_HEIGHT - FIRST_LINE_NUM, vector<short>(FIELD_WIDTH, -1));
	for (int i = 0; i < FIRST_LINE_NUM; i++) {
		fieldBlocks.emplace_back(makeNewLine());
	}
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

//フィールド関係の描画関数
void CField::Draw() {

	//フィールドの黒枠描画及びflag_Gridがtrueならばグリッド線描画
	DrawBox(MARGIN_WIDTH, MARGIN_HEIGHT, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, FIELD_HEIGHT * BLOCK_SIZE + MARGIN_HEIGHT, CR_Black, TRUE);
	if (flag_Grid == true) {
		for (int i = 1; i < FIELD_WIDTH; i++) {
			DrawLine(i * BLOCK_SIZE + MARGIN_WIDTH, MARGIN_HEIGHT, i * BLOCK_SIZE + MARGIN_WIDTH, FIELD_HEIGHT * BLOCK_SIZE + MARGIN_HEIGHT, CR_White);
		}
		for (int j = 1; j < FIELD_HEIGHT; j++) {
			DrawLine(MARGIN_WIDTH, j * BLOCK_SIZE + MARGIN_HEIGHT, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, j * BLOCK_SIZE + MARGIN_HEIGHT, CR_White);
		}
	}
	//fieldBlocksの各要素に対応した色のブロック描画
	for (int i = 0; i < FIELD_WIDTH; i++){
		for (int j = 0; j < FIELD_HEIGHT; j++){
			switch (fieldBlocks[j][i]){
				case BlockType_Red:
					DrawGraph(BLOCK_SIZE * i + MARGIN_WIDTH, BLOCK_SIZE * j + MARGIN_HEIGHT, data->GetImg_BlockRed(), TRUE);
					break;
				case BlockType_Blue:
					DrawGraph(BLOCK_SIZE * i + MARGIN_WIDTH, BLOCK_SIZE * j + MARGIN_HEIGHT, data->GetImg_BlockBlue(), TRUE);
					break;
				case BlockType_Green:
					DrawGraph(BLOCK_SIZE * i + MARGIN_WIDTH, BLOCK_SIZE * j + MARGIN_HEIGHT, data->GetImg_BlockGreen(), TRUE);
					break;
				case BlockType_Yellow:
					DrawGraph(BLOCK_SIZE * i + MARGIN_WIDTH, BLOCK_SIZE * j + MARGIN_HEIGHT, data->GetImg_BlockYellow(), TRUE);
					break;
				default:
					break;
			}
		}

	}
}

vector<short> CField::makeNewLine() {

	vector<short> newLine(FIELD_WIDTH);

	for (int i = 0; i < FIELD_WIDTH; i++) {
		newLine[i] = GetRand(BlockType_Num - 1);
	}

	return newLine;
}