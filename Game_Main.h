#ifndef GAME_MAIN_H
#define GAME_MAIN_H

class CInput;
class CField;
class CActiveBlock;
class CDataLoader;

//�Q�[���V�[���S�̂��Ǘ�����N���X
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
	CDataLoader * data;
	int status;
	int timeNow;
	int timeOld;
};

#endif // !GAME_MAIN_H