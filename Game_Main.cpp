#include <DxLib.h>
#include "Common.h"
#include "SceneBase.h"
#include "Game_Main.h"
#include "Game_Field.h"
#include "Gama_ActiveBlock.h"
#include "Sys_Input.h"
#include "Sys_DataLoader.h"

//CGame�̃R���X�g���N�^
CGame::CGame(): input(0), field(0), block(0), data(0){

	//�C���X�^���X�擾
	input = CInput::GetInstance();
	field = CField::GetInstance();
	block = CActiveBlock::GetInstance();
	data  = CDataLoader::GetInstance();

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
	field->UpData();
	block->UpDate();
	
	return next;
}

//�Q�[���V�[���S�̂̕`��֐�
void CGame::Draw(CSceneMgr* sceneMgr) {

	DrawGraph(0, 0, data->GetImg_Background_Game(), FALSE);
	field->Draw();
	block->Draw();
}

