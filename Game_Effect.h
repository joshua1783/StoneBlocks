#ifndef GAME_EFFECT_H
#define GAME_EFFECT_H

#define EFFECT_BREAK_NUM 14			//破壊エフェクト画像の分割数
#define EFFECT_FLAME_TIME_NUM 100	//エフェクト1フレーム当たりの猶予時間(mS)

class CField;
class CDataLoader;

//エフェクト関係のクラス
class CEffect
{
public:
	CEffect();
	~CEffect() {};
	static CEffect* GetInstance();
	void UpData(int*, int);
	void Draw();
private:
	CField * field;
	CDataLoader* data;
	int count;	//汎用変数
	int num;	//現在のフレーム数保存変数
};

#endif

