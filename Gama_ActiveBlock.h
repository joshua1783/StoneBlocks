#ifndef GAME_ACTIVE_BLOCK_H
#define GAME_ACTIVE_BLOCK_H

#define ACTIVEBLOCK_WIDTH  1	//アクティブブロックの幅
#define ACTIVEBLOCK_HEIGHT 2	//アクティブブロックの高さ
#define DOWN_TIME_NUM 1500		//アクティブブロックの自由落下までの猶予時間(ｍS)
#define WAIT_TIME_NUM 1500		//アクティブブロックが固定されるまでの猶予時間(mS)
	
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