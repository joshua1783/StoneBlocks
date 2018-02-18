#include <DxLib.h>
#include "Common.h"
#include "SceneBase.h"
#include "Game_Main.h"
#include "Game_Field.h"
#include "Gama_ActiveBlock.h"
#include "Game_Effect.h"
#include "Game_Pause.h"
#include "Sys_Input.h"
#include "Sys_Font.h"
#include "Sys_DataLoader.h"

//CGame�̃R���X�g���N�^
CGame::CGame(): input(0), field(0), block(0), effect(0), pause(0), data(0), timeNow(0), timeOld(GetNowCount()){

	//�C���X�^���X�擾
	input = CInput::GetInstance();
	field = CField::GetInstance();
	block = CActiveBlock::GetInstance();
	effect = CEffect::GetInstance();
	pause = CPause::GetInstance();
	font = CFontHandle::GetInstance();
	data  = CDataLoader::GetInstance();

	//�X�e�[�^�X������
	status = GS_NewActiveBlock;
	//�f�ޓǂݍ���
	data->Load();
	PlaySoundMem(data->GetSe_Bgm(), DX_PLAYTYPE_LOOP);
}

//CGame�̃f�X�g���N�^
CGame::~CGame(){
	delete block;
	delete field;
	delete effect;
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
	pause->UpData(&status);
	if (status != GS_Pause) {
		effect->UpData(&status, timeNow);
		block->UpDate(&status, timeNow);
		field->UpData(&status, timeNow);
	}
	
	return next;
}

//�Q�[���V�[���S�̂̕`��֐�
void CGame::Draw(CSceneMgr* sceneMgr) {

	DrawGraph(0, 0, data->GetImg_Background_Game(), FALSE);
	//�e�N���X�̕`��֐�
	field->Draw();
	block->Draw();
	if (status == GS_VanishFieldBlocks) effect->Draw();
	if(status == GS_Pause)	pause->Draw();

	if (status == GS_GameOver) {
		DrawGraph(10, BLOCK_SIZE * 5 + MARGIN_HEIGHT, data->GetImg_GameOver(), TRUE);
	}
}

//1�t���[���̑J�ڎ��Ԃ�Ԃ��֐�
int CGame::GetTimeNow() {
	return timeNow;
}

