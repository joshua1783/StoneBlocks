#include <DxLib.h>
#include "Common.h"
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

	DrawBackgraound();
}

void CGame::DrawBackgraound() {

	DrawGraph(0, 0, data->GetImg_Background_Game(), FALSE);
	DrawBox(40, 40, 520, 760, CR_Black,TRUE);

	for (int i = 1; i < 10; i++) {
		DrawLine(i * 48 + 40, 40, i * 48 + 40, 760, CR_White);
	}
	for (int j = 1; j < 15; j++) {
		DrawLine(40, j * 48 + 40, 520, j * 48 + 40, CR_White);
	}
	
}
