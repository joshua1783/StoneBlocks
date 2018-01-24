#ifndef SYS_DATALOADER_H
#define SYS_DATALOADER_H

//素材読み込み用マクロ(引数:素材ハンドル, 素材の保存パス)
#define MaterialLoad(target, name){\
	target = LoadGraph(name);\
	if(target == -1)\
		throw name;\
	LoadParcent();\
}

namespace {
	float materialNum = 1.0;	//素材総数
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

	const float loadNum;	//ロードする素材数
	int loadCount;			//ロードした素材数
	//以下、各素材ハンドル格納用の変数
	int img_BackgroundGame;
	int img_BlockRed;
};

#endif // !SYS_DATALOADER_H
