#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <vector>

#define FIELD_WIDTH 9	//フィールドの幅
#define FIELD_HEIGHT 14	//フィールドの高さ
#define FIRST_LINE_NUM 1	//ゲーム開始時のブロックライン数
#define VECTOR_CAPACITY_NUM	10000 //あらかじめ確保しておく可変長配列の要素数

using namespace std;

class CDataLoader;

class CField
{
public:
	bool flag_Grid;	//グリッド線の描画フラグ
	CField();
	~CField();
	static CField* GetInstance();
	void Draw();
private:
	CDataLoader * data;
	vector<vector<short>> fieldBlocks;
	vector<short> makeNewLine();

};

#endif GAME_FIELD_H
