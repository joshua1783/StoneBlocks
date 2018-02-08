#include <DxLib.h>
#include "Common.h"
#include "Sys_DataLoader.h"
#include "Game_Field.h"

//CField�̃R���X�g���N�^
CField::CField(): flag_Grid(false), data(0){

	data = CDataLoader::GetInstance();

	fieldBlocks.reserve(VECTOR_CAPACITY_NUM);
	fieldBlocks = vector<vector<short>>(FIELD_HEIGHT - FIRST_LINE_NUM, vector<short>(FIELD_WIDTH, -1));
	for (int i = 0; i < FIRST_LINE_NUM; i++) {
		fieldBlocks.emplace_back(makeNewLine());
	}
}

//CField�̃f�X�g���N�^
CField::~CField(){
}

//CField�̃C���X�^���X�̃|�C���^��Ԃ��֐�
CField* CField::GetInstance() {

	//�C���X�^���X����
	static CField instance;

	return &instance;
}

//�t�B�[���h�֌W�̕`��֐�
void CField::Draw() {

	//�t�B�[���h�̍��g�`��y��flag_Grid��true�Ȃ�΃O���b�h���`��
	DrawBox(MARGIN_WIDTH, MARGIN_HEIGHT, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, FIELD_HEIGHT * BLOCK_SIZE + MARGIN_HEIGHT, CR_Black, TRUE);
	if (flag_Grid == true) {
		for (int i = 1; i < FIELD_WIDTH; i++) {
			DrawLine(i * BLOCK_SIZE + MARGIN_WIDTH, MARGIN_HEIGHT, i * BLOCK_SIZE + MARGIN_WIDTH, FIELD_HEIGHT * BLOCK_SIZE + MARGIN_HEIGHT, CR_White);
		}
		for (int j = 1; j < FIELD_HEIGHT; j++) {
			DrawLine(MARGIN_WIDTH, j * BLOCK_SIZE + MARGIN_HEIGHT, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, j * BLOCK_SIZE + MARGIN_HEIGHT, CR_White);
		}
	}
	//fieldBlocks�̊e�v�f�ɑΉ������F�̃u���b�N�`��
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