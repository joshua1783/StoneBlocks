#ifndef SYS_DATALOADER_H
#define SYS_DATALOADER_H

//�ʏ�^�C�v�̉摜�ǂݍ��ݗp�}�N��
//(����:�f�ރn���h��, �摜�̕ۑ��p�X)
#define ImgLoad(target, pass){\
	target = LoadGraph(pass);\
	if(target == -1)\
		throw pass;\
	LoadParcent();\
}

#define MATERIAL_NUM 2.0	//�f�ޑ���

class CSystem;
class CSceneMgr;

class CDataLoader
{
public:
	CDataLoader();
	~CDataLoader() {};
	static CDataLoader* GetInstance();
	void Load();
	int GetImg_Background_Game() const;
	int GetImg_BlockRed() const;
private:
	CSystem * system;
	CSceneMgr* scene;
	const float loadNum;	//���[�h����f�ސ�
	int loadCount;			//���[�h�����f�ސ�
	//�ȉ��A�e�f�ރn���h���i�[�p�̕ϐ�
	int img_Background_Game;
	int img_BlockRed;

	void LoadParcent();
};

#endif // !SYS_DATALOADER_H
