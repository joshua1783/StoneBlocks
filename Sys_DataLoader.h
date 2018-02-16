#ifndef SYS_DATALOADER_H
#define SYS_DATALOADER_H

//通常タイプの画像読み込み用マクロ
//(引数:素材ハンドル, 画像の保存パス)
#define ImgLoad(target, pass){\
	target = LoadGraph(pass);\
	if(target == -1)\
		throw pass;\
	LoadParcent();\
}

#define MATERIAL_NUM 9.0	//素材総数

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
	int GetImg_BlockBlue() const;
	int GetImg_BlockGreen() const;
	int GetImg_BlockYellow() const;
	int GetImg_EffectRed(int) const;
	int GetImg_EffectBlue(int) const;
	int GetImg_EffectGreen(int) const;
	int GetImg_EffectYellow(int) const;
private:
	CSystem * system;
	CSceneMgr* scene;
	int loadCount;			//ロードした素材数
	//以下、各素材ハンドル格納用の変数
	int img_Background_Game;
	int img_BlockRed;
	int img_BlockBlue;
	int img_BlockGreen;
	int img_BlockYellow;
	int img_EffectRed[14];
	int img_EffectBlue[14];
	int img_EffectGreen[14];
	int img_EffectYellow[14];

	void LoadParcent();
};

#endif // !SYS_DATALOADER_H
