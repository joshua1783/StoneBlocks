#ifndef SYS_MAIN_H
#define SYS_MAIN_H

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