#ifndef GAME_ACTIVE_BLOCK_H
#define GAME_ACTIVE_BLOCK_H

#define ACTIVEBLOCK_WIDTH  1
#define ACTIVEBLOCK_HEIGHT 2
#define DOWN_TIME_NUM 60
#define WAIT_TIME_NUM 60

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
	void UpDate();
	void Draw();
private:
	CInput * input;
	CDataLoader * data;
	CField* field;
	vector<vector<short>> activeBlock;
	Pos pos;
	int downTime;
	int waitTime;
	bool flag_BlockStop;
	void MoveBlock();
	void ChangeBlock();
	void MakeNewBlock();
	Pos CheckHitBlock(Pos);
};

#endif // !GAME_ACTIVE_BLOCK_H