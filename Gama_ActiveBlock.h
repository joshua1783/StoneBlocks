#ifndef GAME_ACTIVE_BLOCK_H
#define GAME_ACTIVE_BLOCK_H

#define ACTIVEBLOCK_WIDTH  1	//�A�N�e�B�u�u���b�N�̕�
#define ACTIVEBLOCK_HEIGHT 2	//�A�N�e�B�u�u���b�N�̍���
#define DOWN_TIME_NUM 1500		//�A�N�e�B�u�u���b�N�̎��R�����܂ł̗P�\����(��S)
#define WAIT_TIME_NUM 1500		//�A�N�e�B�u�u���b�N���Œ肳���܂ł̗P�\����(mS)
	
using namespace std;

class CInput;
class CDataLoader;
class CField;

struct Pos{
	int x;
	int y;
};

class CActiveBlock
{
public:
	CActiveBlock();
	~CActiveBlock();
	static CActiveBlock* GetInstance();
	void UpDate(int*, int);
	void Draw();
private:
	CInput * input;
	CDataLoader * data;
	CField* field;
	vector<vector<short>> activeBlock;
	Pos pos;
	int count;
	int downTime;
	int waitTime;
	bool flag_BlockStop;
	void MoveBlock(int);
	void ChangeBlock();
	void MakeNewBlock();
	bool CheckHitBlock_X(int);
	bool CheckHitBlock_Y();
};

#endif // !GAME_ACTIVE_BLOCK_H