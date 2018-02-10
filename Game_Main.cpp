#include <DxLib.h>
#include "Common.h"
#include "SceneBase.h"
#include "Game_Main.h"
#include "Game_Field.h"
#include "Gama_ActiveBlock.h"
#include "Sys_Input.h"
#include "Sys_DataLoader.h"

//CGameのコンストラクタ
CGame::CGame(): input(0), field(0), block(0), data(0){

	//インスタンス取得
	input = CInput::GetInstance();
	field = CField::GetInstance();
	block = CActiveBlock::GetInstance();
	data  = CDataLoader::GetInstance();

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
	field->UpData();
	block->UpDate();
	
	return next;
}

//ゲームシーン全体の描画関数
void CGame::Draw(CSceneMgr* sceneMgr) {

	DrawGraph(0, 0, data->GetImg_Background_Game(), FALSE);
	field->Draw();
	block->Draw();
}

