#ifndef COMMON_H
#define COMMON_H

//複数のファイルで使用される定数やマクロを定義するヘッダ

#define CR_White GetColor(255, 255, 255)
#define CR_Red   GetColor(255, 0, 0)
#define CR_Black GetColor(0, 0, 0)

#define SCREEN_WIDTH  750	//ウィンドウ幅
#define SCREEN_HEIGHT 800	//ウィンドウ高さ

#define MARGIN_WIDTH  40	//余白の幅
#define MARGIN_HEIGHT 40	//余白の高さ
#define FIELD_WIDTH 9		//フィールドの横マス
#define FIELD_HEIGHT 14		//フィールドの縦マス
#define BLOCK_SIZE 48		//ブロックのサイズ

enum BlockType {
	BlockType_Red,
	BlockType_Blue,
	BlockType_Green,
	BlockType_Yellow,

	BlockType_Num
};

enum GameStatus {
	GS_NewActiveBlock,
	GS_ActiveBlockMove,
	GS_CheckFieldBlocks,
	GS_VanishFieldBlocks,
	GS_FallBlocks,
	GS_CheckGameOver,
	GS_GameOver,
	GS_Pause,
};

#endif // !COMMON_H
