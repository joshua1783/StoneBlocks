#ifndef GAME_PAUSE_H
#define GAME_PAUSE_H

//ポーズ中のメニュー一覧
enum PauseMenu {
	PM_ReturnGame,
	PM_ReturnTitle,
};

class CInput;
class CFontHandle;
class CDataLoader;

//ポーズ関係を管理する関数
class CPause
{
public:
	CPause();
	~CPause(){};
	static CPause* GetInstance();
	void UpData(int*);
	void Draw();
	void SetUp();
private:
	CInput * input;		//入力関係のインスタンス保存用ポインタ
	CFontHandle* font;	//フォント関係のインスタンス保存用ポインタ
	CFade* fade;		//フェード関係の運スタンス保存用ポインタ
	CDataLoader* data;	//素材関係のインスタンス保存用ポインタ
	int saveStatus;		//中断したゲーム状態保存変数
	int selectNow;		//選択中メニュー
	/*以下関数*/
	int PauseNow();
};

#endif