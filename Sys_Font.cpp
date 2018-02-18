#include <DxLib.h>
#include "Sys_Font.h"

//CFontHandle�̃R���X�g���N
CFontHandle::CFontHandle(){
	//�t�H�g�n���h���̐ݒ�
	fontHandle_S = CreateFontToHandle(NULL, 24, 3);	//�t�H���g�T�C�Y��
	fontHandle_M = CreateFontToHandle(NULL, 40, 3);	//�t�H���g�T�C�Y��
	fontHandle_L = CreateFontToHandle(NULL, 100, 3);	//�t�H���g�T�C�Y��
}

CFontHandle::~CFontHandle(){
	//�t�H�g�n���h���̔j��
	InitFontToHandle();
}

CFontHandle* CFontHandle::GetInstance() {
	//�C���X�^���X����
	static CFontHandle* instance = new CFontHandle;

	return instance;
}

//�ȉ�,�e�T�C�Y�̃t�H���g�̃n���h����Ԃ��֐�
int CFontHandle::GetFont_S() {
	return fontHandle_S;
}
int CFontHandle::GetFont_M() {
	return fontHandle_M;
}
int CFontHandle::GetFont_L() {
	return fontHandle_L;
}