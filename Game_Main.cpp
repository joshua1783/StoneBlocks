#include <DxLib.h>
#include "SceneBase.h"
#include "Game_Main.h"
#include "Sys_DataLoader.h"

//CGameのコンストラクタ
CGame::CGame(): data(0){

	//インスタンス取得
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

	return next;
}

//ゲームシーンの描画関数
void CGame::Draw(CSceneMgr* sceneMgr) {

	DrawGraph(0, 0, data->GetImg_BackgroundGame(), FALSE);
}
