#ifndef GAME_PAUSE_H
#define GAME_PAUSE_H

//�|�[�Y���̃��j���[�ꗗ
enum PauseMenu {
	PM_ReturnGame,
	PM_ReturnTitle,
};

class CInput;
class CFontHandle;
class CDataLoader;

//�|�[�Y�֌W���Ǘ�����֐�
class CPause
{
public:
	CPause();
	~CPause(){};
	static CPause* GetInstance();
	void UpData(int*);
	void Draw();
	void SetUp();
private:
	CInput * input;		//���͊֌W�̃C���X�^���X�ۑ��p�|�C���^
	CFontHandle* font;	//�t�H���g�֌W�̃C���X�^���X�ۑ��p�|�C���^
	CFade* fade;		//�t�F�[�h�֌W�̉^�X�^���X�ۑ��p�|�C���^
	CDataLoader* data;	//�f�ފ֌W�̃C���X�^���X�ۑ��p�|�C���^
	int saveStatus;		//���f�����Q�[����ԕۑ��ϐ�
	int selectNow;		//�I�𒆃��j���[
	/*�ȉ��֐�*/
	int PauseNow();
};

#endif