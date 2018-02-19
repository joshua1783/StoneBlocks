#ifndef GAME_EFFECT_H
#define GAME_EFFECT_H

#define EFFECT_BREAK_NUM	  14	//�j��G�t�F�N�g�摜�̕�����
#define EFFECT_FLAME_TIME_NUM 100	//�G�t�F�N�g1�t���[��������̗P�\����(mS)

class CField;
class CDataLoader;

//�G�t�F�N�g�֌W���Ǘ�����N���X
class CEffect
{
public:
	CEffect();
	~CEffect() {};
	static CEffect* GetInstance();
	void UpData(int*, int);
	void Draw();
	void SetUp();
private:
	CField * field;		//�t�B�[���h�u���b�N�֌W�̃C���X�^���X�ۑ��p�|�C���^
	CDataLoader* data;	//�f�ފ֌W�̃C���X�^���X�ۑ��p�|�C���^
	int count;			//�ėp�ϐ�
	int num;			//���݂̃t���[�����ۑ��ϐ�
};

#endif

