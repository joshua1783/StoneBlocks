#include <DxLib.h>
#include "Common.h"
#include "Game_Score.h"
#include "Sys_Font.h"

CScore::CScore(): score(0), highScore(0), font(0){
	
	font = CFontHandle::GetInstance();

	HighScoreLoad();
}

CScore* CScore::GetInstance() {

	static CScore* instance = new CScore;

	return instance;
}

void CScore::UpData() {

	if (score >= highScore) {

		highScore = score;
		HighScoreSave();
	}
}

void CScore::Draw() {

	DrawBox(SCOREBOARD_X, SCOREBOARD_Y, SCREEN_WIDTH - MARGIN_WIDTH, SCOREBOARD_Y + 210, CR_Black, TRUE);
	DrawStringToHandle(SCOREBOARD_X + 5, SCOREBOARD_Y +   5, "SCORE", CR_White, font->GetFont_M());
	DrawStringToHandle(SCOREBOARD_X + 5, SCOREBOARD_Y + 110, "HIGHSCORE", CR_White, font->GetFont_M());
	DrawFormatStringToHandle(SCOREBOARD_X + 10, SCOREBOARD_Y +  50, CR_White, font->GetFont_M(), "%9d", score);
	DrawFormatStringToHandle(SCOREBOARD_X + 10, SCOREBOARD_Y + 160, CR_White, font->GetFont_M(), "%9d", highScore);
}

void CScore::ScoreAdd_Move() {
	score += MOVE_ADDACORE_NUM;
}

void CScore::ScoreAdd_Break(int chain, int line) {
	score += chain * (BREAK_ADDSCORE_NUM * line);
}

void CScore::HighScoreSave() {

	FILE* file;

	fopen_s(&file, "HighScore.dat", "wb");

	if (file == NULL) return;

	fwrite(&highScore, sizeof(highScore), 1, file);
	fclose(file);
}

void CScore::HighScoreLoad() {

	FILE* file;

	fopen_s(&file, "HighScore.dat", "rb");

	if (file == NULL) {
		highScore = 0;
	}else {
		fread(&highScore, sizeof(highScore), 1, file);
		fclose(file);
	}
}