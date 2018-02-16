#include <DxLib.h>
#include "Common.h"
#include "SceneBase.h"
#include "Game_Main.h"
#include "Game_Field.h"
#include "Gama_ActiveBlock.h"
#include "Sys_Input.h"
#include "Sys_DataLoader.h"

//CGame�̃R���X�g���N�^
CGame::CGame(): input(0), field(0), block(0), data(0), timeNow(0), timeOld(GetNowCount()){

	//�C���X�^���X�擾
	input = CInput::GetInstance();
	field = CField::GetInstance();
	block = CActiveBlock::GetInstance();
	data  = CDataLoader::GetInstance();

	//�X�e�[�^�X������
	status = GS_NewActiveBlock;
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
	
	//���ݎ��Ԃ��擾��,1�t���[���ł̑J�ڎ��Ԃ��擾
	int time = GetNowCount();
	timeNow = time - timeOld;
	timeOld = time;

	//�e�N���X�̏�Ԑ��ڊ֐�
	block->UpDate(&status, timeNow);
	field->UpData(&status, timeNow);
	printfDx("%d\n", status);
	return next;
}

//�Q�[���V�[���S�̂̕`��֐�
void CGame::Draw(CSceneMgr* sceneMgr) {

	DrawGraph(0, 0, data->GetImg_Background_Game(), FALSE);
	//�e�N���X�̕`��֐�
	field->Draw();
	block->Draw();
}

//1�t���[���̑J�ڎ��Ԃ�Ԃ��֐�
int CGame::GetTimeNow() {

	return timeNow;
}

