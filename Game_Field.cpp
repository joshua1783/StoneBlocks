#include <DxLib.h>
#include "Common.h"
#include "Sys_Input.h"
#include "Sys_DataLoader.h"
#include "Game_Score.h"
#include "Game_Field.h"
#include "Gama_ActiveBlock.h"

//CField�̃R���X�g���N�^
CField::CField() :vanishBlocks(), score(0), input(0), data(0), newLineBlocks(FIELD_WIDTH, -1) {

	//�C���X�^���X�擾
	score = CScore::GetInstance();
	input = CInput::GetInstance();
	data  = CDataLoader::GetInstance();
	//�t�B�[���h�u���b�N�p�̃����������炩���ߊm��
	fieldBlocks.reserve(VECTOR_CAPACITY_NUM);
}

//CField�̃C���X�^���X�̃|�C���^��Ԃ��֐�
CField* CField::GetInstance() {

	//�C���X�^���X����
	static CField *instance = new CField;

	return instance;
}

//�t�B�[���h�֌W�̏�Ԑ��ڊ֐�
void CField::UpData(int* status,int timeNow) {
	
	//Tab�L�[�������ꂽ��O���b�h���\���̃t���O���]
	if (input->CheckKey(KEY_INPUT_TAB) == 1)
		flag_Grid = !flag_Grid;

	//�A�N�e�B�u�u���b�N�ړ���Ԏ�
	if (*status == GS_ActiveBlockMove) {
		lineUpTime += timeNow;
	}
	//�t�B�[���h�u���b�N�`�F�b�N��Ԏ�
	else if (*status == GS_CheckFieldBlocks) {
		//���C���A�b�v�̎��ԂɒB���Ă���Ȃ�t�B�[���h�u���b�N�̃��C�����グ��
		if (lineUpTime >= LINEUP_TIME_NUM) {
			LineUp();
			lineUpTime = 0;
		}
		count = 0;
		//�t�B�[���h�u���b�N�ɕ���ł��镨���Ȃ����`�F�b�N
		*status =  CheckFieldBlocks();				
	}
	//�t�B�[���h�u���b�N������Ԏ�
	else if (*status == GS_VanishFieldBlocks) {
		count += timeNow;
		if (count >= VANISH_TIME_NUM) {
			count = 0;
			//�����t���O�̗����Ă���u���b�N������
			//���̌�󒆃u���b�N������ԂɈڍs
			VanishFieldBlocks();
			*status = GS_FallBlocks;
		}
	}
	//�󒆃u���b�N������Ԏ�
	else if (*status == GS_FallBlocks) {
		count += timeNow;
		if (count >= FALL_TIME_NUM) {
			count = 0;
			//�󒆂ɕ������u���b�N�̗���
			//�������u���b�N�̗L���Ŏ��̏�Ԉڍs
			*status = FallBlocks();
		}
	}
	//�Q�[���I�[�o�[�`�F�b�N��
	else if (*status == GS_CheckGameOver) {
		//�t�B�[���h�u���b�N���Q�[���I�[�o�[�ʒu�ɓ��B���Ă��Ȃ����`�F�b�N
		//�`�F�b�N���ʂŎ��̏�Ԉڍs
		*status = CheckGameOver();
	}
}

//�t�B�[���h�֌W�̕`��֐�
void CField::Draw() {

	//�t�B�[���h�̍��g�`��
	DrawBox(MARGIN_WIDTH, MARGIN_HEIGHT, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, FIELD_HEIGHT * BLOCK_SIZE + MARGIN_HEIGHT, CR_Black, TRUE);
	DrawBox(MARGIN_WIDTH, MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 10, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, BLOCK_SIZE + MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 10, CR_Black, TRUE);
	DrawGraph(BLOCK_SIZE * 4 + MARGIN_WIDTH, MARGIN_HEIGHT, data->GetImg_EndIcon(), TRUE);
	
	//flag_Grid��true�Ȃ�΃O���b�h���`��
	if (flag_Grid == true) {
		for (int i = 1; i < FIELD_HEIGHT; i++) {
			DrawLine(MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, CR_White);
		}
		for (int j = 1; j < FIELD_WIDTH; j++) {
			DrawLine(BLOCK_SIZE * j + MARGIN_WIDTH, MARGIN_HEIGHT, BLOCK_SIZE * j + MARGIN_WIDTH, FIELD_HEIGHT * BLOCK_SIZE + MARGIN_HEIGHT, CR_White);
		}
	}

	//�e�v�f�ɑΉ������F�̃u���b�N�`��
	for (int i = 0; i < FIELD_HEIGHT; i++){
		for (int j = 0; j < FIELD_WIDTH; j++){
			//�t�B�[���h�̃u���b�N�`��
			switch (fieldBlocks[i + topDrawLineNow][j]){
				case BlockType_Red:
					DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, data->GetImg_BlockRed(), TRUE);
					break;
				case BlockType_Blue:
					DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, data->GetImg_BlockBlue(), TRUE);
					break;
				case BlockType_Green:
					DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, data->GetImg_BlockGreen(), TRUE);
					break;
				case BlockType_Yellow:
					DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, data->GetImg_BlockYellow(), TRUE);
					break;
				default:
					break;
			}
			//���̃��C���̃u���b�N�`��
			switch (newLineBlocks[j]) {
			case BlockType_Red:
				DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 10, data->GetImg_BlockRed(), TRUE);
				break;
			case BlockType_Blue:
				DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 10, data->GetImg_BlockBlue(), TRUE);
				break;
			case BlockType_Green:
				DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 10, data->GetImg_BlockGreen(), TRUE);
				break;
			case BlockType_Yellow:
				DrawGraph(BLOCK_SIZE * j + MARGIN_WIDTH, MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 10, data->GetImg_BlockYellow(), TRUE);
				break;
			default:
				break;
			}
		}
	}
}

