#include "Data.h"
#include "game.h"
#include "shape.h"

/*
http://www.isl.ne.jp/pcsp/beginC/C_Language_16.html
https://9cguide.appspot.com/17-01.html
*/

CHARA_DATA_SAMPLE enemy[ENEMY_MAX];	//敵データ

/// <summary>
/// SCVファイルを読み込む
/// </summary>
/// <param name="path">CSVファイルのパス</param>
/// <param name="chara">キャラデータ構造体の先頭アドレス</param>
/// <param name="dataMax">CSVファイルの最大値</param>
/// <param name="isHeader">CSVファイルの1行目がヘッダならTRUE</param>
/// <returns>TRUEで読み込めた</returns>
BOOL LoadScvChara(const char* path, CHARA_DATA_SAMPLE* chara, int dataMax, BOOL isHeader) 
{
	FILE* fp;					//ファイルポインタ
	char getChar = '\0';		//取得する文字
	int loopCnt = 0;			//ループカウンタ
	errno_t fileErr = NULL;		//ファイル読み込みエラーを確認
	int isEOF = NULL;			//ファイルの終わりかチェック

	fileErr = fopen_s(&fp, path, "r");	//ファイルを読み込みモード(r)で開く
	if (fileErr != NULL) 
	{
		MessageBox(GetMainWindowHandle(), path, CSV_LOAD_ERR_TITLE, MB_OK);	//読み込みエラー
		return FALSE;
	}

	//	↓ここから正常に読み込めた時の処理

	//csvの1行目がヘッダのとき
	if (isHeader == TRUE) 
	{
		//1文字ずつ取り出し、改行をヒントに1行目を読み飛ばす
		while (getChar != '\n') { getChar = fgetc(fp); }
	}

	//実際にデータを格納する
	while (isEOF != EOF)	//ファイルの最後ではないとき繰り返す
	{
		//csvのデータの1行分を読み取る
		//fp = カーソルのイメージ
		isEOF = fscanf_s(
			fp,
			CSV_CHARA_FORMAT,
			&(chara + loopCnt)->no,
			&(chara + loopCnt)->name[0], STR_MAX,
			&(chara + loopCnt)->hp,
			&(chara + loopCnt)->atk,
			&(chara + loopCnt)->def,
			&(chara + loopCnt)->rak,
			&(chara + loopCnt)->hpMax,
			&(chara + loopCnt)->atkMax,
			&(chara + loopCnt)->defMax,
			&(chara + loopCnt)->rakMax
			);

		//次のデータへ
		loopCnt++;
	}

	//データの数が違うとき
	if (loopCnt - 1 != dataMax) 
	{
		MessageBox(GetMainWindowHandle(), path, CSV_DATA_ERR_TITLE, MB_OK);
		return FALSE;
	}

	fclose(fp);	//ファイルを閉じる

	return TRUE;
}