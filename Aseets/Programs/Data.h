#pragma once

//ゲームのメインヘッダファイル
#include "game.h"

//	マクロ定義
//エラーメッセージ
#define CSV_LOAD_ERR_TITLE TEXT("CSV読み込みエラー")

//キャラクターデータのパス
#define CSV_PATH_ENEMY TEXT("./Aseets/Data/enemy.csv")

//データの書式指定子
//キャラクタの書式指定子(%[^,]は文字列(,が来るまで))
#define CSV_CHARA_FORMAT TEXT("%d,%[^,],%d,%d,%d,%d,%d,%d,%d,%d")

//読み込み数エラーメッセージ
#define CSV_DATA_ERR_TITLE TEXT("CSV数エラー")

//敵データ
#define ENEMY_MAX 8

//キャラデータ構造体(サンプル)
struct CHARA_DATA_SAMPLE
{
	int no;					//番号
	char name[STR_MAX];		//名前

	//実際に使う値
	int hp;					//HP
	int atk;				//攻撃力
	int def;				//防御力
	int rak;				//幸運

	//最大値
	int hpMax;				//最大HP
	int atkMax;				//最大攻撃力
	int defMax;				//最大防御力
	int rakMax;				//最大幸運
};

extern CHARA_DATA_SAMPLE enemy[ENEMY_MAX];

extern BOOL LoadScvChara(const char* path, CHARA_DATA_SAMPLE* chara, int dataMax, BOOL isHeader);