//�Q�[���J�n���̏��������s���֐�
void CField::SetUp() {
	flag_Grid = false;	//�O���b�h���`��t���O������
	count = 0;			//�ėp�ϐ�������
	chain = 1;			//�A����������
	lineUpTime = 0;		//���C���㏸���ԏ�����
	topDrawLineNow = 0; //�`�������C��������

	//�t�B�[���h�u���b�N�̒������K���蒷���ꍇ��,�K��ȏ�̗v�f�͍폜
	//�t�B�[���h�u���b�N�̒��g���󔒂ŏ�����
	if (fieldBlocks.size() > FIELD_HEIGHT) {
		fieldBlocks.erase(fieldBlocks.begin() + FIELD_HEIGHT, fieldBlocks.end());
	}
	fieldBlocks = vector<vector<short>>(FIELD_HEIGHT, vector<short>(FIELD_WIDTH, -1));
	//���̃��C������
	MakeNewLine();
}

//�������W�̃t�B�[���h��u���b�N�̎�ނ�Ԃ��֐�
int CField::GetFieldBlockType(int x, int y) {
	return fieldBlocks[y + topDrawLineNow][x];
}

//�������W�̃u���b�N��������\�肩�ǂ�����Ԃ��֐�
int CField::GetVanishBlock(int x, int y) {
	return vanishBlocks[y][x];
}

//���������A�N�e�B�u�u���b�N���t�B�[���h�u���b�N�ɕύX����֐�
void CField::Active2FieldBlock(int x, int y, short blockType) {
	fieldBlocks[y + topDrawLineNow][x] = blockType;
}

//���ɏo�����郉�C���̃u���b�N���쐬����֐�
void CField::MakeNewLine() {		
	for (int i = 0; i < FIELD_WIDTH; i++) {
		newLineBlocks[i] = GetRand(BlockType_Num - 1);
	}
}

//�t�B�[���h�u���b�N�̃��C���𑝂₷�֐�
void CField::LineUp() {

	//�t�B�[���h�u���b�N�̖����ɐV�������C����ǉ�
	//�t�B�[���h�u���b�N�̌��݂̕`�悷��ő僉�C�������炷
	//���̐V�������C���u���b�N���쐬
	fieldBlocks.emplace_back(newLineBlocks);
	topDrawLineNow++;
	MakeNewLine();
}

//�t�B�[���h�u���b�N�ɏ�����u���b�N���Ȃ������`�F�b�N����֐�
int CField::CheckFieldBlocks() {
	
	bool flag_Vanish = false;

	//�ꎞ�ۑ��p�f�[�^�̏�����
	// 0:�󔒂܂��͏����Ȃ��u���b�N
	// 1:������u���b�N
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int j = 0; j < FIELD_WIDTH; j++) {
			vanishBlocks[i][j] = 0;
		}
	}
	//���F�̃u���b�N���Ȃ����Ă��邩��T��
	for (int i = 0; i < FIELD_HEIGHT; i++){
		for (int j = 0; j < FIELD_WIDTH; j++) {
			//�󔒂Ȃ�Ύ���
			if (GetFieldBlockType(j, i) == -1)	continue;
			//���F�u���b�N�T���֐���
			CountSameBlock(j, i, chain);
		}
	}

	//�����t���O�������Ă���u���b�N������΃t���O�𗧂Ă�
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int j = 0; j < FIELD_WIDTH; j++) {
			if (vanishBlocks[i][j] == 1) {
				flag_Vanish = true;
			}
		}
	}

	//��ł�������u���b�N���������Ȃ�u���b�N������ԂɈڍs
	//�����łȂ���΃Q�[���I�[�o�[�łȂ������`�F�b�N
	if (flag_Vanish == true) {
		chain++;
		return GS_VanishFieldBlocks;
	}else {
		chain = 1;
		return GS_CheckGameOver;
	}
}

