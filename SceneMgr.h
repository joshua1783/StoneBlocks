#ifndef SCENEMGR_H
#define SCENEMGR_H

class CSceneBase;

//�V�[���֌W���Ǘ�����N���X
class CSceneMgr
{
public:
	CSceneMgr();
	~CSceneMgr();
	static CSceneMgr* GetInstance();
	void SceneUpdata(int);
	void SceneDraw();
private:
	CSceneBase* sceneNow;	//���݂̃V�[��
	CSceneBase* sceneNext;	//���̃V�[��
};

#endif