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

//�Q�[���V�[���S�̂��Ǘ�����N���X
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