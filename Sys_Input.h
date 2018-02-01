#ifndef SYS_INPUT_H
#define SYS_INPUT_H

#define BUFSIZE 256	//�L�[�o�b�t�@�T�C�Y


//���͊֌W���Ǘ�����N���X
class CInput
{
public:
	CInput();
	~CInput() {};
	static CInput* GetInstance();
	int GetKeyAll();
	int CheckKey(int keyCode) const;
private:
	char keyState[BUFSIZE];	//�L�[��ԕۑ��z��
	int  keyFrame[BUFSIZE];	//�L�[�̉����ꂽ�t���[�����ۑ��z��
};

#endif