#ifndef SYS_INPUT_H
#define SYS_INPUT_H

namespace {
	const int BUFSIZE = 256;	//キーバッファサイズ
}

//入力関係を管理するクラス
class CInput
{
public:
	CInput() {};
	~CInput() {};
	static CInput* GetInstance();
	int GetKeyAll();
	bool CheckKey(int keyCode) const;
private:
	char keyState[BUFSIZE];	//キー状態保存配列
};

#endif