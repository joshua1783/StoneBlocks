#include <DxLib.h>
#include "Common.h"
#include "SceneBase.h"
#include "Sys_Fade.h"
#include "Sys_DataLoader.h"
#include "Game_Main.h"
#include "Game_GameOver.h"
#include "Game_Effect.h"
#include "Game_Pause.h"
#include "Game_Score.h"
#include "Game_Field.h"
#include "Gama_ActiveBlock.h"
#include "Title.h"

//CGame�̃R���X�g���N�^
CGame::CGame(): fade(0), data(0), gameover(0), effect(0), pause(0), score(0), field(0), block(0) {

	//�C���X�^���X�擾
	fade     = CFade::GetInstance();
	data     = CDataLoader::GetInstance();
	gameover = CGameOver::GetInstance();
	effect   = CEffect::GetInstance();
	pause	 = CPause::GetInstance();
	score    = CScore::GetInstance();
	field    = CField::GetInstance();
	block    = CActiveBlock::GetInstance();

	//�X�e�[�^�X������
	status = GS_SetUp;
}

//�Q�[���V�[���̏�Ԑ��ڊ֐�
CSceneBase* CGame::Updata(CSceneMgr* sceneMgr, int timeNow) {

	//���̃V�[�������݂̃V�[��(�Q�[���V�[��)�ɐݒ�
	CSceneBase* next = this;

	//�Q�[���������
	if (status == GS_SetUp) {
		SetUp();
		//�t�F�[�h�C����ԂɈڍs
		status = GS_FadeIn;
	}
	//�t�F�[�h�C�����
	//�t�F�[�h���I�����Ă�����Q�[���J�n
	else if (status == GS_FadeIn) {
		if (fade->CheckFade() == false) {
			//BGM�Đ�
			PlaySoundMem(data->GetSe_Bgm(), DX_PLAYTYPE_LOOP);
			//�A�N�e�B�u�u���b�N�ړ����
			status = GS_ActiveBlockMove;
		}
	}

	//�e�N���X�̏�Ԑ��ڊ֐�
	if (status != GS_SetUp || status != GS_FadeIn || status != GS_Continue || status != GS_FadeOut || status != GS_ReturnTitle) {
		pause->UpData(&status);
		if (status != GS_Pause) {
			effect->UpData(&status, timeNow);
			block->UpDate(&status, timeNow);
			field->UpData(&status, timeNow);
			score->UpData();
			if (status == GS_GameOver)	gameover->UpData(&status);
		}
	}
	
	//�t�F�[�h���I�����Ă�����Q�[��������ԂɈڍs
	if (status == GS_Continue) {
		if (fade->CheckFade() == false)
			status = GS_SetUp;
	}
	//�t�F�[�h�A�E�g���I��������^�C�g���V�[���Ɉڍs
	if (status == GS_FadeOut) {
		if (fade->CheckFade() == false)
			status = GS_ReturnTitle;
	}else if (status == GS_ReturnTitle) {
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
	if (status == GS_VanishFieldBlocks || status == GS_Pause) effect->Draw();
	if (status == GS_Pause)	pause->Draw();

	if (status == GS_GameOver)
		gameover->Draw();

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
}
