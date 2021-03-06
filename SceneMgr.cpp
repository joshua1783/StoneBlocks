#include "SceneBase.h"
#include "SceneMgr.h"
#include "Game_Main.h"

//CSceneMgrのコンストラクタ
CSceneMgr::CSceneMgr(){

	//開始シーンの設定
	sceneNow = new CGame;
}

//CSceneMgrのデストラクタ
CSceneMgr::~CSceneMgr(){

	//現在のシーンを削除
	delete sceneNow;
}

//CSceneMgrのインスタンスのポインタを返す関数
CSceneMgr* CSceneMgr::GetInstance() {

	//インスタンス作成
	static CSceneMgr instance;

	return &instance;
}

//シーンの状態推移関数を呼び出す関数
void CSceneMgr::SceneUpdata() {

	//現在のシーンの状態推移関数の呼び出し(通常、返り値は同じシーン)
	sceneNext = sceneNow->Updata(this);

	//次のシーンが異なった場合、シーンを移動
	if (sceneNext != sceneNow) {
		delete sceneNow;
		sceneNow = sceneNext;
	}
}

//シーンの描画関数を呼び出す関数
void CSceneMgr::SceneDraw() {

	//現在のシーンの描画関数の呼び出し
	sceneNow->Draw(this);
}
