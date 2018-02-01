#include <DxLib.h>
#include "Game_Field.h"

CField::CField(){

	for (int i = 0; i < FIELD_WIDTH; i++){
		for (int j = 0; j < FIELD_HEIGHT; j++){
			field[j][i] = 0;
		}
	}
}

CField::~CField(){
}
