#include <DxLib.h>
#include "Common.h"
#include "Sys_Input.h"
#include "Sys_Font.h"
#include "Sys_Fade.h"
#include "Sys_DataLoader.h"
#include "Game_GameOver.h"

CGameOver::CGameOver() : input(0), font(0), fade(0), data(0), selectNow(Continue_Yes){

	input = CInput::GetInstance();
	font = CFontHandle::GetInstance();
	fade = CFade::GetInstance();
	data = CDataLoader::GetInstance();
}

CGameOver* CGameOver::GetInstance() {

	static CGameOver* instance = new CGameOver;

	return instance;
}

void CGameOver::UpData(int* status) {

	//�R���e�j���[���ڂ̑I��
	*status = ContinueSelect();
}

void CGameOver::Draw() {
	DrawBox(BLOCK_SIZE * 1 + MARGIN_WIDTH, BLOCK_SIZE * 5 + MARGIN_HEIGHT, BLOCK_SIZE * 8 + MARGIN_WIDTH, BLOCK_SIZE * 12 + MARGIN_HEIGHT, CR_Black, TRUE);
	DrawStringToHandle(130 + MARGIN_WIDTH, BLOCK_SIZE * 5 + MARGIN_HEIGHT + 50, "CONTINUE?", CR_White, font->GetFont_M());
	//�I�𒆂Ȃ��,�����łȂ���Δ��ŕ\��
	DrawStringToHandle(180 + MARGIN_WIDTH, BLOCK_SIZE * 8 + MARGIN_HEIGHT, "Yes", selectNow == Continue_Yes ? CR_Red : CR_White, font->GetFont_M());
	DrawStringToHandle(190 + MARGIN_WIDTH, BLOCK_SIZE * 9 + MARGIN_HEIGHT, "No", selectNow == Continue_No ? CR_Red : CR_White, font->GetFont_M());
	DrawGraph(10, BLOCK_SIZE * 1 + MARGIN_HEIGHT, data->GetImg_GameOver(), TRUE);
}

//�R���e�j���[�̃��j���[�I��������֐�
int CGameOver::ContinueSelect() {

	//�オ�����ꂽ��I�����Ă��郁�j���[��1��ɂ��炷
	if (input->CheckKey(KEY_INPUT_W) == 1 || input->CheckKey(KEY_INPUT_UP) == 1) {
		PlaySoundMem(data->GetSe_Select(), DX_PLAYTYPE_BACK);
		if (selectNow == Continue_Yes) {
			selectNow = Continue_No;
		}
		else {
			selectNow--;
		}
	}
	//���������ꂽ��I�����Ă��郁�j���[��1���ɂ��炷
	else if (input->CheckKey(KEY_INPUT_S) == 1 || input->CheckKey(KEY_INPUT_DOWN) == 1) {
		PlaySoundMem(data->GetSe_Select(), DX_PLAYTYPE_BACK);
		if (selectNow == Continue_No) {
			selectNow = Continue_Yes;
		}
		else {
			selectNow++;
		}
	}

	//Enter�L�[�������ꂽ��I�����Ă��鍀�ڂɂ���ď�������
	if (input->CheckKey(KEY_INPUT_RETURN) == 1 || input->CheckKey(KEY_INPUT_NUMPADENTER == 1)) {
		PlaySoundMem(data->GetSe_Enter(), DX_PLAYTYPE_BACK);
		StopSoundMem(data->GetSe_Bgm());
		fade->FadeOut();
		//�uYes�v�Ȃ�΃Q�[����蒼��
		if (selectNow == Continue_Yes) {
			return GS_Continue;
		}
		//�uNo�v�Ȃ�΃^�C�g����ԂɈڍs
		else if (selectNow == Continue_No) {
			return GS_FadeOut;
		}
	}

	return GS_GameOver;
}