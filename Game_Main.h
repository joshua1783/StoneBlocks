#ifndef GAME_MAIN_H
#define GAME_MAIN_H

class CDataLoader;

//�Q�[���V�[���S�̂��Ǘ�����N���X
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