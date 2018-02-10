#ifndef COMMON_H
#define COMMON_H

//�����̃t�@�C���Ŏg�p�����萔��}�N�����`����w�b�_

#define CR_White GetColor(255, 255, 255)
#define CR_Black GetColor(0, 0, 0)

#define SCREEN_WIDTH  750	//�E�B���h�E��
#define SCREEN_HEIGHT 800	//�E�B���h�E����
#define FONTSIZE_S 24		//�t�H���g�T�C�Y��
#define FONTSIZE_M 40		//�t�H���g�T�C�Y��
#define FONTSIZE_L 60		//�t�H���g�T�C�Y��

#define MARGIN_WIDTH  40	//�]���̕�
#define MARGIN_HEIGHT 40	//�]���̍���
#define FIELD_WIDTH 9	//�t�B�[���h�̕�
#define FIELD_HEIGHT 14	//�t�B�[���h�̍���
#define BLOCK_SIZE 48		//�u���b�N�̃T�C�Y

enum BlockType {
	BlockType_Red,
	BlockType_Blue,
	BlockType_Green,
	BlockType_Yellow,

	BlockType_Num
};

#endif // !COMMON_H
