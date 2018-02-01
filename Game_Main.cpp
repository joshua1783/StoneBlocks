#include <DxLib.h>
#include "Common.h"
#include "SceneBase.h"
#include "Game_Main.h"
#include "Game_Field.h"
#include "Sys_Input.h"
#include "Sys_DataLoader.h"

//CGameのコンストラクタ
CGame::CGame(): input(0), data(0), flag_Grid(false){

	//インスタンス取得
	input = CInput::GetInstance();
	data = CDataLoader::GetInstance();

	//素材読み込み
	data->Load();

}

//CGameのデストラクタ
CGame::~CGame(){
}

//ゲームシーンの状態推移関数
CSceneBase* CGame::Updata(CSceneMgr* sceneMgr) {

	//次のシーンを現在のシーン(ゲームシーン)に設定
	CSceneBase* next = this;

	//Tabキーが押されたらグリッド線表示のフラグ反転
	if (input->CheckKey(KEY_INPUT_TAB) == 1)
		flag_Grid = !flag_Grid;

	return next;
}

//ゲームシーンの描画関数
void CGame::Draw(CSceneMgr* sceneMgr) {

	DrawBackgraound();
}

//背景の描画関数
void CGame::DrawBackgraound() {

	DrawGraph(0, 0, data->GetImg_Background_Game(), FALSE);
	DrawBox(MARGIN_WIDTH, MARGIN_HEIGHT, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, FIELD_HEIGHT * BLOCK_SIZE + MARGIN_HEIGHT, CR_Black,TRUE);
	//フラグがtrueならばグリッド線描画
	if (flag_Grid == true) {
		for (int i = 1; i < FIELD_WIDTH; i++) {
			DrawLine(i * BLOCK_SIZE + MARGIN_WIDTH, MARGIN_HEIGHT, i * BLOCK_SIZE + MARGIN_WIDTH, FIELD_HEIGHT * BLOCK_SIZE + MARGIN_HEIGHT, CR_White);
		}
		for (int j = 1; j < FIELD_HEIGHT; j++) {
			DrawLine(MARGIN_WIDTH, j * BLOCK_SIZE + MARGIN_HEIGHT, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, j * BLOCK_SIZE + MARGIN_HEIGHT, CR_White);
		}
	}	
}
