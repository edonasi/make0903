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

/// <summary>
/// マップcsvファイルを読み込む
/// </summary>
/// <param name="imgPath">マップチップ画像ファイルのパス</param>
/// <param name="downPath">下レイヤーファイルのパス</param>
/// <param name="centerPath">中レイヤーのファイルのパス</param>
/// <param name="centerColliderPath">中当たり判定レイヤーのファイルパス</param>
/// <param name="upPath">上レイヤーのファイルパス</param>
/// <param name="map">マップデータ構造体の先頭アドレス</param>
/// <param name="divX">横の分割数</param>
/// <param name="divY">縦の分割数</param>
/// <returns></returns>
BOOL LoadCsvMap(const char* imgPath,
	const char* downPath, const char* centerPath, const char* centerColliderPath, const char* upPath,
	MAP_DATA_SAMPLE* map, int divYoko, int divTate) {
	//マップチップの読み込み
	int isLoad = -1;

	//一時的に画像のハンドルを用意する
	int tempHandle = LoadGraph(imgPath);

	//読み込みエラー
	if (tempHandle == -1) {
		MessageBox(
			GetMainWindowHandle(),
			imgPath,
			"画像読み込みエラー",
			MB_OK
		);
		return FALSE;
	}

	//画像の幅と高さを取得
	int width = -1;
	int height = -1;
	GetGraphSize(tempHandle, &width, &height);

	//分割して読み込み
	isLoad = LoadDivGraph(
		imgPath,
		divYoko * divTate,
		divYoko, divTate,
		width / divYoko, height / divTate,
		map->handle
	);

	//分割エラー
	if (isLoad == -1) {
		MessageBox(
			GetMainWindowHandle(),
			imgPath,
			"画像分割エラー",
			MB_OK
		);

		return FALSE;
	}

	//情報を設定
	map->divMax = divYoko * divTate;
	GetGraphSize(map->handle[0], &map->width, &map->height);

	//画像を描画する
	map->isDraw = TRUE;

	//一時的に読み込んだハンドルを解放
	DeleteGraph(tempHandle);

	//==========================================

	FILE* fp;					//ファイルポインタ
	char getChar = '\0';		//取得する文字
	int loopCnt = 0;			//ループカウンタ
	errno_t fileErr = NULL;		//ファイル読み込みエラーを確認
	int isEOF = NULL;			//ファイルの終わりかチェック

	//下CSV読み込み==========================================

	fileErr = fopen_s(&fp, downPath, "r");	//ファイルを読み込みモード(r)で開く
	if (fileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), downPath, CSV_LOAD_ERR_TITLE, MB_OK);	//読み込みエラー
		return FALSE;
	}

	//	↓ここから正常に読み込めた時の処理

	loopCnt = 0;			//ループカウンタ
	isEOF = NULL;		//ファイル読み込みエラーを確認

	//実際にデータを格納する
	while (isEOF != EOF)	//ファイルの最後ではないとき繰り返す
	{
		//csvのデータの1行分を読み取る
		//fp = カーソルのイメージ
		isEOF = fscanf_s(
			fp,
			CSV_MAP_FORMAT,
			&map->csvDown[loopCnt / MAP1_YOKO_MAX][loopCnt % MAP1_YOKO_MAX]
		);

		//次のデータへ
		loopCnt++;
	}

	fclose(fp);	//ファイルを閉じる

	//中CSV読み込み==========================================

	fileErr = fopen_s(&fp, centerPath, "r");	//ファイルを読み込みモード(r)で開く
	if (fileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), centerPath, CSV_LOAD_ERR_TITLE, MB_OK);	//読み込みエラー
		return FALSE;
	}

	//	↓ここから正常に読み込めた時の処理

	loopCnt = 0;			//ループカウンタ
	isEOF = NULL;		//ファイル読み込みエラーを確認

	//実際にデータを格納する
	while (isEOF != EOF)	//ファイルの最後ではないとき繰り返す
	{
		//csvのデータの1行分を読み取る
		//fp = カーソルのイメージ
		isEOF = fscanf_s(
			fp,
			CSV_MAP_FORMAT,
			&map->csvCenter[loopCnt / MAP1_YOKO_MAX][loopCnt % MAP1_YOKO_MAX]
		);

		//次のデータへ
		loopCnt++;
	}

	fclose(fp);	//ファイルを閉じる

	//中当たり判定CSV読み込み==========================================

	fileErr = fopen_s(&fp, centerColliderPath, "r");	//ファイルを読み込みモード(r)で開く
	if (fileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), centerColliderPath, CSV_LOAD_ERR_TITLE, MB_OK);	//読み込みエラー
		return FALSE;
	}

	//	↓ここから正常に読み込めた時の処理

	loopCnt = 0;			//ループカウンタ
	isEOF = NULL;		//ファイル読み込みエラーを確認

	//実際にデータを格納する
	while (isEOF != EOF)	//ファイルの最後ではないとき繰り返す
	{
		//csvのデータの1行分を読み取る
		//fp = カーソルのイメージ
		isEOF = fscanf_s(
			fp,
			CSV_MAP_FORMAT,
			&map->csvCenterCollider[loopCnt / MAP1_YOKO_MAX][loopCnt % MAP1_YOKO_MAX]
		);

		//次のデータへ
		loopCnt++;
	}

	fclose(fp);	//ファイルを閉じる

	//上CSV読み込み==========================================

	fileErr = fopen_s(&fp, upPath, "r");	//ファイルを読み込みモード(r)で開く
	if (fileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), upPath, CSV_LOAD_ERR_TITLE, MB_OK);	//読み込みエラー
		return FALSE;
	}

	//	↓ここから正常に読み込めた時の処理

	loopCnt = 0;			//ループカウンタ
	isEOF = NULL;		//ファイル読み込みエラーを確認

	//実際にデータを格納する
	while (isEOF != EOF)	//ファイルの最後ではないとき繰り返す
	{
		//csvのデータの1行分を読み取る
		//fp = カーソルのイメージ
		isEOF = fscanf_s(
			fp,
			CSV_MAP_FORMAT,
			&map->csvUp[loopCnt / MAP1_YOKO_MAX][loopCnt % MAP1_YOKO_MAX]
		);

		//次のデータへ
		loopCnt++;
	}

	fclose(fp);	//ファイルを閉じる

	//マップの当たり判定を作成
	for (int y = 0; y < MAP1_TATE_MAX; y++) {
		for (int x = 0; x < MAP1_YOKO_MAX; x++) {
			if (map->csvCenterCollider[y][x] == MAP_STOP_ID) {
			//当たり判定を作成
				map->coll[y][x].left = (x + 0) * map->width + 1;
				map->coll[y][x].right = (x + 1) * map->width - 1;
				map->coll[y][x].top = (y + 0) * map->height + 1;
				map->coll[y][x].bottom = (y + 1) * map->height - 1;
			}
			else {
				map->coll[y][x].left = 	  0;
				map->coll[y][x].right =	  0;
				map->coll[y][x].top = 	  0;
				map->coll[y][x].bottom=   0;
			}

			//マップの場所を設定
			map->x[y][x] = (x + 0) * map->width;
			map->y[y][x] = (y + 0) * map->height;
		}
	}

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