//�����F�̃u���b�N�𐔂���֐�
void CField::CountSameBlock(int x, int y, int chain) {

	//�T�����̐F��ۑ�
	//�X�R�A�p�ɏ��������C�����ۑ�
	int color = GetFieldBlockType(x, y);
	int vanishLine = 0;
	
	//������E�ɂ����ē��F�u���b�N��T��,�w�萔�ȏ�Ȃ�Y���u���b�N�ɏ����t���O�𗧂Ă�
	int num = 0;
	for (int i = 0; x + i < FIELD_WIDTH && color == GetFieldBlockType(x + i, y); i++, num++){}
	if (num >= VANISH_MIN_MUN) {
		if (num == 3) vanishLine++;
		for (int j = 0; j < num; j++) {
			vanishBlocks[y][x + j] = 1;
		}
	}
	//�ォ�牺�ɂ����ē��F�u���b�N��T��,�w�萔�ȏ�Ȃ�Y���u���b�N�ɏ����t���O�𗧂Ă�
	num = 0;
	for (int i = 0; y + i < FIELD_HEIGHT && color == GetFieldBlockType(x, y + i); i++, num++) {}
	if (num >= VANISH_MIN_MUN) {
		if (num == 3) vanishLine++;
		for (int j = 0; j < num; j++) {
			vanishBlocks[y + j][x] = 1;
		}
	}
	//���ォ��E���ɂ����ē��F�u���b�N��T��,�w�萔�ȏ�Ȃ�Y���u���b�N�ɏ����t���O�𗧂Ă�
	num = 0;
	for (int i = 0; x + i < FIELD_WIDTH && y + i < FIELD_HEIGHT && color == GetFieldBlockType(x + i, y + i); i++, num++) {}
	if (num >= VANISH_MIN_MUN) {
		if (num == 3) vanishLine++;
		for (int j = 0; j < num; j++) {
			vanishBlocks[y + j][x + j] = 1;
		}
	}
	//�E�ォ�獶���ɂ����ē��F�u���b�N��T��,�w�萔�ȏ�Ȃ�Y���u���b�N�ɏ����t���O�𗧂Ă�
	num = 0;
	for (int i = 0; x - i >= 0 && y + i < FIELD_HEIGHT && color == GetFieldBlockType(x - i, y + i); i++, num++) {}
	if (num >= VANISH_MIN_MUN) {
		if (num == 3) vanishLine++;
		for (int j = 0; j < num; j++) {
			vanishBlocks[y + j][x - j] = 1;
		}
	}
	//�X�R�A���Z
	score->ScoreAdd_Break(chain, vanishLine);
}

//�����t���O���o���Ă���u���b�N������
void CField::VanishFieldBlocks() {
		
	//�����t���O�������Ă���u���b�N������ΊY���u���b�N������
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int j = 0; j < FIELD_WIDTH; j++) {
			if (vanishBlocks[i][j] == 1) {
				fieldBlocks[i + topDrawLineNow][j] = -1;
			}
		}
	}
}

//���ɋ󔒂��ł����u���b�N�𗎂Ƃ��֐�
int CField::FallBlocks() {

	int line;
	bool flag_Fall = false;

	//�t�B�[���h�[����T�����������u���b�N��T��
	for (int j = 0; j < FIELD_WIDTH; j++) {
		for (int i = FIELD_HEIGHT -1; i >= 0; i--){
			//�T���܂����󔒂Ȃ��
			if (GetFieldBlockType(j, i) == -1) {
				//�󔒂͔�΂������C������Ȃ�Ύ��̗��
				for (line = i - 1; line >= 0 && GetFieldBlockType(j, line) == -1; line--) {};
				if (line < 0) break;
				//�����܂ł����Ȃ�Ή�������̃u���b�N�L
				//�u���b�N��1�}�X���Ƃ�
				flag_Fall = true;
				for (line = i + topDrawLineNow; line >= 0; line--){
					if (line - 1 >= 0) 
						fieldBlocks[line][j] = fieldBlocks[line - 1][j];
				}
			}
		}
	}
	
	//������u���b�N���������Ȃ�Η�����ԑ��s
	//�Ȃ���΃t�B�[���h�u���b�N�`�F�b�N��ԂɈڍs
	if (flag_Fall == true) {
		return GS_FallBlocks;
	}else {
		return GS_CheckFieldBlocks;
	}
}

//�t�B�[���h�u���b�N���Q�[���I�[�o�[�ʒu�ɓ��B���Ă��邩�`�F�b�N����֐�
int CField::CheckGameOver() {

	//�Q�[���I�[�o�[�ʒu���󔒂łȂ���΃Q�[���I�[�o�[
	if (GetFieldBlockType(FIELD_WIDTH / 2, 0) != -1) {

		if (count < FIELD_HEIGHT) {
			LineUp();
		}else {
			return GS_GameOver;
		}

		count++;

		return GS_CheckGameOver;		
	}
	//�󔒂Ȃ�Ύ��̃A�N�e�B�u�u���b�N����
	count = 0;

	return GS_NewActiveBlock;
}