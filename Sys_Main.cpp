#include <Windows.h>
#include <DxLib.h>
#include "Common.h"
#include "Sys_Font.h"
#include "Sys_Input.h"
#include "Sys_Fade.h"
#include "Sys_DataLoader.h"
#include "SceneMgr.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);

	//Dx���C�u����������,�E�B���h�E���[�h�ݒ�,����ʕ`��ݒ�
	if (DxLib_Init() == -1 ||
		ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK ||
		SetDrawScreen(DX_SCREEN_BACK) == -1)
		return -1;
	
	//�E�B���h�E�쐬
	SetMainWindowText("StoneBlocks");
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	//�J�ڎ��Ԍv���p�ϐ�
	int time, timeNow;
	int timeOld = GetNowCount();

	//�C���X�^���X�擾
	CInput* input = CInput::GetInstance();
	CFade* fade = CFade::GetInstance();
	CSceneMgr* scene = CSceneMgr::GetInstance();
	CFontHandle* font = CFontHandle::GetInstance();
	CDataLoader* data = CDataLoader::GetInstance();
	
	//�f�ޓǂݍ���
	data->Load();

	//���C�����[�v
	while (ProcessMessage() == 0 &&
		   ClearDrawScreen() == 0 &&
		   input->GetKeyAll() == 0 &&
		   input->CheckKey(KEY_INPUT_ESCAPE) == 0){

		//���ݎ��Ԃ��擾��,1�t���[���ł̑J�ڎ��Ԃ��擾
		time = GetNowCount();
		timeNow = time - timeOld;
		timeOld = time;

		//��Ԑ��ڊ֐�
		scene->SceneUpdata(timeNow);
		fade->UpData();

		//�u�����h���[�h�Ȃ��ɐݒ�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		
		//�`��֐�
		scene->SceneDraw();
		fade->Draw();

		//��ʔ��f
		ScreenFlip();
	}

	//�������[�J��
	delete input;
	delete fade;
	delete scene;
	delete font;
	delete data;
	
	//Dx���C�u�����I������
	DxLib_End();

	return 0;
}