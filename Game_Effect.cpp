#include <DxLib.h>
#include "Common.h"
#include "Sys_DataLoader.h"
#include "Game_Effect.h"
#include "Game_Field.h"

//CEffectnodのコンストラクタ
CEffect::CEffect() : field(0), data(0), count(0), num(0) {

	//インスタンス取得
	data = CDataLoader::GetInstance();
	field = CField::GetInstance();
}

//CEffectnodのインスタンスのポインタを返す関数
CEffect* CEffect::GetInstance() {

	//インスタンス生成
	static CEffect *instance = new CEffect;

	return instance;
}

//CEffectの状態推移関数
void CEffect::UpData(int* status, int timeNow) {

	//ブロック消去状態ならば猶予時間ごとにフレーム数を加算
	//それ以外ならば変数初期化
	if (*status == GS_VanishFieldBlocks) {
		count += timeNow;
		if (count >= EFFECT_FLAME_TIME_NUM) {
			if (num == 0) PlaySoundMem(data->GetSe_Break(), DX_PLAYTYPE_BACK);
			num++;
			count = 0;
			if (num > EFFECT_BREAK_NUM) {
				num = 0;
			}
		}
	}else {
		count = 0;
		num   = 0;
	}
}

//CEffectの描画関数
void CEffect::Draw() {

	for (int i = 0; i < FIELD_HEIGHT; i++){
		for (int j = 0; j < FIELD_WIDTH; j++) {
			//消えるブロックがあるなら該当座標にエフェクト描画
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

//ゲーム開始時の初期化を行う関数
void CEffect::SetUp() {
	count = 0;	//汎用変数の初期化
	num = 0;	//現在フレーム数初期化
}