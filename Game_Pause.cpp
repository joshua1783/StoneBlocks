#include <DxLib.h>
#include "Common.h"
#include "Game_Pause.h"
#include "Sys_Input.h"
#include "Sys_Font.h"

//CPauseのコンストラク
CPause::CPause(): input(0), font(0), saveStatus(0){

	//インスタンス取得
	input = CInput::GetInstance();
	font = CFontHandle::GetInstance();
	//選択メニューの初期化
	selectNow = PM_ReturnGame;
}


//CPauseのインスタンスのポインタを返す関数
CPause* CPause::GetInstance() {

	//インスタンス生成
	static CPause *instance = new CPause;

	return instance;
}

//CPauseの状態推移関数
void CPause::UpData(int* status) {

	//スペースキーが押された時のゲーム状態によって処理分岐
	if (input->CheckKey(KEY_INPUT_SPACE) == 1) {
		//ゲーム状態がポーズでなければポーズ状態に移行
		if (*status != GS_Pause) {
			saveStatus = *status;
			*status = GS_Pause;
			SetDrawBright(150, 150, 150);
		}
		//ゲーム状態がポーズならば中断したゲーム状態に移行
		else {
			*status = saveStatus;
			SetDrawBright(255, 255, 255);
		}
	}

	//ポーズ中ならばメニュー選択処理
	if (*status == GS_Pause) *status = PauseNow();
}

//CPauseの描画関数
void CPause::Draw() {

	DrawStringToHandle(SCREEN_WIDTH / 5 - 20, 200, "PAUSE", CR_White, font->GetFont_L());
	//ポーズ中のメニューは選択中なら赤,そうでなければ白で表示
	DrawStringToHandle(SCREEN_WIDTH / 5, 350, "ゲーム再開", selectNow == PM_ReturnGame ? CR_Red : CR_White, font->GetFont_M());
	DrawStringToHandle(SCREEN_WIDTH / 5 - 40, 400, "タイトルに戻る", selectNow == PM_ReturnTitle ? CR_Red : CR_White, font->GetFont_M());

}

//ポーズ中のメニュー選択をする関数
int CPause::PauseNow() {

	//上が押されたら選択しているメニューを1つ上にずらす
	if (input->CheckKey(KEY_INPUT_W) == 1 || input->CheckKey(KEY_INPUT_UP) == 1) {
		if (selectNow == PM_ReturnGame) {
			selectNow = PM_ReturnTitle;
		}else {
			selectNow--;
		}
	}
	//下が押されたら選択しているメニューを1つ下にずらす
	else if (input->CheckKey(KEY_INPUT_S) == 1 || input->CheckKey(KEY_INPUT_DOWN) == 1) {
		if (selectNow == PM_ReturnTitle) {
			selectNow = PM_ReturnGame;
		}else {
			selectNow++;
		}
	}

	//Enterキーが押されたら選択しているメニューによって処理分岐
	if (input->CheckKey(KEY_INPUT_RETURN) == 1 || input->CheckKey(KEY_INPUT_NUMPADENTER == 1)) {
		//「ゲームに戻る」存していた状態に戻る
		if (selectNow == PM_ReturnGame) {
			SetDrawBright(255, 255, 255);
			return saveStatus;
		}
		//「タイトルに戻る」ならばタイトル状態に移行
		else if (selectNow == PM_ReturnTitle) {
			SetDrawBright(10, 10, 10);
			return saveStatus;
		}
	}

	return GS_Pause;
}