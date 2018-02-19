#ifndef SYS_DATALOADER_H
#define SYS_DATALOADER_H

//�摜�ǂݍ��ݗp�}�N��
//(����:�f�ރn���h��, �摜�̕ۑ��p�X)
#define ImgLoad(target, pass){\
	target = LoadGraph(pass);\
	if(target == -1)\
		throw pass;\
	LoadParcent();\
}
//���ʉ��ǂݍ��ݗp�}�N��
//(����:�f�ރn���h��, ���ʉ��̕ۑ��p�X)
#define SoundLoad(target, volume, pass){\
	target = LoadSoundMem(pass);\
	ChangeVolumeSoundMem(255 * volume / 100, target);\
	if(target == -1)\
		throw pass;\
	LoadParcent();\
}

#define MATERIAL_NUM 16.0	//�f�ޑ���

class CSystem;
class CSceneMgr;
class CFontHandle;

class CDataLoader
{
public:
	CDataLoader();
	~CDataLoader();
	static CDataLoader* GetInstance();
	void Load();
	int GetImg_Background_Game() const;
	int GetImg_BlockRed() const;
	int GetImg_BlockBlue() const;
	int GetImg_BlockGreen() const;
	int GetImg_BlockYellow() const;
	int GetImg_EffectRed(int) const;
	int GetImg_EffectBlue(int) const;
	int GetImg_EffectGreen(int) const;
	int GetImg_EffectYellow(int) const;
	int GetImg_EndIcon() const;
	int GetImg_GameOver() const;
	int GetSe_Break() const;
	int GetSe_Move() const;
	int GetSe_Bgm() const;
	int GetSe_Select() const;
	int GetSe_Enter() const;
private:
	CFontHandle * font;	
	int loadCount;	//���[�h�����f�ސ�
	//�ȉ��A�e�f�ރn���h���i�[�p�̕ϐ�
	int img_Background_Game;
	int img_BlockRed;
	int img_BlockBlue;
	int img_BlockGreen;
	int img_BlockYellow;
	int img_EffectRed[14];
	int img_EffectBlue[14];
	int img_EffectGreen[14];
	int img_EffectYellow[14];
	int img_EndIcon;
	int img_GameOver;
	int se_Break;
	int se_Move;
	int se_Bgm;
	int se_Select;
	int se_Enter;

	void LoadParcent();
};

#endif // !SYS_DATALOADER_H
