#include <DxLib.h>
#include "SceneMgr.h"
#include "Sys_Main.h"
#include "Sys_DataLoader.h"

//CDataLoader�̃R���X�g���N�^
CDataLoader::CDataLoader():system(0), loadNum(1.0), loadCount(0){

	//�C���X�^���X�擾
	system = CSystem::GetInstance();
}

//CDataLoader�̃C���X�^���X�̃|�C���^��Ԃ��֐�
CDataLoader* CDataLoader::GetInstance() {

	//�C���X�^���X����
	static CDataLoader instance;

	return &instance;
}

//�f�ނ̓ǂݍ��ݏ󋵂����\������֐�
void CDataLoader::LoadParcent() {
	//�ǂݍ��񂾑f�ސ����J�E���g���A�i�s����\��
	loadCount++;
	ProcessMessage();
	ClearDrawScreen();
	DrawStringToHandle(0, 0, "NowLading�c", CR_White, system->GetFontHandle(FontHandle_S));
	DrawFormatStringToHandle(0, 100, CR_White, system->GetFontHandle(FontHandle_S), "%.0f��", loadCount / loadNum * 100);
	ScreenFlip();
}

//�f�ނ̓ǂݍ��݂��s���֐�
void CDataLoader::Load() {

	try {
		//�摜
		MaterialLoad(img_BackgroundGame, "img/Background_Game.png");
		MaterialLoad(img_BlockRed, "img/Block_red.png");
	}
	catch (const char* msg) {
		printfDx("Load Error -> %s", msg);
		WaitKey();
	}
}

//�ȉ��A�e�f�ރn���h����Ԃ��֐�
int CDataLoader::GetImg_BackgroundGame() const {
	return img_BackgroundGame;
}

int CDataLoader::GetImg_BlockRed() const {
	return img_BlockRed;
}