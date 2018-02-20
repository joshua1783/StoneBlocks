#ifndef TITLE_H
#define TITLE_H

enum TitleStatus {
	TS_Start,
	TS_FadeIn,
	TS_WaitEnter,
	TS_FadeOut,
};

class CInput;
class CFade;
class CFontHandle;
class CDataLoader;

class CTitle: public CSceneBase
{
public:
	CTitle();
	~CTitle(){};
	CSceneBase* Updata(CSceneMgr* sceneMgr);
	void Draw(CSceneMgr* sceneMgr);
private:
	CInput * input;
	CFade* fade;
	CFontHandle* font;
	CDataLoader* data;
	int status;
};

#endif