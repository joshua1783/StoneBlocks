#include "SceneBase.h"
#include "SceneMgr.h"
#include "Title.h"

//CSceneMgr�̃R���X�g���N�^
CSceneMgr::CSceneMgr(){

	//�J�n�V�[���̐ݒ�
	sceneNow = new CTitle;
}

//CSceneMgr�̃f�X�g���N�^
CSceneMgr::~CSceneMgr(){

	//���݂̃V�[�����폜
	delete sceneNow;
}

//CSceneMgr�̃C���X�^���X�̃|�C���^��Ԃ��֐�
CSceneMgr* CSceneMgr::GetInstance() {

	//�C���X�^���X�쐬
	static CSceneMgr* instance = new CSceneMgr;

	return instance;
}

//�V�[���̏�Ԑ��ڊ֐����Ăяo���֐�
void CSceneMgr::SceneUpdata() {

	//���݂̃V�[���̏�Ԑ��ڊ֐��̌Ăяo��(�ʏ�A�Ԃ�l�͓����V�[��)
	sceneNext = sceneNow->Updata(this);

	//���̃V�[�����قȂ����ꍇ�A�V�[�����ړ�
	if (sceneNext != sceneNow) {
		delete sceneNow;
		sceneNow = sceneNext;
		sceneNext = sceneNow->Updata(this);
	}
}

//�V�[���̕`��֐����Ăяo���֐�
void CSceneMgr::SceneDraw() {

	//���݂̃V�[���̕`��֐��̌Ăяo��
	sceneNow->Draw(this);
}
