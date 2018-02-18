#include <DxLib.h>
#include "Sys_Font.h"

//CFontHandleのコンストラク
CFontHandle::CFontHandle(){
	//フォトハンドルの設定
	fontHandle_S = CreateFontToHandle(NULL, 24, 3);	//フォントサイズ小
	fontHandle_M = CreateFontToHandle(NULL, 40, 3);	//フォントサイズ中
	fontHandle_L = CreateFontToHandle(NULL, 100, 3);	//フォントサイズ大
}

CFontHandle::~CFontHandle(){
	//フォトハンドルの破棄
	InitFontToHandle();
}

CFontHandle* CFontHandle::GetInstance() {
	//インスタンス生成
	static CFontHandle* instance = new CFontHandle;

	return instance;
}

//以下,各サイズのフォントのハンドルを返す関数
int CFontHandle::GetFont_S() {
	return fontHandle_S;
}
int CFontHandle::GetFont_M() {
	return fontHandle_M;
}
int CFontHandle::GetFont_L() {
	return fontHandle_L;
}