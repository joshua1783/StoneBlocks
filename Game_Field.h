#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#define FIELD_WIDTH 9	//フィールドの幅
#define FIELD_HEIGHT 14	//フィールドの高さ

class CField
{
public:
	CField();
	~CField();
private:
	int field[FIELD_HEIGHT][FIELD_WIDTH];
};

#endif GAME_FIELD_H
