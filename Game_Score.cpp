#include <DxLib.h>
#include "Common.h"
#include "Game_Score.h"
#include "Sys_Font.h"

//CScore�̃R���X�g���N
CScore::CScore():font(0){
	//�C���X�^���X�擾
	font = CFontHandle::GetInstance();
}

//CScore�̃C���X�^���X�̃|�C���^��Ԃ��֐�
CScore* CScore::GetInstance() {
	//�C���X�^���X����
	static CScore* instance = new CScore;

	return instance;
}

//CScore�̏�Ԑ��ڊ֐�
void CScore::UpData() {
	//�X�R�A�̏���`�F�b�N
	if (score >= SCORE_MAX) score = SCORE_MAX;
	//���݃X�R�A���n�C�X�R�A�𒴂��Ă���Ȃ�΃n�C�X�R�A�X�V
	if (score >= highScore) {
		highScore = score;
		HighScoreSave();
	}
}

//CScore�̕`��֐�
void CScore::Draw() {

	//���݃X�R�A�ƃn�C�X�R�A��\��
	DrawBox(SCOREBOARD_X, SCOREBOARD_Y, SCREEN_WIDTH - MARGIN_WIDTH, SCOREBOARD_Y + 210, CR_Black, TRUE);
	DrawStringToHandle(SCOREBOARD_X + 5, SCOREBOARD_Y +   5, "SCORE", CR_White, font->GetFont_M());
	DrawStringToHandle(SCOREBOARD_X + 5, SCOREBOARD_Y + 110, "HIGHSCORE", CR_White, font->GetFont_M());
	DrawFormatStringToHandle(SCOREBOARD_X + 10, SCOREBOARD_Y +  50, CR_White, font->GetFont_M(), "%9d", score);
	DrawFormatStringToHandle(SCOREBOARD_X + 10, SCOREBOARD_Y + 160, CR_White, font->GetFont_M(), "%9d", highScore);
}

//�Q�[���J�n���̏��������s���֐�
void CScore::SetUp() {	
	score = 0;			//���݃X�R�A������
	HighScoreLoad();	//�n�C�X�R�A�f�[�^���擾
}

//�v���[���[���͂ɂ�闎�����ɃX�R�A�����Z����֐�
void CScore::ScoreAdd_Move() {
	score += MOVE_ADDSCORE_NUM;
}

//�t�B�[���h�u���b�N�������ď��������ɃX�R�A�����Z����֐�
void CScore::ScoreAdd_Break(int chain, int line) {
	//���Z�� = �A���� * 1���C��������̃X�R�A * ���������C����
	score += chain * (BREAK_ADDSCORE_NUM * line);
}

//�n�C�X�R�A���O���t�@�C���ɕۑ�����֐�
void CScore::HighScoreSave() {

	FILE* file;

	//�n�C�X�R�A�f�[�^��"HighScire.dat"�t�@�C���ɕۑ�
	fopen_s(&file, "HighScore.dat", "wb");
	if (file == NULL) return;
	fwrite(&highScore, sizeof(highScore), 1, file);
	fclose(file);
}

//�O���t�@�C������n�C�X�R�A�f�[�^��ǂݍ��ފ֐�
void CScore::HighScoreLoad() {

	FILE* file;

	//�n�C�X�R�A�f�[�^��"HighScore.dat"�t�@�C������ǂݍ���
	fopen_s(&file, "HighScore.dat", "rb");
	if (file == NULL) {
		highScore = 0;
	}else {
		fread(&highScore, sizeof(highScore), 1, file);
		fclose(file);
	}
}