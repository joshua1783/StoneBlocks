#include <DxLib.h>
#include "Sys_Input.h"

//CInputのコンストラクタ
CInput::CInput(){

	for (int i = 0; i < BUFSIZE; i++){
		keyFrame[i] = 0;
	}
}

//CInputのインスタンスのポインタを返す関数
CInput* CInput::GetInstance(){

	//インスタンス生成
	static CInput *instance = new CInput;

	return instance;
}

//全てのキー状態を取得する関数
int CInput::GetKeyAll() {

	if (GetHitKeyStateAll(keyState) != 0)
		return -1;
	//キーが押されているならば押されている間のフレーム数を加算
	for (int i = 0; i < BUFSIZE; i++) {
		if (keyState[i] != 0) {
			keyFrame[i]++;
		}else {
			keyFrame[i] = 0;
		}
	}

	return 0;
}

//引数のキーの状態を返す関数
int CInput::CheckKey(int keyCode) const {

	if (keyState[keyCode] != 0)
		return keyFrame[keyCode];

	return 0;
}