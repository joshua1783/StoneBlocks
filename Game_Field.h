#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <vector>

#define VECTOR_CAPACITY_NUM	10000	//���炩���ߊm�ۂ��Ă����ϒ��z��̗v�f��
#define VANISH_MIN_MUN		3		//���F���Ȃ����Ă������ɏ����邽�߂̍ŏ���
#define LINEUP_TIME_NUM		10000	//�����Ń��C�����オ��܂ł̗P�\����(mS)
#define VANISH_TIME_NUM		1400	//�t�B�[���h�u���b�N����������܂ł̗P�\����(mS)		
#define FALL_TIME_NUM		500		//�������u���b�N��1�}�X������܂ł̗P�\����(mS)

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
	bool flag_Grid;	//�O���b�h���̕`��t���O
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
