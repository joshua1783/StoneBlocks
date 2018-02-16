#include <DxLib.h>
#include "Sys_Input.h"

//CInput�̃R���X�g���N�^
CInput::CInput(){

	for (int i = 0; i < BUFSIZE; i++){
		keyFrame[i] = 0;
	}
}

//CInput�̃C���X�^���X�̃|�C���^��Ԃ��֐�
CInput* CInput::GetInstance(){

	//�C���X�^���X����
	static CInput *instance = new CInput;

	return instance;
}

//�S�ẴL�[��Ԃ��擾����֐�
int CInput::GetKeyAll() {

	if (GetHitKeyStateAll(keyState) != 0)
		return -1;
	//�L�[��������Ă���Ȃ�Ή�����Ă���Ԃ̃t���[���������Z
	for (int i = 0; i < BUFSIZE; i++) {
		if (keyState[i] != 0) {
			keyFrame[i]++;
		}else {
			keyFrame[i] = 0;
		}
	}

	return 0;
}

//�����̃L�[�̏�Ԃ�Ԃ��֐�
int CInput::CheckKey(int keyCode) const {

	if (keyState[keyCode] != 0)
		return keyFrame[keyCode];

	return 0;
}