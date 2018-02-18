#ifndef GAME_MAIN_H
#define GAME_MAIN_H

class CInput;
class CField;
class CActiveBlock;
class CEffect;
class CPause;
class CFontHandle;
class CDataLoader;

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
	CInput * input;
	CField* field;
	CActiveBlock* block;
	CEffect* effect;
	CPause* pause;
	CFontHandle* font;
	CDataLoader * data;
	int status;
	int timeNow;
	int timeOld;
};

#endif // !GAME_MAIN_H