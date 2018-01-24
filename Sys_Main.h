#ifndef SYS_MAIN_H
#define SYS_MAIN_H

#define CR_White GetColor(255, 255, 255)
#define CR_Black GetColor(0, 0, 0)

namespace {
	const int SCREEN_WIDTH = 800;	//ウィンドウ幅
	const int SCREEN_HEIGHT = 900;	//ウィンドウ高さ
	const int FONTSIZE_S = 24;		//フォントサイズ小
	const int FONTSIZE_M = 40;		//フォントサイズ中
	const int FONTSIZE_L = 60;		//フォントサイズ大
}

//フォントハンドル
enum FontHandle {
	FontHandle_S,
	FontHandle_M,
	FontHandle_L,

	FontHandle_Num
};

//システム関係を管理するクラス
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