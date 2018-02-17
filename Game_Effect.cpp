#include <DxLib.h>
#include "Common.h"
#include "Sys_DataLoader.h"
#include "Game_Field.h"
#include "Game_Effect.h"

CEffect::CEffect() : field(0), data(0), count(0), num(0) {

	//インスタンス取得
	field = CField::GetInstance();
	data = CDataLoader::GetInstance();
}

CEffect* CEffect::GetInstance() {

	//インスタンス生成
	static CEffect *instance = new CEffect;

	return instance;
}

void CEffect::UpData(int* status, int timeNow) {
	if (*status == GS_VanishFieldBlocks) {
		count += timeNow;
		if (count >= EFFECT_FLAME_TIME_NUM) {
			num++;
			count = 0;
			if (num > EFFECT_BREAK_NUM) {
				num = 0;
			}
		}
	}else {
		count = 0;
		num = 0;
	}
}

void CEffect::Draw() {	
	for (int i = 0; i < FIELD_HEIGHT; i++){
		for (int j = 0; j < FIELD_WIDTH; j++) {
			if (field->GetVanishBlock(j, i) == 1) {
				switch (field->GetFieldBlockType(j, i)) {
				case BlockType_Red:
					DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, data->GetImg_EffectRed(num), TRUE);
					break;
				case BlockType_Blue:
					DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, data->GetImg_EffectBlue(num), TRUE);
					break;
				case BlockType_Green:
					DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, data->GetImg_EffectGreen(num), TRUE);
					break;
				case BlockType_Yellow:
					DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, data->GetImg_EffectYellow(num), TRUE);
					break;
				default:
					break;
				}
			}
		}
	}
}