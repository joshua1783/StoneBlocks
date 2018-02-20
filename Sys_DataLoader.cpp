#include <DxLib.h>
#include "Common.h"
#include "SceneMgr.h"
#include "Sys_Font.h"
#include "Sys_DataLoader.h"

//CDataLoaderのコンストラクタ
CDataLoader::CDataLoader():font(0), loadCount(0){

	//インスタンス取得
	font = CFontHandle::GetInstance();
}

//CDataLoaderのコンストラクタ
CDataLoader::~CDataLoader(){

	//読み込んだ全ての素材データを消去
	InitGraph();
	InitSoundMem();
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
		ImgLoad(img_TitleLogo, "img/TitleLogo.png");
		ImgLoad(img_BlockRed, "img/Block_Red.png");
		ImgLoad(img_BlockBlue, "img/Block_Blue.png");
		ImgLoad(img_BlockGreen, "img/Block_Green.png");
		ImgLoad(img_BlockYellow, "img/Block_Yellow.png");
		ImgLoad(img_EndIcon, "img/EndIcon.png");
		ImgLoad(img_GameOver, "img/GameOver.png");

		//分割画像
		LoadDivGraph("img/Effect_Red.png", 14, 14, 1, 48, 48, img_EffectRed);
		if (img_EffectRed[0] == -1)
			throw "img/Effect_Red.png";
		LoadParcent();
		LoadDivGraph("img/Effect_Blue.png", 14, 14, 1, 48, 48, img_EffectBlue);
		if (img_EffectBlue[0] == -1)
			throw "img/Effect_Blue.png";
		LoadParcent();
		LoadDivGraph("img/Effect_Green.png", 14, 14, 1, 48, 48, img_EffectGreen);
		if (img_EffectGreen[0] == -1)
			throw "img/Effect_Green.png";
		LoadParcent();
		LoadDivGraph("img/Effect_Yellow.png", 14, 14, 1, 48, 48, img_EffectYellow);
		if (img_EffectYellow[0] == -1)
			throw "img/Effect_Yellow.png";
		LoadParcent();

		//効果音
		SoundLoad(se_Break, 80, "se/Break.wav");
		SoundLoad(se_Move, 50, "se/Move.wav");
		SoundLoad(se_Bgm, 60, "se/BGM.wav");
		SoundLoad(se_Select, 60, "se/Select.wav");
		SoundLoad(se_Enter, 60, "se/Enter.wav");
		
	}
	catch (const char* msg) {
		printfDx("Load Error -> %s\n", msg);
		WaitKey();
	}
}

//素材の読み込み状況を％表示する関数
void CDataLoader::LoadParcent() {
	//読み込んだ素材数をカウントし、進行率を表示
	loadCount++;
	ClearDrawScreen();
	DrawStringToHandle(SCREEN_HEIGHT / 2, SCREEN_HEIGHT - 50, "NowLading…", CR_White, font->GetFont_M());
	DrawFormatStringToHandle(SCREEN_HEIGHT / 2 + 230, SCREEN_HEIGHT - 50, CR_White, font->GetFont_M(), "%.0f％", loadCount / MATERIAL_NUM * 100);
	ScreenFlip();
}

//以下、各素材ハンドルを返す関数
int CDataLoader::GetImg_Background_Game() const {
	return img_Background_Game;
}
int CDataLoader::GetImg_TitleLogo() const {
	return img_TitleLogo;
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
int CDataLoader::GetImg_EffectRed(int i) const {
	return img_EffectRed[i];
}
int CDataLoader::GetImg_EffectBlue(int i) const {
	return img_EffectBlue[i];
}
int CDataLoader::GetImg_EffectGreen(int i) const {
	return img_EffectGreen[i];
}
int CDataLoader::GetImg_EffectYellow(int i) const {
	return img_EffectYellow[i];
}
int CDataLoader::GetImg_EndIcon() const {
	return img_EndIcon;
}
int CDataLoader::GetImg_GameOver() const {
	return img_GameOver;
}
int CDataLoader::GetSe_Break() const {
	return se_Break;
}
int CDataLoader::GetSe_Move() const {
	return se_Move;
}
int CDataLoader::GetSe_Bgm() const {
	return se_Bgm;
}
int CDataLoader::GetSe_Select() const {
	return se_Select;
}
int CDataLoader::GetSe_Enter() const {
	return se_Enter;
}