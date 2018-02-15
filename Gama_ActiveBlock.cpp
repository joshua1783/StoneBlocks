#include <DxLib.h>
#include <vector>
#include <iterator>
#include "Common.h"
#include "Game_Field.h"
#include "Gama_ActiveBlock.h"
#include "Sys_Input.h"
#include "Sys_DataLoader.h"

//CBlock�̃R���X�g���N
CActiveBlock::CActiveBlock(): input(0), data(0), field(0), downTime(0), waitTime(0), flag_BlockStop(false){

	input = CInput::GetInstance();
	data = CDataLoader::GetInstance();
	field = CField::GetInstance();

	activeBlock = vector<vector<short>>(ACTIVEBLOCK_HEIGHT, vector<short>(ACTIVEBLOCK_WIDTH, -1));
	MakeNewBlock();
}

//CBllock�̃f�X�g���N�^
CActiveBlock::~CActiveBlock(){

}

//CBlock�̃C���X�^���X�̃|�C���^��Ԃ��֐�
CActiveBlock* CActiveBlock::GetInstance() {

	//�C���X�^���X����
	static CActiveBlock instance;

	return &instance;
}

//�A�N�e�B�u�u���b�N�֌W�̏�Ԑ��ڊ֐�
void CActiveBlock::UpDate(int* status, int timeNow) {
	if (*status == GS_NewActiveBlock) {
		MakeNewBlock();
		waitTime = 0;
		flag_BlockStop = false;
		*status = GS_ActiveBlockMove;
	}else if (*status == GS_ActiveBlockMove) {
		MoveBlock(timeNow);
		//�u���b�N�������s�̏ꍇ,�A�N�e�B�u�u���b�N���t�B�[���h�u���b�N�̑Ή��ʒu�ɕϊ�
		if (waitTime >= WAIT_TIME_NUM) {
			for (int i = 0; i < ACTIVEBLOCK_HEIGHT; i++) {
				for (int j = 0; j < ACTIVEBLOCK_WIDTH; j++) {
					field->Active2FieldBlock(pos.x, pos.y + i, activeBlock[i][j]);
					activeBlock[i][j] = -1;
				}
			}
			*status = GS_CheckFieldBlock;
		}

	}

}

//�A�N�e�B�u�u���b�N�֌W�̕`��֐�
void CActiveBlock::Draw() {

	//activeBlock�̊e�v�f�ɑΉ������F�̃u���b�N�`��
	for (int i = 0; i < ACTIVEBLOCK_HEIGHT; i++) {
		for (int j = 0; j < ACTIVEBLOCK_WIDTH; j++) {
			//�A�N�e�B�u�u���b�N�̕`��
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
	}
}
//�A�N�e�B�u�u���b�N�ړ��֌W�̊֐�
void CActiveBlock::MoveBlock(int timeNow) {
	
	Pos movePos;
	movePos.x = 0;
	movePos.y = 0;
	downTime += timeNow;

	//�A�N�e�B�u�u���b�N��]
	if (input->CheckKey(KEY_INPUT_W) == 1 || input->CheckKey(KEY_INPUT_UP) == 1) {
		ChangeBlock();
	}
	//x���W�ړ�����
	if ((input->CheckKey(KEY_INPUT_A) % 8) == 1 || (input->CheckKey(KEY_INPUT_LEFT) % 8) == 1) {
		movePos.x = -1;
	}else if ((input->CheckKey(KEY_INPUT_D) % 8) == 1 || (input->CheckKey(KEY_INPUT_RIGHT) % 8) == 1) {
		movePos.x = 1;
	}
	//y���W�ړ�����
	if ((input->CheckKey(KEY_INPUT_S) % 8) == 1 || (input->CheckKey(KEY_INPUT_DOWN) % 8) == 1) {
		movePos.y = 1;
		downTime = 0;
		flag_BlockStop = true;
	}else if (downTime >= DOWN_TIME_NUM) {
		movePos.y = 1;
		downTime = 0;
	}

	pos.x = CheckHitBlock_X(movePos.x) ? pos.x : pos.x + movePos.x;
	pos.y = CheckHitBlock_Y() ? pos.y : pos.y + movePos.y;

	if (CheckHitBlock_Y() && flag_BlockStop == true) {
		waitTime = WAIT_TIME_NUM;
	}else if (CheckHitBlock_Y() && flag_BlockStop == false) {
		waitTime += timeNow;
	}	
}

//�A�N�e�B�u�u���b�N�̐F�̏��Ԃ�ς���֐�
void CActiveBlock::ChangeBlock() {

	iter_swap(activeBlock[0].begin(),activeBlock[ACTIVEBLOCK_HEIGHT - 1].begin());
}

//�V�����u���b�N���쐬����֐�
void CActiveBlock::MakeNewBlock() {

	//�ʒu��������
	pos.x = FIELD_WIDTH / 2;
	pos.y = 0;

	for (int i = 0; i < ACTIVEBLOCK_HEIGHT; i++){
		for (int j = 0; j < ACTIVEBLOCK_WIDTH; j++){

			activeBlock[i][j] = GetRand(BlockType_Num - 1);
		}
	}
}

//�A�N�e�B�u�u���b�N�ƕǂ�t�B�[���h�u���b�N�Ƃ̓����蔻��֐�
bool CActiveBlock::CheckHitBlock_X(int x) {

	//�A�N�e�B�u�u���b�N���ǂɏՓ˂��Ă����true
	if (pos.x == 0 && x == -1) {
		return true;
	}else if (pos.x == FIELD_WIDTH - 1 && x == 1) {
		return true;
	}

	//�A�N�e�B�u�u���b�N���t�B�[���h�u���b�N�ƏՓ˂��Ă����true
	if (field->GetFieldBlockType(pos.x + x, pos.y + ACTIVEBLOCK_HEIGHT - 1) != -1) {
		return true;
	}

	return false;
}

bool CActiveBlock::CheckHitBlock_Y() {

	//�A�N�e�B�u�u���b�N���ǂɏՓ˂��Ă����true
	if (pos.y == FIELD_HEIGHT - ACTIVEBLOCK_HEIGHT) {
		return true;
	}

	//�A�N�e�B�u�u���b�N���t�B�[���h�u���b�N�ƏՓ˂��Ă����true
	if (field->GetFieldBlockType(pos.x, pos.y + ACTIVEBLOCK_HEIGHT) != -1) {
		return true;
	}

	waitTime = 0;
	flag_BlockStop = false;

	return false;
}