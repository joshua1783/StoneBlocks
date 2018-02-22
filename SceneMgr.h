#ifndef SCENEMGR_H
#define SCENEMGR_H

class CSceneBase;

//シーン関係を管理するクラス
class CSceneMgr
{
public:
	CSceneMgr();
	~CSceneMgr();
	static CSceneMgr* GetInstance();
	void SceneUpdata(int);
	void SceneDraw();
private:
	CSceneBase* sceneNow;	//現在のシーン
	CSceneBase* sceneNext;	//次のシーン
};

#endif