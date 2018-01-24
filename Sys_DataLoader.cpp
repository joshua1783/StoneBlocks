#include <DxLib.h>
#include "SceneMgr.h"
#include "Sys_Main.h"
#include "Sys_DataLoader.h"

//CDataLoaderのコンストラクタ
CDataLoader::CDataLoader():system(0), loadNum(1.0), loadCount(0){

	//インスタンス取得
	system = CSystem::GetInstance();
}

//CDataLoaderのインスタンスのポインタを返す関数
CDataLoader* CDataLoader::GetInstance() {

	//インスタンス生成
	static CDataLoader instance;

	return &instance;
}

//素材の読み込み状況を％表示する関数
void CDataLoader::LoadParcent() {
	//読み込んだ素材数をカウントし、進行率を表示
	loadCount++;
	ProcessMessage();
	ClearDrawScreen();
	DrawStringToHandle(0, 0, "NowLading…", CR_White, system->GetFontHandle(FontHandle_S));
	DrawFormatStringToHandle(0, 100, CR_White, system->GetFontHandle(FontHandle_S), "%.0f％", loadCount / loadNum * 100);
	ScreenFlip();
}

//素材の読み込みを行う関数
void CDataLoader::Load() {

	try {
		//画像
		MaterialLoad(img_BackgroundGame, "img/Background_Game.png");
		MaterialLoad(img_BlockRed, "img/Block_red.png");
	}
	catch (const char* msg) {
		printfDx("Load Error -> %s", msg);
		WaitKey();
	}
}

//以下、各素材ハンドルを返す関数
int CDataLoader::GetImg_BackgroundGame() const {
	return img_BackgroundGame;
}

int CDataLoader::GetImg_BlockRed() const {
	return img_BlockRed;
}