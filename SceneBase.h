#ifndef SCENEBASE_H
#define SCENEBASE_H

class CSceneMgr;

//�V�[���֌W�̊��N���X
class CSceneBase
{
public:
	virtual ~CSceneBase() {};
	virtual CSceneBase* Updata(CSceneMgr* sceneMgr) = 0;
	virtual void Draw(CSceneMgr* sceneMgr) = 0;
};

#endif // !SCENEBASE_H
