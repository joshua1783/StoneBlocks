#include <Windows.h>
#include <DxLib.h>
#include "Common.h"
#include "Sys_Font.h"
#include "Sys_Input.h"
#include "Sys_DataLoader.h"
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

	//インスタンス取得
	CInput* input = CInput::GetInstance();
	CSceneMgr* scene = CSceneMgr::GetInstance();
	CFontHandle* font = CFontHandle::GetInstance();
	CDataLoader* data = CDataLoader::GetInstance();
	
	//素材読み込み
	data->Load();

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

	//メモリー開放
	delete input;
	delete scene;
	delete font;
	delete data;
	
	//Dxライブラリ終了処理
	DxLib_End();

	return 0;
}