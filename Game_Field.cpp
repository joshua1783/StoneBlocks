#include <DxLib.h>
#include "Common.h"
#include "Sys_Input.h"
#include "Sys_DataLoader.h"
#include "Game_Field.h"
#include "Gama_ActiveBlock.h"

//CFieldのコンストラクタ
CField::CField() : flag_Grid(false), lineUpTime(0), topDrowLineNow(0), vanishBlocks(), input(0), data(0), newLineBlocks(FIELD_WIDTH, -1) {

	//インスタンス取得
	input = CInput::GetInstance();
	data  = CDataLoader::GetInstance();
	//フィールドブロック初期化
	fieldBlocks.reserve(VECTOR_CAPACITY_NUM);
	fieldBlocks = vector<vector<short>>(FIELD_HEIGHT, vector<short>(FIELD_WIDTH, -1));
	//次のライン生成
	MakeNewLine();
}

//CFieldのインスタンスのポインタを返す関数
CField* CField::GetInstance() {

	//インスタンス生成
	static CField *instance = new CField;

	return instance;
}

//フィールド関係の状態推移関数
void CField::UpData(int* status,int timeNow) {
		
	//Tabキーが押されたらグリッド線表示のフラグ反転
	if (input->CheckKey(KEY_INPUT_TAB) == 1)
		flag_Grid = !flag_Grid;

	//アクティブブロック移動状態時
	if (*status == GS_ActiveBlockMove) {
		lineUpTime += timeNow;
	}
	//フィールドブロックチェック状態時
	else if (*status == GS_CheckFieldBlocks) {
		//ラインアップの時間に達しているならフィールドブロックのラインを上げる
		if (lineUpTime >= LINEUP_TIME_NUM) {
			LineUp();
			lineUpTime = 0;
		}
		count = 0;
		//フィールドブロックに並んでいる物がないかチェック
		*status =  CheckFieldBlocks();				
	}
	//フィールドブロック消去状態時
	else if (*status == GS_VanishFieldBlocks) {
		count += timeNow;
		if (count >= VANISH_TIME_NUM) {
			count = 0;
			//消去フラグの立っているブロックを消去
			//その後空中ブロック落下状態に移行
			VanishFieldBlocks();
			*status = GS_FallBlocks;
		}
	}
	//空中ブロック落下状態時
	else if (*status == GS_FallBlocks) {
		count += timeNow;
		if (count >= FALL_TIME_NUM) {
			count = 0;
			//空中に浮いたブロックの落下
			//浮いたブロックの有無で次の状態移行
			*status = FallBlocks();
		}
	}
	//ゲームオーバーチェック時
	else if (*status == GS_CheckGameOver) {
		//フィールドブロックがゲームオーバー位置に到達していないかチェック
		//チェック結果で次の状態移行
		*status = CheckGameOver();
	}
}

//フィールド関係の描画関数
void CField::Draw() {

	//フィールドの黒枠描画
	DrawBox(MARGIN_WIDTH, MARGIN_HEIGHT, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, FIELD_HEIGHT * BLOCK_SIZE + MARGIN_HEIGHT, CR_Black, TRUE);
	DrawBox(MARGIN_WIDTH, MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 10, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, BLOCK_SIZE + MARGIN_HEIGHT + FIELD_HEIGHT * BLOCK_SIZE + 10, CR_Black, TRUE);
	DrawGraph(BLOCK_SIZE * 4 + MARGIN_WIDTH, MARGIN_HEIGHT, data->GetImg_EndIcon(), TRUE);
	
	//flag_Gridがtrueならばグリッド線描画
	if (flag_Grid == true) {
		for (int i = 1; i < FIELD_HEIGHT; i++) {
			DrawLine(MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, FIELD_WIDTH * BLOCK_SIZE + MARGIN_WIDTH, BLOCK_SIZE * i + MARGIN_HEIGHT, CR_White);
		}
		for (int j = 1; j < FIELD_WIDTH; j++) {
			DrawLine(BLOCK_SIZE * j + MARGIN_WIDTH, MARGIN_HEIGHT, BLOCK_SIZE * j + MARGIN_WIDTH, FIELD_HEIGHT * BLOCK_SIZE + MARGIN_HEIGHT, CR_White);
		}
	}

	//各要素に対応した色のブロック描画
	for (int i = 0; i < FIELD_HEIGHT; i++){
		for (int j = 0; j < FIELD_WIDTH; j++){
			//フィールドのブロック描画
			switch (fieldBlocks[i + topDrowLineNow][j]){
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
			//次のラインのブロック描画
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

//引数座標のフィールド上ブロックの種類を返す関数
int CField::GetFieldBlockType(int x, int y) {
	return fieldBlocks[y + topDrowLineNow][x];
}

//引数座標のブロックが消える予定かどうかを返す関数
int CField::GetVanishBlock(int x, int y) {
	return vanishBlocks[y][x];
}

//落下したアクティブブロックをフィールドブロックに変更する関数
void CField::Active2FieldBlock(int x, int y, short blockType) {
	fieldBlocks[y + topDrowLineNow][x] = blockType;
}

//次に出現するラインのブロックを作成する関数
void CField::MakeNewLine() {		
	for (int i = 0; i < FIELD_WIDTH; i++) {
		newLineBlocks[i] = GetRand(BlockType_Num - 1);
	}
}

//フィールドブロックのラインを増やす関数
void CField::LineUp() {

	//フィールドブロックの末尾に新しいラインを追加
	//フィールドブロックの現在の描画する最大ラインをずらす
	//次の新しいラインブロックを作成
	fieldBlocks.emplace_back(newLineBlocks);
	topDrowLineNow++;
	MakeNewLine();
}

//フィールドブロックに消えるブロックがないかをチェックする関数
int CField::CheckFieldBlocks() {
	
	bool flag_Vanish = false;

	//一時保存用データの初期化
	// 0:空白または消えないブロック
	// 1:消えるブロック
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int j = 0; j < FIELD_WIDTH; j++) {
			vanishBlocks[i][j] = 0;
		}
	}
	//同色のブロックがつながっているかを探索
	for (int i = 0; i < FIELD_HEIGHT; i++){
		for (int j = 0; j < FIELD_WIDTH; j++) {
			//空白ならば次へ
			if (GetFieldBlockType(j, i) == -1)	continue;
			//同色ブロック探索関数へ
			CountSameBlock(j, i);
		}
	}

	//消去フラグが立っているブロックがあればフラグを立てる
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int j = 0; j < FIELD_WIDTH; j++) {
			if (vanishBlocks[i][j] == 1) {
				flag_Vanish = true;
			}
		}
	}

	//一つでも消えるブロックがあったならブロック消去状態に移行
	//そうでなければゲームオーバーでないかをチェック
	if (flag_Vanish == true) {
		return GS_VanishFieldBlocks;
	}else {
		return GS_CheckGameOver;
	}
}

