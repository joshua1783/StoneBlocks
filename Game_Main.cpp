#include <DxLib.h>
#include "Common.h"
#include "SceneBase.h"
#include "Game_Main.h"
#include "Game_Field.h"
#include "Gama_ActiveBlock.h"
#include "Sys_Input.h"
#include "Sys_DataLoader.h"

//CGameのコンストラクタ
CGame::CGame(): input(0), field(0), block(0), data(0), timeNow(0), timeOld(GetNowCount()){

	//インスタンス取得
	input = CInput::GetInstance();
	field = CField::GetInstance();
	block = CActiveBlock::GetInstance();
	data  = CDataLoader::GetInstance();

	//ステータス初期化
	status = GS_NewActiveBlock;
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
	
	//現在時間を取得し,1フレームでの遷移時間を取得
	int time = GetNowCount();
	timeNow = time - timeOld;
	timeOld = time;

	//各クラスの状態推移関数
	block->UpDate(&status, timeNow);
	field->UpData(&status, timeNow);
	printfDx("%d\n", status);
	return next;
}

//ゲームシーン全体の描画関数
void CGame::Draw(CSceneMgr* sceneMgr) {

	DrawGraph(0, 0, data->GetImg_Background_Game(), FALSE);
	//各クラスの描画関数
	field->Draw();
	block->Draw();
}

//1フレームの遷移時間を返す関数
int CGame::GetTimeNow() {

	return timeNow;
}

