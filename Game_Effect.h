#ifndef GAME_EFFECT_H
#define GAME_EFFECT_H

#define EFFECT_BREAK_NUM 14
#define EFFECT_FLAME_TIME_NUM 100

class CField;
class CDataLoader;

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
	int count;
	int num;
};

#endif

