#include <Windows.h>
#include <DxLib.h>
#include "Common.h"
#include "Sys_Input.h"
#include "SceneMgr.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Dx���C�u����������,�E�B���h�E���[�h�ݒ�,����ʕ`��ݒ�
	if (DxLib_Init() == -1 ||
		ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK ||
		SetDrawScreen(DX_SCREEN_BACK) == -1)
		return -1;
	
	//�E�B���h�E�쐬
	SetMainWindowText("StoneBlocks");
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	//�t�H���g�T�C�Y�w��
	SetFontSize(45);
	
	//�C���X�^���X�擾
	CInput* input = CInput::GetInstance();
	CSceneMgr* scene = CSceneMgr::GetInstance();

	//���C�����[�v
	while (ProcessMessage() == 0 &&
		   ClearDrawScreen() == 0 &&
		   input->GetKeyAll() == 0 &&
		   input->CheckKey(KEY_INPUT_ESCAPE) == 0){

		scene->SceneUpdata();

		scene->SceneDraw();

		//��ʔ��f
		ScreenFlip();

	}
	
	//Dx���C�u�����I������
	DxLib_End();

	return 0;
}