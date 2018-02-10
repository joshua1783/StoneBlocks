#ifndef COMMON_H
#define COMMON_H

//複数のファイルで使用される定数やマクロを定義するヘッダ

#define CR_White GetColor(255, 255, 255)
#define CR_Black GetColor(0, 0, 0)

#define SCREEN_WIDTH  750	//ウィンドウ幅
#define SCREEN_HEIGHT 800	//ウィンドウ高さ
#define FONTSIZE_S 24		//フォントサイズ小
#define FONTSIZE_M 40		//フォントサイズ中
#define FONTSIZE_L 60		//フォントサイズ大

#define MARGIN_WIDTH  40	//余白の幅
#define MARGIN_HEIGHT 40	//余白の高さ
#define FIELD_WIDTH 9	//フィールドの幅
#define FIELD_HEIGHT 14	//フィールドの高さ
#define BLOCK_SIZE 48		//ブロックのサイズ

enum BlockType {
	BlockType_Red,
	BlockType_Blue,
	BlockType_Green,
	BlockType_Yellow,

	BlockType_Num
};

#endif // !COMMON_H
