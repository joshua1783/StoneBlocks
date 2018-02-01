#ifndef GAME_MAIN_H
#define GAME_MAIN_H

#define BLOCK_SIZE 48	//�u���b�N�̃T�C�Y
#define MARGIN_WIDTH  40	//�]���̕�
#define MARGIN_HEIGHT 40	//�]���̍���

class CInput;
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
	CInput * input;
	CDataLoader * data;
	bool flag_Grid;	//�O���b�h���̕`��t���O
	void DrawBackgraound();
};

#endif // !GAME_MAIN_H