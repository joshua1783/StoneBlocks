#include <DxLib.h>
#include "Common.h"
#include "SceneBase.h"
#include "Sys_Font.h"
#include "Sys_Fade.h"
#include "Sys_DataLoader.h"
#include "Game_Main.h"
#include "Game_Effect.h"
#include "Game_Pause.h"
#include "Game_Score.h"
#include "Game_Field.h"
#include "Gama_ActiveBlock.h"
#include "Title.h"

//CGameのコンストラクタ
CGame::CGame(): fade(0), field(0), block(0), effect(0), pause(0), score(0), data(0), timeNow(0), timeOld(GetNowCount()){

	//インスタンス取得
	font = CFontHandle::GetInstance();
	fade = CFade::GetInstance();
	data = CDataLoader::GetInstance();
	effect = CEffect::GetInstance();
	pause = CPause::GetInstance();
	score = CScore::GetInstance();
	field = CField::GetInstance();
	block = CActiveBlock::GetInstance();

	//ステータス初期化
	status = GS_SetUp;
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
	}
	else if (status == GS_FadeIn) {
		if (fade->CheckFade() == false) {
			//BGM再生
			PlaySoundMem(data->GetSe_Bgm(), DX_PLAYTYPE_LOOP);
			status = GS_ActiveBlockMove;
		}
	}

	//各クラスの状態推移関数
	if (status != GS_SetUp || status != GS_FadeIn || status != GS_ReturnTitle) {
		pause->UpData(&status);
		if (status != GS_Pause) {
			effect->UpData(&status, timeNow);
			block->UpDate(&status, timeNow);
			field->UpData(&status, timeNow);
			score->UpData();
		}
	}

	//フェードアウトが終了したらタイトルシーンに移行
	if (status == GS_ReturnTitle) {
		if(fade->CheckFade() == false)
			next = new CTitle;
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
	if (status == GS_VanishFieldBlocks || status == GS_Pause) 
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
	//各種初期設定
	block->SetUp();
	field->SetUp();
	effect->SetUp();
	pause->SetUp();
	score->SetUp();
	fade->FadeIn();
	//フェードイン状態に移行
	status = GS_FadeIn;
}
