#include <DxLib.h>
#include "Common.h"
#include "SceneBase.h"
#include "Game_Main.h"
#include "Game_Field.h"
#include "Gama_ActiveBlock.h"
#include "Game_Effect.h"
#include "Game_Pause.h"
#include "Game_Score.h"
#include "Sys_Font.h"
#include "Sys_DataLoader.h"

//CGameのコンストラクタ
CGame::CGame(): field(0), block(0), effect(0), pause(0), score(0), data(0), timeNow(0), timeOld(GetNowCount()){

	//インスタンス取得
	field = CField::GetInstance();
	block = CActiveBlock::GetInstance();
	effect = CEffect::GetInstance();
	pause = CPause::GetInstance();
	score = CScore::GetInstance();
	font = CFontHandle::GetInstance();
	data  = CDataLoader::GetInstance();

	//ステータス初期化
	status = GS_SetUp;
}

//CGameのデストラクタ
CGame::~CGame(){
	delete block;
	delete field;
	delete effect;
	delete pause;
	delete score;
}

//ゲームシーンの状態推移関数
CSceneBase* CGame::Updata(CSceneMgr* sceneMgr) {

	//次のシーンを現在のシーン(ゲームシーン)に設定
	CSceneBase* next = this;
	
	//現在時間を取得し,1フレームでの遷移時間を取得
	int time = GetNowCount();
	timeNow = time - timeOld;
	timeOld = time;

	if (status == GS_SetUp) {
		SetUp();
		status = GS_NewActiveBlock;
	}

	//各クラスの状態推移関数
	pause->UpData(&status);
	if (status != GS_Pause) {
		effect->UpData(&status, timeNow);
		block->UpDate(&status, timeNow);
		field->UpData(&status, timeNow);
		score->UpData();
	}
	
	return next;
}

//ゲームシーン全体の描画関数
void CGame::Draw(CSceneMgr* sceneMgr) {

	//背景描画
	DrawGraph(0, 0, data->GetImg_Background_Game(), FALSE);
	//各クラスの描画関数
	field->Draw();
	block->Draw();
	score->Draw();
	if (status == GS_VanishFieldBlocks) 
		effect->Draw();
	if(status == GS_Pause)	
		pause->Draw();

	if (status == GS_GameOver) {
		DrawGraph(10, BLOCK_SIZE * 5 + MARGIN_HEIGHT, data->GetImg_GameOver(), TRUE);
	}
}

//1フレームの遷移時間を返す関数
int CGame::GetTimeNow() {
	return timeNow;
}

//ゲームの初期設定を行う関数
void CGame::SetUp() {

	PlaySoundMem(data->GetSe_Bgm(), DX_PLAYTYPE_LOOP);
}
