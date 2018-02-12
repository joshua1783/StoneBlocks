#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <vector>

#define VECTOR_CAPACITY_NUM	10000 //あらかじめ確保しておく可変長配列の要素数
#define LINEUP_TIME_NUM 10000	//自動でラインが上がるまでの猶予時間(mS)

using namespace std;

class CInput;
class CDataLoader;

class CField
{
public:
	CField();
	~CField();
	static CField* GetInstance();
	int UpData(int, int);
	void Draw();
	int GetFieldBlockType(int, int);
	void Active2FieldBlock(int, int, short);
private:
	CInput * input;
	CDataLoader * data;
	bool flag_Grid;	//グリッド線の描画フラグ
	int lineUpTime;
	unsigned int topDrowLineNow;
	vector<short> newLineBlocks;
	vector<vector<short>> fieldBlocks;
	void MakeNewLine();
	void LineUp();
};

#endif // !GAME_FIELD_H
