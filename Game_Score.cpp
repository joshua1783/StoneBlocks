#include <DxLib.h>
#include "Common.h"
#include "Game_Score.h"
#include "Sys_Font.h"

//CScoreのコンストラク
CScore::CScore():font(0){
	//インスタンス取得
	font = CFontHandle::GetInstance();
}

//CScoreのインスタンスのポインタを返す関数
CScore* CScore::GetInstance() {
	//インスタンス生成
	static CScore* instance = new CScore;

	return instance;
}

//CScoreの状態推移関数
void CScore::UpData() {
	//スコアの上限チェック
	if (score >= SCORE_MAX) score = SCORE_MAX;
	//現在スコアがハイスコアを超えているならばハイスコア更新
	if (score >= highScore) {
		highScore = score;
		HighScoreSave();
	}
}

//CScoreの描画関数
void CScore::Draw() {

	//現在スコアとハイスコアを表示
	DrawBox(SCOREBOARD_X, SCOREBOARD_Y, SCREEN_WIDTH - MARGIN_WIDTH, SCOREBOARD_Y + 210, CR_Black, TRUE);
	DrawStringToHandle(SCOREBOARD_X + 5, SCOREBOARD_Y +   5, "SCORE", CR_White, font->GetFont_M());
	DrawStringToHandle(SCOREBOARD_X + 5, SCOREBOARD_Y + 110, "HIGHSCORE", CR_White, font->GetFont_M());
	DrawFormatStringToHandle(SCOREBOARD_X + 10, SCOREBOARD_Y +  50, CR_White, font->GetFont_M(), "%9d", score);
	DrawFormatStringToHandle(SCOREBOARD_X + 10, SCOREBOARD_Y + 160, CR_White, font->GetFont_M(), "%9d", highScore);
}

//ゲーム開始時の初期化を行う関数
void CScore::SetUp() {	
	score = 0;			//現在スコア初期化
	HighScoreLoad();	//ハイスコアデータを取得
}

//プレーヤー入力による落下時にスコアを加算する関数
void CScore::ScoreAdd_Move() {
	score += MOVE_ADDSCORE_NUM;
}

//フィールドブロックが揃って消えた時にスコアを加算する関数
void CScore::ScoreAdd_Break(int chain, int line) {
	//加算量 = 連鎖数 * 1ライン当たりのスコア * 消えたライン数
	score += chain * (BREAK_ADDSCORE_NUM * line);
}

//ハイスコアを外部ファイルに保存する関数
void CScore::HighScoreSave() {

	FILE* file;

	//ハイスコアデータを"HighScire.dat"ファイルに保存
	fopen_s(&file, "HighScore.dat", "wb");
	if (file == NULL) return;
	fwrite(&highScore, sizeof(highScore), 1, file);
	fclose(file);
}

//外部ファイルからハイスコアデータを読み込む関数
void CScore::HighScoreLoad() {

	FILE* file;

	//ハイスコアデータを"HighScore.dat"ファイルから読み込む
	fopen_s(&file, "HighScore.dat", "rb");
	if (file == NULL) {
		highScore = 0;
	}else {
		fread(&highScore, sizeof(highScore), 1, file);
		fclose(file);
	}
}