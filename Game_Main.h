#ifndef GAME_MAIN_H
#define GAME_MAIN_H

#define BLOCK_SIZE 48	//ブロックのサイズ
#define MARGIN_WIDTH  40	//余白の幅
#define MARGIN_HEIGHT 40	//余白の高さ

class CInput;
class CDataLoader;

//ゲームシーン全体を管理するクラス
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
	bool flag_Grid;	//グリッド線の描画フラグ
	void DrawBackgraound();
};

#endif // !GAME_MAIN_H