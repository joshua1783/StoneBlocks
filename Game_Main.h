#ifndef GAME_MAIN_H
#define GAME_MAIN_H

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
	CDataLoader * data;
	void DrawBackgraound();
};

#endif // !GAME_MAIN_H