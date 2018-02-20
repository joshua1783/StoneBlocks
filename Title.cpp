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

CSceneBase* CTitle::Updata(CSceneMgr* sceneMgr) {

	//次のシーンを現在のシーン(ゲームシーン)に設定
	CSceneBase* next = this;

	if (status == TS_Start) {
		SetDrawBright(255, 255, 255);
		fade->FadeIn();
		status = TS_FadeIn;
	}else if (status == TS_FadeIn) {
		if (fade->CheckFade() == false)
			status = TS_WaitEnter;
	}else if (status == TS_WaitEnter){
		if (input->CheckKey(KEY_INPUT_RETURN) == 1) {
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
	DrawGraph(SCREEN_WIDTH / 2 - 320, 50, data->GetImg_TitleLogo(), TRUE);
	//DrawStringToHandle(0, 0, "Title", CR_White, font->GetFont_L());

}