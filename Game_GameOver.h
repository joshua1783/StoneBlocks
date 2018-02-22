#ifndef GAME_GAMEOVER_H
#define GAME_GAMEOVER_H

enum Continue {
	Continue_Yes,
	Continue_No,
};

class CInput;
class CFontHandle;
class CFade;
class CDataLoader;

class CGameOver
{
public:
	CGameOver();
	~CGameOver() {};
	static CGameOver* GetInstance();
	void UpData(int*);
	void Draw();
private:
	CInput * input;
	CFontHandle* font;
	CFade* fade;
	CDataLoader* data;
	int selectNow;
	/*à»â∫,ä÷êî*/
	int ContinueSelect();
};

#endif

