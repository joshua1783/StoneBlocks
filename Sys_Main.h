#ifndef SYS_MAIN_H
#define SYS_MAIN_H

//�t�H���g�n���h��
enum FontHandle {
	FontHandle_S,
	FontHandle_M,
	FontHandle_L,

	FontHandle_Num
};

//�V�X�e���֌W���Ǘ�����N���X
class CSystem
{
public:
	CSystem();
	~CSystem() {};
	static CSystem* GetInstance();
	int GetFontHandle(int fontSize) const;
private:
	int fontHandle[FontHandle_Num];
};

#endif