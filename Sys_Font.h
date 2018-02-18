#ifndef SYS_FONT_H
#define SYS_FONT_H

//�t�H���g���Ǘ�����N���X
class CFontHandle
{
public:
	CFontHandle();
	~CFontHandle();
	static CFontHandle* GetInstance();
	int GetFont_S();
	int GetFont_M();
	int GetFont_L();
private:
	int fontHandle_S;	//�t�H���g�T�C�YS�̃n���h��
	int fontHandle_M;	//�t�H���g�T�C�YM�̃n���h��
	int fontHandle_L;	//�t�H���g�T�C�YL�̃n���h��
};

#endif // !SYS_FONT_H


