#include <DxLib.h>
#include "Common.h"
#include "SceneBase.h"
#include "Game_Main.h"
#include "Game_Field.h"
#include "Gama_ActiveBlock.h"
#include "Game_Effect.h"
#include "Game_Pause.h"
#include "Game_Score.h"
#include "Sys_Font.h"
#include "Sys_DataLoader.h"

//CGame�̃R���X�g���N�^
CGame::CGame(): field(0), block(0), effect(0), pause(0), score(0), data(0), timeNow(0), timeOld(GetNowCount()){

	//�C���X�^���X�擾
	field = CField::GetInstance();
	block = CActiveBlock::GetInstance();
	effect = CEffect::GetInstance();
	pause = CPause::GetInstance();
	score = CScore::GetInstance();
	font = CFontHandle::GetInstance();
	data  = CDataLoader::GetInstance();

	//�X�e�[�^�X������
	status = GS_SetUp;
}

//CGame�̃f�X�g���N�^
CGame::~CGame(){
	delete block;
	delete field;
	delete effect;
	delete pause;
	delete score;
}

//�Q�[���V�[���̏�Ԑ��ڊ֐�
CSceneBase* CGame::Updata(CSceneMgr* sceneMgr) {

	//���̃V�[�������݂̃V�[��(�Q�[���V�[��)�ɐݒ�
	CSceneBase* next = this;
	
	//���ݎ��Ԃ��擾��,1�t���[���ł̑J�ڎ��Ԃ��擾
	int time = GetNowCount();
	timeNow = time - timeOld;
	timeOld = time;

	if (status == GS_SetUp) {
		SetUp();
		status = GS_NewActiveBlock;
	}

	//�e�N���X�̏�Ԑ��ڊ֐�
	pause->UpData(&status);
	if (status != GS_Pause) {
		effect->UpData(&status, timeNow);
		block->UpDate(&status, timeNow);
		field->UpData(&status, timeNow);
		score->UpData();
	}
	
	return next;
}

//�Q�[���V�[���S�̂̕`��֐�
void CGame::Draw(CSceneMgr* sceneMgr) {

	//�w�i�`��
	DrawGraph(0, 0, data->GetImg_Background_Game(), FALSE);
	//�e�N���X�̕`��֐�
	field->Draw();
	block->Draw();
	score->Draw();
	if (status == GS_VanishFieldBlocks) 
		effect->Draw();
	if(status == GS_Pause)	
		pause->Draw();

	if (status == GS_GameOver) {
		DrawGraph(10, BLOCK_SIZE * 5 + MARGIN_HEIGHT, data->GetImg_GameOver(), TRUE);
	}
}

//1�t���[���̑J�ڎ��Ԃ�Ԃ��֐�
int CGame::GetTimeNow() {
	return timeNow;
}

//�Q�[���̏����ݒ���s���֐�
void CGame::SetUp() {

	PlaySoundMem(data->GetSe_Bgm(), DX_PLAYTYPE_LOOP);
}
