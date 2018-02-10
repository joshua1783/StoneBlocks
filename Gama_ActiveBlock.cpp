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
void CActiveBlock::UpDate() {

	MoveBlock();

	//�u���b�N�������s�̏ꍇ,�A�N�e�B�u�u���b�N���t�B�[���h�u���b�N�̑Ή��ʒu�ɕϊ�
	if (flag_BlockStop == true) {
		waitTime++;
		if (waitTime >= WAIT_TIME_NUM) {
			for (int i = 0; i < ACTIVEBLOCK_WIDTH; i++) {
				for (int j = 0; j < ACTIVEBLOCK_HEIGHT; j++) {
					field->Active2FieldBlock(pos.x, pos.y + j, activeBlock[j][i]);
				}
			}
			MakeNewBlock();
			waitTime = 0;
			flag_BlockStop = false;
		}
	}	
}

//�A�N�e�B�u�u���b�N�֌W�̕`��֐�
void CActiveBlock::Draw() {

	//activeBlock�̊e�v�f�ɑΉ������F�̃u���b�N�`��
	for (int i = 0; i < ACTIVEBLOCK_WIDTH; i++) {
		for (int j = 0; j < ACTIVEBLOCK_HEIGHT; j++) {
			//�A�N�e�B�u�u���b�N�̕`��
			switch (activeBlock[j][i]) {
				case BlockType_Red:
					DrawGraph(BLOCK_SIZE * (i + pos.x) + MARGIN_WIDTH, BLOCK_SIZE * (j + pos.y) + MARGIN_HEIGHT, data->GetImg_BlockRed(), TRUE);
					break;
				case BlockType_Blue:
					DrawGraph(BLOCK_SIZE * (i + pos.x) + MARGIN_WIDTH, BLOCK_SIZE * (j + pos.y) + MARGIN_HEIGHT, data->GetImg_BlockBlue(), TRUE);
					break;
				case BlockType_Green:
					DrawGraph(BLOCK_SIZE * (i + pos.x) + MARGIN_WIDTH, BLOCK_SIZE * (j + pos.y) + MARGIN_HEIGHT, data->GetImg_BlockGreen(), TRUE);
					break;
				case BlockType_Yellow:
					DrawGraph(BLOCK_SIZE * (i + pos.x) + MARGIN_WIDTH, BLOCK_SIZE * (j + pos.y) + MARGIN_HEIGHT, data->GetImg_BlockYellow(), TRUE);
					break;
				default:
					break;
			}
		}
	}
}
//�A�N�e�B�u�u���b�N�ړ��֌W�̊֐�
void CActiveBlock::MoveBlock() {
	
	Pos movePos;
	movePos.x = 0;
	movePos.y = 0;
	downTime++;

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
	}else if (downTime == DOWN_TIME_NUM) {
		movePos.y = 1;
		downTime = 0;
	}

	movePos = CheckHitBlock(movePos);

	pos.x += movePos.x;
	pos.y += movePos.y;
}

//�A�N�e�B�u�u���b�N�̐F�̏��Ԃ�ς���֐�
void CActiveBlock::ChangeBlock() {

	iter_swap(activeBlock[0].begin(),activeBlock[ACTIVEBLOCK_HEIGHT - 1].begin());
}

//�V�����u���b�N���쐬����֐�
void CActiveBlock::MakeNewBlock() {

	pos.x = FIELD_WIDTH / 2;
	pos.y = 0;

	for (int i = 0; i < ACTIVEBLOCK_WIDTH; i++){
		for (int j = 0; j < ACTIVEBLOCK_HEIGHT; j++){

			activeBlock[j][i] = GetRand(BlockType_Num - 1);
		}
	}
}

//�A�N�e�B�u�u���b�N�ƕǂ�t�B�[���h�u���b�N�Ƃ̓����蔻��֐�
Pos CActiveBlock::CheckHitBlock(Pos movePos) {

	//�A�N�e�B�u�u���b�N���ǂɏՓ˂��Ă���Έړ����Ȃ�
	if (pos.x == 0 && movePos.x == -1) {
		movePos.x = 0;
	}else if (pos.x == FIELD_WIDTH - 1 && movePos.x == 1) {
		movePos.x = 0;
	}
	if (pos.y == FIELD_HEIGHT - ACTIVEBLOCK_HEIGHT) {
		movePos.y = 0;
	}else {
		flag_BlockStop = false;
	}

	//�A�N�e�B�u�u���b�N���t�B�[���h�u���b�N�ƏՓ˂��Ă����true
	if (field->GetFieldBlockType(pos.x + movePos.x, pos.y + ACTIVEBLOCK_HEIGHT - 1) != -1) {
		movePos.x = 0;
	}
	if (field->GetFieldBlockType(pos.x, (pos.y + ACTIVEBLOCK_HEIGHT - 1) + movePos.y) != -1) {
		movePos.y = 0;
	}else {
		flag_BlockStop = false;
	}

	return movePos;
}