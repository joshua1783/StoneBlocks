#include <DxLib.h>
#include "Common.h"
#include "Sys_DataLoader.h"
#include "Game_Effect.h"
#include "Game_Field.h"

//CEffectnod�̃R���X�g���N�^
CEffect::CEffect() : field(0), data(0), count(0), num(0) {

	//�C���X�^���X�擾
	data = CDataLoader::GetInstance();
	field = CField::GetInstance();
}

//CEffectnod�̃C���X�^���X�̃|�C���^��Ԃ��֐�
CEffect* CEffect::GetInstance() {

	//�C���X�^���X����
	static CEffect *instance = new CEffect;

	return instance;
}

//CEffect�̏�Ԑ��ڊ֐�
void CEffect::UpData(int* status, int timeNow) {

	//�u���b�N������ԂȂ�ΗP�\���Ԃ��ƂɃt���[���������Z
	//����ȊO�Ȃ�Εϐ�������
	if (*status == GS_VanishFieldBlocks) {
		count += timeNow;
		if (count >= EFFECT_FLAME_TIME_NUM) {
			if (num == 0) PlaySoundMem(data->GetSe_Break(), DX_PLAYTYPE_BACK);
			num++;
			count = 0;
			if (num > EFFECT_BREAK_NUM) {
				num = 0;
			}
		}
	}else {
		count = 0;
		num   = 0;
	}
}

//CEffect�̕`��֐�
void CEffect::Draw() {

	for (int i = 0; i < FIELD_HEIGHT; i++){
		for (int j = 0; j < FIELD_WIDTH; j++) {
			//������u���b�N������Ȃ�Y�����W�ɃG�t�F�N�g�`��
			if (field->GetVanishBlock(j, i) == 1) {
				switch (field->GetFieldBlockType(j, i)) {
				case BlockType_Red:
					DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, data->GetImg_EffectRed(num), TRUE);
					break;
				case BlockType_Blue:
					DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, data->GetImg_EffectBlue(num), TRUE);
					break;
				case BlockType_Green:
					DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, data->GetImg_EffectGreen(num), TRUE);
					break;
				case BlockType_Yellow:
					DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, data->GetImg_EffectYellow(num), TRUE);
					break;
				default:
					break;
				}
			}
		}
	}
}

//�Q�[���J�n���̏��������s���֐�
void CEffect::SetUp() {
	count = 0;	//�ėp�ϐ��̏�����
	num = 0;	//���݃t���[����������
}