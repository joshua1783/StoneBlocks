#include <DxLib.h>
#include "Common.h"
#include "SceneBase.h"
#include "Game_Main.h"
#include "Game_Field.h"
#include "Sys_Input.h"
#include "Sys_DataLoader.h"

//CGame�̃R���X�g���N�^
CGame::CGame(): input(0), field(0), data(0){

	//�C���X�^���X�擾
	input = CInput::GetInstance();
	field = CField::GetInstance();
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
		field->flag_Grid = !field->flag_Grid;

	return next;
}

//�Q�[���V�[���S�̂̕`��֐�
void CGame::Draw(CSceneMgr* sceneMgr) {

	DrawGraph(0, 0, data->GetImg_Background_Game(), FALSE);
	field->Draw();
}

