#include <Windows.h>
#include <DxLib.h>
#include "Common.h"
#include "Sys_Main.h"
#include "Sys_Input.h"
#include "SceneMgr.h"

//CSystemのコンストラクタ
CSystem::CSystem(){
	
	//フォントハンドル作成
	fontHandle[FontHandle_S] = CreateFontToHandle(NULL, FONTSIZE_S, 8, DX_FONTTYPE_ANTIALIASING_8X8);
	fontHandle[FontHandle_M] = CreateFontToHandle(NULL, FONTSIZE_M, 8, DX_FONTTYPE_ANTIALIASING_8X8);
	fontHandle[FontHandle_L] = CreateFontToHandle(NULL, FONTSIZE_L, 8, DX_FONTTYPE_ANTIALIASING_8X8);
}
//CSystemのインスタンスのポインタを返す関数
CSystem* CSystem::GetInstance() {

	//インスタンス生成
	static CSystem instance;
	
	return &instance;
}

//フォントハンドルを返す関数
int CSystem::GetFontHandle(int fontSize) const {
	return fontHandle[fontSize];
}

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
	CSystem* system = CSystem::GetInstance();
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