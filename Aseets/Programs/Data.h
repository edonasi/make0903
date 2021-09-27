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

//エラーメッセージ
#define SCORE_CREATE_ERR_TITLE TEXT("スコアデータ作成エラー")
#define SCORE_LOAD_ERR_TITLE TEXT("スコアデータ読み込みエラー")
#define SCORE_CREATE_TITLE TEXT("スコアデータ作成OK")
#define SCORE_SAVE_TITLE TEXT("スコアデータ保存OK")
#define SCORE_DELETE_TITLE TEXT("スコアデータ削除OK")
#define SCORE_DELETE_ERR_TITLE TEXT("スコアデータ削除エラー")

//スコアデータのパス(拡張子を変なものにすることでチート対策？)
#define SCORE_DATA_PATH TEXT("./Aseets/Data/questionTest")

//データの書式指定子
#define SCORE_DATA_FORMAT TEXT("%[^,],%d,%[^,],%d,%[^,],%d")

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

//スコアデータ構造体(サンプル)
struct SCORE_DATA_SAMPLE
{
	char path[PATH_MAX];	//スコアデータがあるパス

	char name1[STR_MAX];	//名前1
	int score1;				//スコア1

	char name2[STR_MAX];	//名前2
	int score2;				//スコア2

	char name3[STR_MAX];	//名前3
	int score3;				//スコア3
};

//変数
extern CHARA_DATA_SAMPLE enemy[ENEMY_MAX];	//敵データ
extern SCORE_DATA_SAMPLE scoreData;			//スコアデータ
extern SCORE_DATA_SAMPLE scoreDataInit;		//スコアデータ(初期化用)


//関数
extern BOOL LoadScvChara(const char* path, CHARA_DATA_SAMPLE* chara, int dataMax, BOOL isHeader);
extern BOOL LoadScoreData(const char* path, SCORE_DATA_SAMPLE* score, BOOL isHeader);
extern BOOL CreateScoreData(VOID);
extern BOOL SaveScoreData(VOID);
extern BOOL DeleteScoreData(VOID);
extern const char* GetScoreDataPath(VOID);
extern VOID SetScoreDataPath(const char* path);