//同じ色のブロックを数える関数
void CField::CountSameBlock(int x, int y) {

	//探索元の色を保存
	int color = GetFieldBlockType(x, y);
	
	//左から右にかけて同色ブロックを探索,指定数以上なら該当ブロックに消去フラグを立てる
	int num = 0;
	for (int i = 0; x + i < FIELD_WIDTH && color == GetFieldBlockType(x + i, y); i++, num++){}
	if (num >= VANISH_MIN_MUN) {
		for (int j = 0; j < num; j++) {
			vanishBlocks[y][x + j] = 1;
		}
	}
	//上から下にかけて同色ブロックを探索,指定数以上なら該当ブロックに消去フラグを立てる
	num = 0;
	for (int i = 0; y + i < FIELD_HEIGHT && color == GetFieldBlockType(x, y + i); i++, num++) {}
	if (num >= VANISH_MIN_MUN) {
		for (int j = 0; j < num; j++) {
			vanishBlocks[y + j][x] = 1;
		}
	}
	//左上から右下にかけて同色ブロックを探索,指定数以上なら該当ブロックに消去フラグを立てる
	num = 0;
	for (int i = 0; x + i < FIELD_WIDTH && y + i < FIELD_HEIGHT && color == GetFieldBlockType(x + i, y + i); i++, num++) {}
	if (num >= VANISH_MIN_MUN) {
		for (int j = 0; j < num; j++) {
			vanishBlocks[y + j][x + j] = 1;
		}
	}
	//右上から左下にかけて同色ブロックを探索,指定数以上なら該当ブロックに消去フラグを立てる
	num = 0;
	for (int i = 0; x - i >= 0 && y + i < FIELD_HEIGHT && color == GetFieldBlockType(x - i, y + i); i++, num++) {}
	if (num >= VANISH_MIN_MUN) {
		for (int j = 0; j < num; j++) {
			vanishBlocks[y + j][x - j] = 1;
		}
	}
}

//消去フラグが経っているブロックを消す
void CField::VanishFieldBlocks() {
		
	//消去フラグが立っているブロックがあれば該当ブロックを消去
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int j = 0; j < FIELD_WIDTH; j++) {
			if (vanishBlocks[i][j] == 1) {
				fieldBlocks[i + topDrowLineNow][j] = -1;
			}
		}
	}
}

//下に空白ができたブロックを落とす関数
int CField::FallBlocks() {

	int line;
	bool flag_Fall = false;

	//フィールド端から探索し浮いたブロックを探索
	for (int j = 0; j < FIELD_WIDTH; j++) {
		for (int i = FIELD_HEIGHT -1; i >= 0; i--){
			//探索ますが空白ならば
			if (GetFieldBlockType(j, i) == -1) {
				//空白は飛ばすかつライン上限ならば次の列へ
				for (line = i - 1; line >= 0 && GetFieldBlockType(j, line) == -1; line--) {};
				if (line < 0) break;
				//ここまできたならば何かしらのブロック有
				//ブロックを1マス落とす
				flag_Fall = true;
				for (line = i + topDrowLineNow; line >= 0; line--){
					if (line - 1 >= 0) 
						fieldBlocks[line][j] = fieldBlocks[line - 1][j];
				}
			}
		}
	}
	
	//落ちるブロックがあったならば落下状態続行
	//なければフィールドブロックチェック状態に移行
	if (flag_Fall == true) {
		return GS_FallBlocks;
	}else {
		return GS_CheckFieldBlocks;
	}
}

//フィールドブロックがゲームオーバー位置に到達しているかチェックする関数
int CField::CheckGameOver() {

	//ゲームオーバー位置が空白でなければゲームオーバー
	if (GetFieldBlockType(FIELD_WIDTH / 2, 0) != -1) {

		if (count < FIELD_HEIGHT) {
			LineUp();
		}else {
			return GS_GameOver;
		}

		count++;

		return GS_CheckGameOver;		
	}
	//空白ならば次のアクティブブロック生成
	count = 0;

	return GS_NewActiveBlock;
}