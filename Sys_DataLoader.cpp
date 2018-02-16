#include <DxLib.h>
#include "Common.h"
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
	static CDataLoader *instance = new CDataLoader;

	return instance;
}

//素材の読み込みを行う関数
void CDataLoader::Load() {

	try {
		//画像
		ImgLoad(img_Background_Game, "img/Background_Game.png");
		ImgLoad(img_BlockRed, "img/Block_Red.png");
		ImgLoad(img_BlockBlue, "img/Block_Blue.png");
		ImgLoad(img_BlockGreen, "img/Block_Green.png");
		ImgLoad(img_BlockYellow, "img/Block_Yellow.png");
	}
	catch (const char* msg) {
		printfDx("Load Error -> %s", msg);
		WaitKey();
	}
}

//以下、各素材ハンドルを返す関数
int CDataLoader::GetImg_Background_Game() const {
	return img_Background_Game;
}
int CDataLoader::GetImg_BlockRed() const {
	return img_BlockRed;
}
int CDataLoader::GetImg_BlockBlue() const {
	return img_BlockBlue;
}
int CDataLoader::GetImg_BlockGreen() const {
	return img_BlockGreen;
}
int CDataLoader::GetImg_BlockYellow() const {
	return img_BlockYellow;
}


//素材の読み込み状況を％表示する関数
void CDataLoader::LoadParcent() {
	//読み込んだ素材数をカウントし、進行率を表示
	loadCount++;
	ClearDrawScreen();
	DrawStringToHandle(0, 0, "NowLading…", CR_White, system->GetFontHandle(FontHandle_S));
	DrawFormatStringToHandle(0, 100, CR_White, system->GetFontHandle(FontHandle_S), "%.0f％", loadCount / loadNum * 100);
	ScreenFlip();
}