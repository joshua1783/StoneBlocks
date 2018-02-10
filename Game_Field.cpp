#include <DxLib.h>
#include "Common.h"
#include "Sys_Input.h"
#include "Sys_DataLoader.h"
#include "Game_Field.h"
#include "Gama_ActiveBlock.h"

//CFieldのコンストラクタ
CField::CField() : flag_Grid(false), input(0), data(0), newLineBlocks(FIELD_WIDTH, -1) {

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
void CField::UpData() {

	//Tabキーが押されたらグリッド線表示のフラグ反転
	if (input->CheckKey(KEY_INPUT_TAB) == 1)
		flag_Grid = !flag_Grid;
}

//フィールド関係の描画関数
void CField::Draw() {

	//フィールドの黒枠描画及びflag_Gridがtrueならばグリッド線描画
	DrawBox(MARGIN_WIDTH, MARGIN_HEIGHT, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, FIELD_HEIGHT * BLOCK_SIZE + MARGIN_HEIGHT, CR_Black, TRUE);
	DrawBox(MARGIN_WIDTH, MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 5, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, BLOCK_SIZE + MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 5, CR_Black, TRUE);
	if (flag_Grid == true) {
		for (int i = 1; i < FIELD_WIDTH; i++) {
			DrawLine(BLOCK_SIZE * i + MARGIN_WIDTH, MARGIN_HEIGHT,BLOCK_SIZE * i + MARGIN_WIDTH, FIELD_HEIGHT * BLOCK_SIZE + MARGIN_HEIGHT, CR_White);
		}
		for (int j = 1; j < FIELD_HEIGHT; j++) {
			DrawLine(MARGIN_WIDTH, BLOCK_SIZE * j + MARGIN_HEIGHT, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, BLOCK_SIZE * j + MARGIN_HEIGHT, CR_White);
		}
	}
	//fieldBlocksの各要素に対応した色のブロック描画
	for (int i = 0; i < FIELD_WIDTH; i++){
		for (int j = 0; j < FIELD_HEIGHT; j++){
			//フィールドのブロック描画
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
		//次のラインのブロック描画
		switch (newLineBlocks[i]) {
			case BlockType_Red:
				DrawGraph(BLOCK_SIZE * i + MARGIN_WIDTH, MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 5, data->GetImg_BlockRed(), TRUE);
				break;
			case BlockType_Blue:
				DrawGraph(BLOCK_SIZE * i + MARGIN_WIDTH, MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 5, data->GetImg_BlockBlue(), TRUE);
				break;
			case BlockType_Green:
				DrawGraph(BLOCK_SIZE * i + MARGIN_WIDTH, MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 5, data->GetImg_BlockGreen(), TRUE);
				break;
			case BlockType_Yellow:
				DrawGraph(BLOCK_SIZE * i + MARGIN_WIDTH, MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 5, data->GetImg_BlockYellow(), TRUE);
				break;
			default:
				break;
		}
	}
}

//引数座標のフィールド上ブロックの種類を返す関数
int CField::GetFieldBlockType(int x, int y) {

	return fieldBlocks[y][x];
}

//落下したアクティブブロックをフィールドブロックに変更する関数
void CField::Active2FieldBlock(int i, int j, short blockType) {

	fieldBlocks[j][i] = blockType;
}

//次に出現するラインのブロックを作成する関数
void CField::MakeNewLine() {
		
	for (int i = 0; i < FIELD_WIDTH; i++) {
		newLineBlocks[i] = GetRand(BlockType_Num - 1);
	}

}