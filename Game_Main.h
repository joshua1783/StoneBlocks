#ifndef GAME_MAIN_H
#define GAME_MAIN_H

class CFade;
class CDataLoader;
class CGameOver;
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
	~CGame(){};
	CSceneBase* Updata(CSceneMgr* sceneMgr, int timeNow);
	void Draw(CSceneMgr* sceneMgr);
private:
	CFade* fade;
	CDataLoader * data;
	CGameOver* gameover;
	CEffect* effect;
	CPause* pause;
	CScore* score;
	CField * field;
	CActiveBlock* block;
	int status;

	void SetUp();
};

#endif // !GAME_MAIN_H