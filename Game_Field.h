#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <vector>

#define VECTOR_CAPACITY_NUM	10000 //���炩���ߊm�ۂ��Ă����ϒ��z��̗v�f��
#define LINEUP_TIME_NUM 10000	//�����Ń��C�����オ��܂ł̗P�\����(mS)
#define VANISH_MIN_MUN 3	//���F���Ȃ����Ă������ɏ����邽�߂̍ŏ���

using namespace std;

class CInput;
class CDataLoader;

class CField
{
public:
	CField();
	~CField();
	static CField* GetInstance();
	void UpData(int*, int);
	void Draw();
	int GetFieldBlockType(int, int);
	void Active2FieldBlock(int, int, short);
private:
	CInput * input;
	CDataLoader * data;
	bool flag_Grid;	//�O���b�h���̕`��t���O
	int lineUpTime;
	unsigned int topDrowLineNow;
	int bufferBlocks[FIELD_HEIGHT][FIELD_WIDTH];
	vector<short> newLineBlocks;
	vector<vector<short>> fieldBlocks;
	void MakeNewLine();
	void LineUp();
	int CheckFieldBlocks();
	void CountSameBlock(int, int);
	void DropBlocks();
};

#endif // !GAME_FIELD_H
