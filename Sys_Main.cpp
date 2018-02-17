#include <Windows.h>
#include <DxLib.h>
#include "Common.h"
#include "Sys_Input.h"
#include "SceneMgr.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Dxライブラリ初期化,ウィンドウモード設定,裏画面描画設定
	if (DxLib_Init() == -1 ||
		ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK ||
		SetDrawScreen(DX_SCREEN_BACK) == -1)
		return -1;
	
	//ウィンドウ作成
	SetMainWindowText("StoneBlocks");
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	//フォントサイズ指定
	SetFontSize(45);
	
	//インスタンス取得
	CInput* input = CInput::GetInstance();
	CSceneMgr* scene = CSceneMgr::GetInstance();

	//メインループ
	while (ProcessMessage() == 0 &&
		   ClearDrawScreen() == 0 &&
		   input->GetKeyAll() == 0 &&
		   input->CheckKey(KEY_INPUT_ESCAPE) == 0){

		scene->SceneUpdata();

		scene->SceneDraw();

		//画面反映
		ScreenFlip();

	}
	
	//Dxライブラリ終了処理
	DxLib_End();

	return 0;
}