#include <DxLib.h>
#include "Sys_Input.h"

//Cinput�̃C���X�^���X�̃|�C���^��Ԃ��֐�
CInput* CInput::GetInstance() {

	//�C���X�^���X����
	static CInput instance;

	return &instance;
}

//�S�ẴL�[��Ԃ��擾����֐�
int CInput::GetKeyAll() {

	return GetHitKeyStateAll(keyState);
}

//�����̃L�[�̏�Ԃ�Ԃ��֐�
bool CInput::CheckKey(int keyCode) const {

	if (keyState[keyCode] != 0)
		return true;

	return false;
}