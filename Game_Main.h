#ifndef GAME_MAIN_H
#define GAME_MAIN_H

class CFontHandle;
class CDataLoader;
class CEffect;
class CPause;
class CScore;
class CField;
class CActiveBlock;

//ゲームシーン全体を管理するクラス
class CGame : public CSceneBase
{
public:
	CGame();
	~CGame();
	CSceneBase* Updata(CSceneMgr* sceneMgr);
	void Draw(CSceneMgr* sceneMgr);
	int GetTimeNow();
private:
	CFontHandle * font;
	CDataLoader * data;
	CEffect* effect;
	CPause* pause;
	CScore* score;
	CField * field;
	CActiveBlock* block;
	int status;
	int timeNow;
	int timeOld;

	void SetUp();
};

#endif // !GAME_MAIN_H