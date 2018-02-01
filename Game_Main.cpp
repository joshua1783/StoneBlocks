#include <DxLib.h>
#include "Common.h"
#include "SceneBase.h"
#include "Game_Main.h"
#include "Game_Field.h"
#include "Sys_Input.h"
#include "Sys_DataLoader.h"

//CGame�̃R���X�g���N�^
CGame::CGame(): input(0), data(0), flag_Grid(false){

	//�C���X�^���X�擾
	input = CInput::GetInstance();
	data = CDataLoader::GetInstance();

	//�f�ޓǂݍ���
	data->Load();

}

//CGame�̃f�X�g���N�^
CGame::~CGame(){
}

//�Q�[���V�[���̏�Ԑ��ڊ֐�
CSceneBase* CGame::Updata(CSceneMgr* sceneMgr) {

	//���̃V�[�������݂̃V�[��(�Q�[���V�[��)�ɐݒ�
	CSceneBase* next = this;

	//Tab�L�[�������ꂽ��O���b�h���\���̃t���O���]
	if (input->CheckKey(KEY_INPUT_TAB) == 1)
		flag_Grid = !flag_Grid;

	return next;
}

//�Q�[���V�[���̕`��֐�
void CGame::Draw(CSceneMgr* sceneMgr) {

	DrawBackgraound();
}

//�w�i�̕`��֐�
void CGame::DrawBackgraound() {

	DrawGraph(0, 0, data->GetImg_Background_Game(), FALSE);
	DrawBox(MARGIN_WIDTH, MARGIN_HEIGHT, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, FIELD_HEIGHT * BLOCK_SIZE + MARGIN_HEIGHT, CR_Black,TRUE);
	//�t���O��true�Ȃ�΃O���b�h���`��
	if (flag_Grid == true) {
		for (int i = 1; i < FIELD_WIDTH; i++) {
			DrawLine(i * BLOCK_SIZE + MARGIN_WIDTH, MARGIN_HEIGHT, i * BLOCK_SIZE + MARGIN_WIDTH, FIELD_HEIGHT * BLOCK_SIZE + MARGIN_HEIGHT, CR_White);
		}
		for (int j = 1; j < FIELD_HEIGHT; j++) {
			DrawLine(MARGIN_WIDTH, j * BLOCK_SIZE + MARGIN_HEIGHT, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, j * BLOCK_SIZE + MARGIN_HEIGHT, CR_White);
		}
	}	
}
