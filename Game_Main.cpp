#include <DxLib.h>
#include "SceneBase.h"
#include "Game_Main.h"
#include "Sys_DataLoader.h"

//CGame�̃R���X�g���N�^
CGame::CGame(): data(0){

	//�C���X�^���X�擾
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

	return next;
}

//�Q�[���V�[���̕`��֐�
void CGame::Draw(CSceneMgr* sceneMgr) {

	DrawGraph(0, 0, data->GetImg_BackgroundGame(), FALSE);
}
