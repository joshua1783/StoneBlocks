#include <Windows.h>
#include <DxLib.h>
#include "Common.h"
#include "Sys_Main.h"
#include "Sys_Input.h"
#include "SceneMgr.h"

//CSystem�̃R���X�g���N�^
CSystem::CSystem(){
	
	//�t�H���g�n���h���쐬
	fontHandle[FontHandle_S] = CreateFontToHandle(NULL, FONTSIZE_S, 8, DX_FONTTYPE_ANTIALIASING_8X8);
	fontHandle[FontHandle_M] = CreateFontToHandle(NULL, FONTSIZE_M, 8, DX_FONTTYPE_ANTIALIASING_8X8);
	fontHandle[FontHandle_L] = CreateFontToHandle(NULL, FONTSIZE_L, 8, DX_FONTTYPE_ANTIALIASING_8X8);
}
//CSystem�̃C���X�^���X�̃|�C���^��Ԃ��֐�
CSystem* CSystem::GetInstance() {

	//�C���X�^���X����
	static CSystem instance;
	
	return &instance;
}

//�t�H���g�n���h����Ԃ��֐�
int CSystem::GetFontHandle(int fontSize) const {
	return fontHandle[fontSize];
}

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

	//�C���X�^���X�擾
	CSystem* system = CSystem::GetInstance();
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