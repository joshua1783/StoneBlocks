#ifndef GAME_MAIN_H
#define GAME_MAIN_H

class CInput;
class CField;
class CActiveBlock;
class CDataLoader;

//ゲームシーン全体を管理するクラス
class CGame : public CSceneBase
{
public:
	CGame();
	~CGame();
	CSceneBase* Updata(CSceneMgr* sceneMgr);
	void Draw(CSceneMgr* sceneMgr);
private:
	CInput * input;
	CField* field;
	CActiveBlock* block;
	CDataLoader * data;
};

#endif // !GAME_MAIN_H