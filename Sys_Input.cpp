#include <DxLib.h>
#include "Sys_Input.h"

//Cinputのインスタンスのポインタを返す関数
CInput* CInput::GetInstance() {

	//インスタンス生成
	static CInput instance;

	return &instance;
}

//全てのキー状態を取得する関数
int CInput::GetKeyAll() {

	return GetHitKeyStateAll(keyState);
}

//引数のキーの状態を返す関数
bool CInput::CheckKey(int keyCode) const {

	if (keyState[keyCode] != 0)
		return true;

	return false;
}