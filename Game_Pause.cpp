#include <DxLib.h>
#include "Common.h"
#include "Game_Pause.h"
#include "Sys_Input.h"
#include "Sys_Font.h"

//CPause�̃R���X�g���N
CPause::CPause(): input(0), font(0), saveStatus(0){

	//�C���X�^���X�擾
	input = CInput::GetInstance();
	font = CFontHandle::GetInstance();
	//�I�����j���[�̏�����
	selectNow = PM_ReturnGame;
}


//CPause�̃C���X�^���X�̃|�C���^��Ԃ��֐�
CPause* CPause::GetInstance() {

	//�C���X�^���X����
	static CPause *instance = new CPause;

	return instance;
}

//CPause�̏�Ԑ��ڊ֐�
void CPause::UpData(int* status) {

	//�X�y�[�X�L�[�������ꂽ���̃Q�[����Ԃɂ���ď�������
	if (input->CheckKey(KEY_INPUT_SPACE) == 1) {
		//�Q�[����Ԃ��|�[�Y�łȂ���΃|�[�Y��ԂɈڍs
		if (*status != GS_Pause) {
			saveStatus = *status;
			*status = GS_Pause;
			SetDrawBright(150, 150, 150);
		}
		//�Q�[����Ԃ��|�[�Y�Ȃ�Β��f�����Q�[����ԂɈڍs
		else {
			*status = saveStatus;
			SetDrawBright(255, 255, 255);
		}
	}

	//�|�[�Y���Ȃ�΃��j���[�I������
	if (*status == GS_Pause) *status = PauseNow();
}

//CPause�̕`��֐�
void CPause::Draw() {

	DrawStringToHandle(SCREEN_WIDTH / 5 - 20, 200, "PAUSE", CR_White, font->GetFont_L());
	//�|�[�Y���̃��j���[�͑I�𒆂Ȃ��,�����łȂ���Δ��ŕ\��
	DrawStringToHandle(SCREEN_WIDTH / 5, 350, "�Q�[���ĊJ", selectNow == PM_ReturnGame ? CR_Red : CR_White, font->GetFont_M());
	DrawStringToHandle(SCREEN_WIDTH / 5 - 40, 400, "�^�C�g���ɖ߂�", selectNow == PM_ReturnTitle ? CR_Red : CR_White, font->GetFont_M());

}

//�|�[�Y���̃��j���[�I��������֐�
int CPause::PauseNow() {

	//�オ�����ꂽ��I�����Ă��郁�j���[��1��ɂ��炷
	if (input->CheckKey(KEY_INPUT_W) == 1 || input->CheckKey(KEY_INPUT_UP) == 1) {
		if (selectNow == PM_ReturnGame) {
			selectNow = PM_ReturnTitle;
		}else {
			selectNow--;
		}
	}
	//���������ꂽ��I�����Ă��郁�j���[��1���ɂ��炷
	else if (input->CheckKey(KEY_INPUT_S) == 1 || input->CheckKey(KEY_INPUT_DOWN) == 1) {
		if (selectNow == PM_ReturnTitle) {
			selectNow = PM_ReturnGame;
		}else {
			selectNow++;
		}
	}

	//Enter�L�[�������ꂽ��I�����Ă��郁�j���[�ɂ���ď�������
	if (input->CheckKey(KEY_INPUT_RETURN) == 1 || input->CheckKey(KEY_INPUT_NUMPADENTER == 1)) {
		//�u�Q�[���ɖ߂�v�����Ă�����Ԃɖ߂�
		if (selectNow == PM_ReturnGame) {
			SetDrawBright(255, 255, 255);
			return saveStatus;
		}
		//�u�^�C�g���ɖ߂�v�Ȃ�΃^�C�g����ԂɈڍs
		else if (selectNow == PM_ReturnTitle) {
			SetDrawBright(10, 10, 10);
			return saveStatus;
		}
	}

	return GS_Pause;
}