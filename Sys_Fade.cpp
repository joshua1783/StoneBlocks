#include <DxLib.h>
#include "Common.h"
#include "Sys_Fade.h"

CFade::CFade(): rate(0.0), flag_Fade(false), flag_FadeType(false){
}

CFade* CFade::GetInstance() {

	static CFade* instance = new CFade;

	return instance;
}

void CFade::UpData() {

	if (flag_Fade == true) {
		if (ParamChange(flag_FadeType ? 0.0f : 1.0f))
			flag_Fade = false; 
	}
}

void CFade::Draw() {

	int alpha = (int)(rate * 255.0f);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, CR_Black, TRUE);
}

void CFade::FadeIn() {
	rate = 1.0f;
	flag_Fade = true;
	flag_FadeType = true;
}

void CFade::FadeOut() {
	rate = 0.0f;
	flag_Fade = true;
	flag_FadeType = false;
}

bool CFade::CheckFade() {
	return flag_Fade;
}

bool CFade::ParamChange(float target) {

	if (rate < target) {
		rate += SPEED;
		if (rate >= target) {
			rate = target;
			return true;
		}
	}else if (rate > target) {
		rate -= SPEED;
		if (rate <= target) {
			rate = target;
			return true;
		}
	}

	return false;

}