#ifndef SYS_DATALOADER_H
#define SYS_DATALOADER_H

//�f�ޓǂݍ��ݗp�}�N��(����:�f�ރn���h��, �f�ނ̕ۑ��p�X)
#define MaterialLoad(target, name){\
	target = LoadGraph(name);\
	if(target == -1)\
		throw name;\
	LoadParcent();\
}

namespace {
	float materialNum = 1.0;	//�f�ޑ���
}

class CSystem;
class CSceneMgr;

class CDataLoader
{
public:
	CDataLoader();
	~CDataLoader() {};
	static CDataLoader* GetInstance();
	void LoadParcent();
	void Load();

	int GetImg_BackgroundGame() const;
	int GetImg_BlockRed() const;
private:
	CSystem * system;
	CSceneMgr* scene;

	const float loadNum;	//���[�h����f�ސ�
	int loadCount;			//���[�h�����f�ސ�
	//�ȉ��A�e�f�ރn���h���i�[�p�̕ϐ�
	int img_BackgroundGame;
	int img_BlockRed;
};

#endif // !SYS_DATALOADER_H
