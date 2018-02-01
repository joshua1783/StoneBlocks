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

#define MATERIAL_NUM 5.0	//素材総数

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
private:
	CSystem * system;
	CSceneMgr* scene;
	const float loadNum;	//ロードする素材数
	int loadCount;			//ロードした素材数
	//以下、各素材ハンドル格納用の変数
	int img_Background_Game;
	int img_BlockRed;
	int img_BlockBlue;
	int img_BlockGreen;
	int img_BlockYellow;

	void LoadParcent();
};

#endif // !SYS_DATALOADER_H
