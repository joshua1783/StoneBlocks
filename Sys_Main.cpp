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

	//Dxライブラリ初期化,ウィンドウモード設定,裏画面描画設定
	if (DxLib_Init() == -1 ||
		ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK ||
		SetDrawScreen(DX_SCREEN_BACK) == -1)
		return -1;
	
	//ウィンドウ作成
	SetMainWindowText("StoneBlocks");
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	//遷移時間計測用変数
	int time, timeNow;
	int timeOld = GetNowCount();

	//インスタンス取得
	CInput* input = CInput::GetInstance();
	CFade* fade = CFade::GetInstance();
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

		//現在時間を取得し,1フレームでの遷移時間を取得
		time = GetNowCount();
		timeNow = time - timeOld;
		timeOld = time;

		//状態推移関数
		scene->SceneUpdata(timeNow);
		fade->UpData();

		//ブレンドモードなしに設定
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		
		//描画関数
		scene->SceneDraw();
		fade->Draw();

		//画面反映
		ScreenFlip();
	}

	//メモリー開放
	delete input;
	delete fade;
	delete scene;
	delete font;
	delete data;
	
	//Dxライブラリ終了処理
	DxLib_End();

	return 0;
}