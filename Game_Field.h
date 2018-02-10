#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <vector>

#define VECTOR_CAPACITY_NUM	10000 //あらかじめ確保しておく可変長配列の要素数

using namespace std;

class CInput;
class CDataLoader;

class CField
{
public:
	CField();
	~CField();
	static CField* GetInstance();
	void UpData();
	void Draw();
	int GetFieldBlockType(int, int);
	void Active2FieldBlock(int, int, short);
private:
	CInput * input;
	CDataLoader * data;
	bool flag_Grid;	//グリッド線の描画フラグ
	vector<short> newLineBlocks;
	vector<vector<short>> fieldBlocks;
	void MakeNewLine();
};

#endif // !GAME_FIELD_H