BOOL CollMap(RECT rect, MAP_DATA_SAMPLE map) {
	for (int y = 0; y < MAP1_TATE_MAX; y++) {
		for (int x = 0; x < MAP1_YOKO_MAX; x++) {
			if (CheckCollRectToRect(rect, map.coll[y][x]) == TRUE) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

VOID DrawMap(MAP_DATA_SAMPLE map) {
	//マップが描画できるときは
	if (map.isDraw == TRUE) {
		//下レイヤー描画
		for (int y = 0; y < MAP1_TATE_MAX; y++) {
			for (int x = 0; x < MAP1_YOKO_MAX; x++) {
				//描画
				DrawGraph(
					map.x[y][x],
					map.y[y][x],
					map.handle[map.csvDown[y][x]], TRUE
					//&map->csvDown[loopCnt / MAP1_YOKO_MAX][loopCnt % MAP1_YOKO_MAX]
				);
				
			}
		}

		//中レイヤーの描画描画
		for (int y = 0; y < MAP1_TATE_MAX; y++) {
			for (int x = 0; x < MAP1_YOKO_MAX; x++) {
				//描画
				DrawGraph(
					map.x[y][x],
					map.y[y][x],
					map.handle[map.csvCenter[y][x]], TRUE
				);
			}
		}

		//プレイヤーの画像を描画する
		DrawDivImageChara(&samplePlayerImg);

		//上レイヤーの描画
		for (int y = 0; y < MAP1_TATE_MAX; y++) {
			for (int x = 0; x < MAP1_YOKO_MAX; x++) {
				//描画
				DrawGraph(
					map.x[y][x],
					map.y[y][x],
					map.handle[map.csvUp[y][x]], TRUE
				);
			}
		}

		//デバックモードではないときここで処理終了
		if (GAME_DEBUG == FALSE) { return; }

		//当たり判定を描画
		for (int y = 0; y < MAP1_TATE_MAX; y++) {
			for (int x = 0; x < MAP1_YOKO_MAX; x++) {
				//描画
				DrawRect(map.coll[y][x], GetColor(255, 255, 255), FALSE);
			}
		}
	}
	return;
}