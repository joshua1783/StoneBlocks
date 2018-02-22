#include <DxLib.h>
#include "Common.h"
#include "SceneBase.h"
#include "Sys_Input.h"
#include "Sys_Fade.h"
#include "Sys_Font.h"
#include "Sys_DataLoader.h"
#include "Title.h"
#include "Game_Main.h"


CTitle::CTitle():input(0), fade(0), font(0), data(0){

	input = CInput::GetInstance();
	fade = CFade::GetInstance();
	font = CFontHandle::GetInstance();
	data = CDataLoader::GetInstance();

	//タイトルステータス初期化
	status = TS_Start;
}

CSceneBase* CTitle::Updata(CSceneMgr* sceneMgr, int timeNow) {

	//次のシーンを現在のシーン(ゲームシーン)に設定
	CSceneBase* next = this;

	if (status == TS_Start) {
		SetDrawBright(255, 255, 255);
		fade->FadeIn();
		status = TS_FadeIn;
	}else if (status == TS_FadeIn) {
		if (fade->CheckFade() == false) {
			PlaySoundMem(data->GetSe_Bgm(), DX_PLAYTYPE_LOOP);
			status = TS_WaitEnter;
		}
	}else if (status == TS_WaitEnter){
		if (input->CheckKey(KEY_INPUT_RETURN) == 1) {
			PlaySoundMem(data->GetSe_Enter(), DX_PLAYTYPE_BACK);
			StopSoundMem(data->GetSe_Bgm());
			fade->FadeOut();
			status = TS_FadeOut;
		}
	}else if (status == TS_FadeOut) {
		if (fade->CheckFade() == false)
			next = new CGame;
	}

	return next;
}

void CTitle::Draw(CSceneMgr* sceneMgr) {
	DrawGraph(0, 0, data->GetImg_Background_Game(), FALSE);
	DrawGraph(SCREEN_WIDTH / 2 - 330, 50, data->GetImg_TitleLogo(), TRUE);
	DrawStringToHandle(SCREEN_WIDTH / 2 - 170, 550, "Please press Enter\n  to start Game", CR_Black, font->GetFont_M());

}