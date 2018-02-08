#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <vector>

#define FIELD_WIDTH 9	//�t�B�[���h�̕�
#define FIELD_HEIGHT 14	//�t�B�[���h�̍���
#define FIRST_LINE_NUM 1	//�Q�[���J�n���̃u���b�N���C����
#define VECTOR_CAPACITY_NUM	10000 //���炩���ߊm�ۂ��Ă����ϒ��z��̗v�f��

using namespace std;

class CDataLoader;

class CField
{
public:
	bool flag_Grid;	//�O���b�h���̕`��t���O
	CField();
	~CField();
	static CField* GetInstance();
	void Draw();
private:
	CDataLoader * data;
	vector<vector<short>> fieldBlocks;
	vector<short> makeNewLine();

};

#endif GAME_FIELD_H
