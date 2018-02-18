#ifndef SYS_FONT_H
#define SYS_FONT_H

//フォントを管理するクラス
class CFontHandle
{
public:
	CFontHandle();
	~CFontHandle();
	static CFontHandle* GetInstance();
	int GetFont_S();
	int GetFont_M();
	int GetFont_L();
private:
	int fontHandle_S;	//フォントサイズSのハンドル
	int fontHandle_M;	//フォントサイズMのハンドル
	int fontHandle_L;	//フォントサイズLのハンドル
};

#endif // !SYS_FONT_H


