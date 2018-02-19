#ifndef GAME_SCORE_H
#define GAME_SCORE_H

#define SCOREBOARD_X	   512		 //�X�R�A�{�[�h��x���W
#define SCOREBOARD_Y	   280		 //�X�R�A�{�[�h��y���W
#define SCORE_MAX		   999999999 //�X�R�A�̏��
#define MOVE_ADDSCORE_NUM  1		 //���[�U�[���͂ɂ��ړ��ł̊�{���Z�X�R�A
#define BREAK_ADDSCORE_NUM 100		 //1���C�������������̊�{���Z�X�R�A

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
	CFontHandle * font;	//�t�H���g�֌W�̃C���X�^���X�ۑ��p�|�C���^
	int score;			//���݃X�R�A
	int highScore;		//�n�C�X�R�A
	/*�ȉ�,�֐�*/
	void HighScoreSave();
	void HighScoreLoad();
};

#endif