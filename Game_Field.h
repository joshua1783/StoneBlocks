#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <vector>

#define VECTOR_CAPACITY_NUM	10000	//あらかじめ確保しておく可変長配列の要素数
#define VANISH_MIN_MUN		3		//同色がつながっていた時に消えるための最小数
#define LINEUP_TIME_NUM		10000	//自動でラインが上がるまでの猶予時間(mS)
#define VANISH_TIME_NUM		1400	//フィールドブロックが消失するまでの猶予時間(mS)		
#define FALL_TIME_NUM		500		//浮いたブロックが1マス落ちるまでの猶予時間(mS)

using namespace std;

class CScore;
class CInput;
class CDataLoader;

class CField
{
public:
	CField();
	~CField(){};
	static CField* GetInstance();
	void UpData(int*, int);
	void Draw();
	int GetFieldBlockType(int, int);
	int GetVanishBlock(int, int);
	void Active2FieldBlock(int, int, short);
private:
	CScore * score;
	CInput * input;
	CDataLoader * data;
	bool flag_Grid;	//グリッド線の描画フラグ
	int count;
	int chain;
	int lineUpTime;
	unsigned int topDrowLineNow;
	int vanishBlocks[FIELD_HEIGHT][FIELD_WIDTH];
	vector<short> newLineBlocks;
	vector<vector<short>> fieldBlocks;

	void MakeNewLine();
	void LineUp();
	int CheckFieldBlocks();
	void CountSameBlock(int, int, int);
	void VanishFieldBlocks();
	int FallBlocks();
	int CheckGameOver();
};

#endif // !GAME_FIELD_H
