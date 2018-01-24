#ifndef SCENEBASE_H
#define SCENEBASE_H

class CSceneMgr;

//シーン関係の基底クラス
class CSceneBase
{
public:
	virtual ~CSceneBase() {};
	virtual CSceneBase* Updata(CSceneMgr* sceneMgr) = 0;
	virtual void Draw(CSceneMgr* sceneMgr) = 0;
};

#endif // !SCENEBASE_H
