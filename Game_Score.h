#ifndef GAME_SCORE_H
#define GAME_SCORE_H

#define SCOREBOARD_X	   512		 //スコアボードのx座標
#define SCOREBOARD_Y	   280		 //スコアボードのy座標
#define SCORE_MAX		   999999999 //スコアの上限
#define MOVE_ADDSCORE_NUM  1		 //ユーザー入力による移動での基本加算スコア
#define BREAK_ADDSCORE_NUM 100		 //1ラインが消えた時の基本加算スコア

class CFontHandle;

class CScore
{
public:
	CScore();
	~CScore() {};
	static CScore* GetInstance();
	void UpData();
	void Draw();
	void SetUp();
	void ScoreAdd_Move();
	void ScoreAdd_Break(int, int);
private:
	CFontHandle * font;	//フォント関係のインスタンス保存用ポインタ
	int score;			//現在スコア
	int highScore;		//ハイスコア
	/*以下,関数*/
	void HighScoreSave();
	void HighScoreLoad();
};

#endif