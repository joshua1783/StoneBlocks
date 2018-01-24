#ifndef SYS_INPUT_H
#define SYS_INPUT_H

namespace {
	const int BUFSIZE = 256;	//�L�[�o�b�t�@�T�C�Y
}

//���͊֌W���Ǘ�����N���X
class CInput
{
public:
	CInput() {};
	~CInput() {};
	static CInput* GetInstance();
	int GetKeyAll();
	bool CheckKey(int keyCode) const;
private:
	char keyState[BUFSIZE];	//�L�[��ԕۑ��z��
};

#endif