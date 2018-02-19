#ifndef GAME_SCORE_H
#define GAME_SCORE_H

#define SCOREBOARD_X 512
#define SCOREBOARD_Y 280
#define SCORE_MAX 999999999
#define MOVE_ADDACORE_NUM 1
#define BREAK_ADDSCORE_NUM 100

class CFontHandle;

class CScore
{
public:
	CScore();
	~CScore() {};
	static CScore* GetInstance();
	void UpData();
	void Draw();
	void ScoreAdd_Move();
	void ScoreAdd_Break(int, int);
private:
	CFontHandle * font;
	int score;
	int highScore;

	void HighScoreSave();
	void HighScoreLoad();
};

#endif