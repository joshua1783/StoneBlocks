#include <DxLib.h>
#include "Common.h"
#include "Sys_Input.h"
#include "Sys_DataLoader.h"
#include "Game_Field.h"
#include "Gama_ActiveBlock.h"

//CField�̃R���X�g���N�^
CField::CField() : flag_Grid(false), lineUpTime(0), topDrowLineNow(0), bufferBlocks(), input(0), data(0), newLineBlocks(FIELD_WIDTH, -1) {

	//�C���X�^���X�擾
	input = CInput::GetInstance();
	data  = CDataLoader::GetInstance();

	fieldBlocks.reserve(VECTOR_CAPACITY_NUM);
	fieldBlocks = vector<vector<short>>(FIELD_HEIGHT, vector<short>(FIELD_WIDTH, -1));
	MakeNewLine();
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

//�t�B�[���h�֌W�̏�Ԑ��ڊ֐�
void CField::UpData(int* status,int timeNow) {

	lineUpTime += timeNow;
	
	//Tab�L�[�������ꂽ��O���b�h���\���̃t���O���]
	if (input->CheckKey(KEY_INPUT_TAB) == 1)
		flag_Grid = !flag_Grid;

	//�Q�[����Ԃ��t�B�[���h�u���b�N�̃��C���㏸���P�\���ԂɒB���Ă���Ȃ�΃��C�����㏸
	//�����łȂ���Ύ��̃Q�[����ԂɈڍs
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

//�t�B�[���h�֌W�̕`��֐�
void CField::Draw() {

	//�t�B�[���h�̍��g�`��
	DrawBox(MARGIN_WIDTH, MARGIN_HEIGHT, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, FIELD_HEIGHT * BLOCK_SIZE + MARGIN_HEIGHT, CR_Black, TRUE);
	DrawBox(MARGIN_WIDTH, MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 10, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, BLOCK_SIZE + MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 10, CR_Black, TRUE);
	//flag_Grid��true�Ȃ�΃O���b�h���`��
	if (flag_Grid == true) {
		for (int i = 1; i < FIELD_HEIGHT; i++) {
			DrawLine(MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, CR_White);
		}
		for (int j = 1; j < FIELD_WIDTH; j++) {
			DrawLine(BLOCK_SIZE * j + MARGIN_WIDTH, MARGIN_HEIGHT, BLOCK_SIZE * j + MARGIN_WIDTH, FIELD_HEIGHT * BLOCK_SIZE + MARGIN_HEIGHT, CR_White);
		}
	}
	//fieldBlocks�̊e�v�f�ɑΉ������F�̃u���b�N�`��
	for (int i = 0; i < FIELD_HEIGHT; i++){
		for (int j = 0; j < FIELD_WIDTH; j++){
			//�t�B�[���h�̃u���b�N�`��
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
			//���̃��C���̃u���b�N�`��
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

//�������W�̃t�B�[���h��u���b�N�̎�ނ�Ԃ��֐�
int CField::GetFieldBlockType(int x, int y) {

	return fieldBlocks[y + topDrowLineNow][x];
}

//���������A�N�e�B�u�u���b�N���t�B�[���h�u���b�N�ɕύX����֐�
void CField::Active2FieldBlock(int i, int j, short blockType) {

	fieldBlocks[j + topDrowLineNow][i] = blockType;
}

//���ɏo�����郉�C���̃u���b�N���쐬����֐�
void CField::MakeNewLine() {
		
	for (int i = 0; i < FIELD_WIDTH; i++) {
		newLineBlocks[i] = GetRand(BlockType_Num - 1);
	}
}

//�t�B�[���h�u���b�N�̃��C���𑝂₷�֐�
void CField::LineUp() {

	//�t�B�[���h�u���b�N�̖����ɐV�������C����ǉ�
	fieldBlocks.emplace_back(newLineBlocks);

	//�t�B�[���h�u���b�N�̌��݂̕`�悷��ő僉�C�������炷
	topDrowLineNow++;

	//���̐V�������C���u���b�N���쐬
	MakeNewLine();
}

//�t�B�[���h�u���b�N�ɏ�����u���b�N���Ȃ������`�F�b�N����֐�
int CField::CheckFieldBlocks() {

	bool flag_Vanish = false;

	//�ꎞ�ۑ��p�f�[�^�̏�����
	// 0:�󔒂܂��͏����Ȃ��u���b�N
	// 1:������u���b�N
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

//�����F�̃u���b�N�𐔂���֐�
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


//���ɋ󔒂��ł����u���b�N�𗎂Ƃ��֐�
void CField::DropBlocks() {

}