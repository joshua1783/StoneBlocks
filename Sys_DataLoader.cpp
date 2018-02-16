#include <DxLib.h>
#include "Common.h"
#include "SceneMgr.h"
#include "Sys_Main.h"
#include "Sys_DataLoader.h"

//CDataLoader�̃R���X�g���N�^
CDataLoader::CDataLoader():system(0), loadCount(0){

	//�C���X�^���X�擾
	system = CSystem::GetInstance();
}

//CDataLoader�̃C���X�^���X�̃|�C���^��Ԃ��֐�
CDataLoader* CDataLoader::GetInstance() {

	//�C���X�^���X����
	static CDataLoader *instance = new CDataLoader;

	return instance;
}

//�f�ނ̓ǂݍ��݂��s���֐�
void CDataLoader::Load() {

	try {
		//�摜
		ImgLoad(img_Background_Game, "img/Background_Game.png");
		ImgLoad(img_BlockRed, "img/Block_Red.png");
		ImgLoad(img_BlockBlue, "img/Block_Blue.png");
		ImgLoad(img_BlockGreen, "img/Block_Green.png");
		ImgLoad(img_BlockYellow, "img/Block_Yellow.png");

		//�����摜
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
	}
	catch (const char* msg) {
		printfDx("Load Error -> %s", msg);
		WaitKey();
	}
}

//�ȉ��A�e�f�ރn���h����Ԃ��֐�
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


//�f�ނ̓ǂݍ��ݏ󋵂����\������֐�
void CDataLoader::LoadParcent() {
	//�ǂݍ��񂾑f�ސ����J�E���g���A�i�s����\��
	loadCount++;
	ClearDrawScreen();
	DrawStringToHandle(0, 0, "NowLading�c", CR_White, system->GetFontHandle(FontHandle_S));
	DrawFormatStringToHandle(0, 100, CR_White, system->GetFontHandle(FontHandle_S), "%.0f��", loadCount / MATERIAL_NUM * 100);
	ScreenFlip();
}