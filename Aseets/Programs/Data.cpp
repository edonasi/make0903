#include "Data.h"
#include "game.h"
#include "shape.h"

/*
http://www.isl.ne.jp/pcsp/beginC/C_Language_16.html
https://9cguide.appspot.com/17-01.html
*/

CHARA_DATA_SAMPLE enemy[ENEMY_MAX];	//敵データ
SCORE_DATA_SAMPLE scoreData;			//スコアデータ
SCORE_DATA_SAMPLE scoreDataInit;		//スコアデータ(初期化用)

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

/// <summary>
/// スコアデータを読み込む
/// </summary>
/// <param name="path">スコアデータのパス</param>
/// <param name="chara">スコアデータ構造体の先頭アドレス</param>
/// <param name="isHeader">CSVファイルの1行目がヘッダならTRUE</param>
/// <returns>TRUEで読み取り成功</returns>
BOOL LoadScoreData(const char* path, SCORE_DATA_SAMPLE* score, BOOL isHeader = FALSE) 
{
	FILE* fp;					//ファイルポインタ
	char getChar = '\0';		//取得する文字
	errno_t fileErr = NULL;		//ファイル読み込みエラーを確認
	int isEOF = NULL;			//ファイルの終わりかチェック

	SetScoreDataPath(path);		//パスのコピー

	fileErr = fopen_s(&fp, path, "r");	//ファイルを読み込みモード(r)で開く
	if (fileErr != NULL)
	{
		//スコアデータの作成
		if (CreateScoreData() == FALSE) { return FALSE; }

		//ここまでの処理でスコアデータは必ず作られる

		fileErr = fopen_s(&fp, path, "r");
		if (fileErr != NULL)
		{
			MessageBox(GetMainWindowHandle(), path, SCORE_LOAD_ERR_TITLE, MB_OK);	//読み込みエラー
			return FALSE;
		}
	}

	//	↓ここから正常に読み込めた時の処理

	//csvの1行目がヘッダのとき
	if (isHeader == TRUE)
	{
		//1文字ずつ取り出し、改行をヒントに1行目を読み飛ばす
		while (getChar != '\n') { getChar = fgetc(fp); }
	}

	//実際にデータを格納する
	isEOF = fscanf_s(
		fp,
		SCORE_DATA_FORMAT,	//データが「一行=レコード」で書かれているのがポイント！
		&(score)->name1, STR_MAX,	//文字列を読み込むときは、次の引数で文字列最大数を指定する
		&(score)->score1,
		&(score)->name2, STR_MAX,	//文字列を読み込むときは、次の引数で文字列最大数を指定する
		&(score)->score2,
		&(score)->name3, STR_MAX,	//文字列を読み込むときは、次の引数で文字列最大数を指定する
		&(score)->score3
	);

	fclose(fp);	//ファイルを閉じる

	return TRUE;
}

//スコアデータ作成
BOOL CreateScoreData(VOID) 
{
	//無かったらスコアデータを作る
	FILE* creFp;
	errno_t creFileErr = NULL;	//ファイル読み込みエラーを確認

	//ファイルを書き込みモードで開く(作成する)
	creFileErr = fopen_s(&creFp, GetScoreDataPath(), "w");
	if (creFileErr != NULL) 
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_CREATE_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//ヘッダを書き込み
	fprintf_s(
		creFp, "Name1,Score1,Name2,Score2,Name3,Score3\n"
	);

	//空のスコアデータを書き込み
	fprintf_s(
		creFp, "%s,%d,%s,%d,%s,%d",
		scoreDataInit.name1, scoreDataInit.score1,
		scoreDataInit.name2, scoreDataInit.score2,
		scoreDataInit.name3, scoreDataInit.score3
	);

	//スコアデータを閉じる
	fclose(creFp);

	MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_CREATE_TITLE, MB_OK);
	return TRUE;
}

//スコアデータ保存
BOOL SaveScoreData(VOID) 
{
	//無かったらスコアデータを作る
	FILE* creFp;
	errno_t creFileErr = NULL;	//ファイル読み込みエラーを確認

	//ファイルを書き込みモードで開く(作成する)
	creFileErr = fopen_s(&creFp, GetScoreDataPath(), "w");
	if (creFileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_CREATE_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//ヘッダを書き込み
	fprintf_s(
		creFp, "Name1,Score1,Name2,Score2,Name3,Score3\n"
	);

	//空のスコアデータを書き込み
	fprintf_s(
		creFp, "%s,%d,%s,%d,%s,%d",
		scoreData.name1, scoreData.score1,
		scoreData.name2, scoreData.score2,
		scoreData.name3, scoreData.score3
	);

	//スコアデータを閉じる
	fclose(creFp);

	MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_SAVE_TITLE, MB_OK);
	return TRUE;
}

//スコアデータ削除
BOOL DeleteScoreData(VOID) 
{
//ファイル削除
	if (remove(GetScoreDataPath()) != 0)
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_DELETE_ERR_TITLE, MB_OK);
	}
	else 
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_DELETE_TITLE, MB_OK);
	}

	//スコアデータ作成
	return CreateScoreData();
}

//スコアデータのパスを返す
const char* GetScoreDataPath(VOID) 
{
	return scoreData.path;
}

/// <summary>
/// スコアデータのパスを設定する
/// </summary>
/// <param name="path"></param>
VOID SetScoreDataPath(const char* path) 
{
	strcpyDx(scoreData.path, path);
	return;
}