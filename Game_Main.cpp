#include <DxLib.h>
#include "Common.h"
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

	DrawBackgraound();
}

void CGame::DrawBackgraound() {

	DrawGraph(0, 0, data->GetImg_Background_Game(), FALSE);
	DrawBox(40, 40, 520, 760, CR_Black,TRUE);

	for (int i = 1; i < 10; i++) {
		DrawLine(i * 48 + 40, 40, i * 48 + 40, 760, CR_White);
	}
	for (int j = 1; j < 15; j++) {
		DrawLine(40, j * 48 + 40, 520, j * 48 + 40, CR_White);
	}
	
}
