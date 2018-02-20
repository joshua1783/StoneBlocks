#include <DxLib.h>
#include "Common.h"
#include "SceneBase.h"
#include "Sys_Font.h"
#include "Sys_Fade.h"
#include "Sys_DataLoader.h"
#include "Game_Main.h"
#include "Game_Effect.h"
#include "Game_Pause.h"
#include "Game_Score.h"
#include "Game_Field.h"
#include "Gama_ActiveBlock.h"
#include "Title.h"

//CGame�̃R���X�g���N�^
CGame::CGame(): fade(0), field(0), block(0), effect(0), pause(0), score(0), data(0), timeNow(0), timeOld(GetNowCount()){

	//�C���X�^���X�擾
	font = CFontHandle::GetInstance();
	fade = CFade::GetInstance();
	data = CDataLoader::GetInstance();
	effect = CEffect::GetInstance();
	pause = CPause::GetInstance();
	score = CScore::GetInstance();
	field = CField::GetInstance();
	block = CActiveBlock::GetInstance();

	//�X�e�[�^�X������
	status = GS_SetUp;
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
	}
	else if (status == GS_FadeIn) {
		if (fade->CheckFade() == false) {
			//BGM�Đ�
			PlaySoundMem(data->GetSe_Bgm(), DX_PLAYTYPE_LOOP);
			status = GS_ActiveBlockMove;
		}
	}

	//�e�N���X�̏�Ԑ��ڊ֐�
	if (status != GS_SetUp || status != GS_FadeIn || status != GS_ReturnTitle) {
		pause->UpData(&status);
		if (status != GS_Pause) {
			effect->UpData(&status, timeNow);
			block->UpDate(&status, timeNow);
			field->UpData(&status, timeNow);
			score->UpData();
		}
	}

	//�t�F�[�h�A�E�g���I��������^�C�g���V�[���Ɉڍs
	if (status == GS_ReturnTitle) {
		if(fade->CheckFade() == false)
			next = new CTitle;
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
	if (status == GS_VanishFieldBlocks || status == GS_Pause) 
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
	//�e�평���ݒ�
	block->SetUp();
	field->SetUp();
	effect->SetUp();
	pause->SetUp();
	score->SetUp();
	fade->FadeIn();
	//�t�F�[�h�C����ԂɈڍs
	status = GS_FadeIn;
}
