#ifndef SYS_MAIN_H
#define SYS_MAIN_H

#define CR_White GetColor(255, 255, 255)
#define CR_Black GetColor(0, 0, 0)

namespace {
	const int SCREEN_WIDTH = 800;	//�E�B���h�E��
	const int SCREEN_HEIGHT = 900;	//�E�B���h�E����
	const int FONTSIZE_S = 24;		//�t�H���g�T�C�Y��
	const int FONTSIZE_M = 40;		//�t�H���g�T�C�Y��
	const int FONTSIZE_L = 60;		//�t�H���g�T�C�Y��
}

//�t�H���g�n���h��
enum FontHandle {
	FontHandle_S,
	FontHandle_M,
	FontHandle_L,

	FontHandle_Num
};

//�V�X�e���֌W���Ǘ�����N���X
class CSystem
{
public:
	CSystem();
	~CSystem() {};
	static CSystem* GetInstance();
	int GetFontHandle(int fontSize) const;
private:
	int fontHandle[FontHandle_Num];
};

#endif