#include <DxLib.h>
#include "Common.h"
#include "SceneBase.h"
#include "Game_Main.h"
#include "Game_Field.h"
#include "Sys_Input.h"
#include "Sys_DataLoader.h"

//CGameのコンストラクタ
CGame::CGame(): input(0), field(0), data(0){

	//インスタンス取得
	input = CInput::GetInstance();
	field = CField::GetInstance();
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
		field->flag_Grid = !field->flag_Grid;

	return next;
}

//ゲームシーン全体の描画関数
void CGame::Draw(CSceneMgr* sceneMgr) {

	DrawGraph(0, 0, data->GetImg_Background_Game(), FALSE);
	field->Draw();
}

