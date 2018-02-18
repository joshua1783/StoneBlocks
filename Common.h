#ifndef COMMON_H
#define COMMON_H

//�����̃t�@�C���Ŏg�p�����萔��}�N�����`����w�b�_

#define CR_White GetColor(255, 255, 255)
#define CR_Red   GetColor(255, 0, 0)
#define CR_Black GetColor(0, 0, 0)

#define SCREEN_WIDTH  750	//�E�B���h�E��
#define SCREEN_HEIGHT 800	//�E�B���h�E����

#define MARGIN_WIDTH  40	//�]���̕�
#define MARGIN_HEIGHT 40	//�]���̍���
#define FIELD_WIDTH 9		//�t�B�[���h�̉��}�X
#define FIELD_HEIGHT 14		//�t�B�[���h�̏c�}�X
#define BLOCK_SIZE 48		//�u���b�N�̃T�C�Y

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
