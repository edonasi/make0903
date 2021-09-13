//ヘッダファイル読み込み
#include "Font.h"
#include "game.h"

/*
■フォントを一時的にインストール

　■ハンドルでフォントを管理

　↓

　■ハンドルを解放

■フォントを一時的にアンインストール
*/

//グローバル変数
FONT fontdef;		//デフォルトのフォント
FONT sampleFont1;	//サンプルのフォント
FONT sampleFont2;	//サンプルのフォント(読み込み)
FONT dotFont;
FONT reggaeFont;

/// <summary>
/// フォントの読み込み
/// </summary>
/// <param name=""></param>
/// <returns></returns>
BOOL FontAdd(VOID) 
{
	//フォントを一時的に読み込み(WinApi)
	if (AddFontResourceEx(FONT_JIYU_PATH, FR_PRIVATE, NULL) == 0)
	{
		//エラーメッセージ
		MessageBox(
			GetMainWindowHandle(),
			FONT_JIYU_NAME,
			FONT_INSTALL_ERR_TITLE,
			MB_OK
		);

		return FALSE;
	}

	//フォントを一時的に読み込み(WinApi)
	if (AddFontResourceEx(FONT_DOT_PATH, FR_PRIVATE, NULL) == 0)
	{
		//エラーメッセージ
		MessageBox(
			GetMainWindowHandle(),
			FONT_DOT_NAME,
			FONT_INSTALL_ERR_TITLE,
			MB_OK
		);

		return FALSE;
	}

	//フォントを一時的に読み込み(WinApi)
	if (AddFontResourceEx(FONT_REGGAE_PATH, FR_PRIVATE, NULL) == 0)
	{
		//エラーメッセージ
		MessageBox(
			GetMainWindowHandle(),
			FONT_REGGAE_NAME,
			FONT_INSTALL_ERR_TITLE,
			MB_OK
		);

		return FALSE;
	}

	//読み込み成功
	return TRUE;
}

//フォントの作成
BOOL FontCreate(VOID) 
{
	//デフォルトのフォントの情報を初期化
	SetFont(
		&fontdef,			//設定するフォント
		DEF_FONT_NAME,		//フォントの名前をコピー
		DEF_FONT_SIZE,		//フォントのサイズ
		DEF_FONT_THINCK,	//フォントの太さ
		DEF_FONT_TYPE		//フォントのタイプ
	);

	//デフォルトフォントのハンドルを作成
	if (FontCreateHandle(&fontdef) == FALSE) { return FALSE; }

	//デフォルトフォントを全体に反映
	SetDefaultFont(fontdef);

	//サンプルフォントの情報を設定
	SetFont(
		&sampleFont1,
		FONT_MSGOTH_NAME,
		32,
		5,
		DX_FONTTYPE_ANTIALIASING
	);

	//サンプルフォントのハンドルを作成
	if (FontCreateHandle(&sampleFont1) == FALSE) { return FALSE; }

	//サンプルフォントの情報を設定
	SetFont(
		&sampleFont2,
		FONT_JIYU_NAME,
		64,
		1,
		DX_FONTTYPE_ANTIALIASING
	);

	//サンプルフォントのハンドルを作成
	if (FontCreateHandle(&sampleFont2) == FALSE) { return FALSE; }

	//ドットサンプルフォントの情報を設定
	SetFont(
		&dotFont,
		FONT_DOT_NAME,
		32,
		1,
		DX_FONTTYPE_ANTIALIASING
	);

	//ドットサンプルフォントのハンドルを作成
	if (FontCreateHandle(&dotFont) == FALSE) { return FALSE; }

	//ドットサンプルフォントの情報を設定
	SetFont(
		&reggaeFont,
		FONT_REGGAE_NAME,
		32,
		1,
		DX_FONTTYPE_ANTIALIASING
	);

	//ドットサンプルフォントのハンドルを作成
	if (FontCreateHandle(&reggaeFont) == FALSE) { return FALSE; }

	return TRUE;
}

/// <summary>
/// 引数のフォント構造体へ設定する
/// </summary>
/// <param name="f">設定するフォント構造体</param>
/// <param name="name">フォント名</param>
/// <param name="size">フォントのサイズ</param>
/// <param name="thinck">フォントの太さ</param>
/// <param name="type">フォントのタイプ</param>
VOID SetFont(FONT* f, const char* name, int size, int thinck, int type) 
{
	strcpy_sDx(f->name, STR_MAX, name);	//名前
	f->size = size;						//サイズ
	f->thinck = thinck;					//太さ
	f->type = type;						//タイプ
	return;
}

/// <summary>
/// フォントハンドルを作成
/// </summary>
/// <param name="f">フォント構造体</param>
/// <returns></returns>
BOOL FontCreateHandle(FONT* f) 
{
	//※CreateFontToHandleはDXライブラリの関数
	f->handle = CreateFontToHandle(
		f->name,
		f->size,
		f->thinck,
		f->type
	);

	//ハンドルが読み込まれないなら失敗
	if (f->handle == -1) { return FALSE; }

	return TRUE;
}

/// <summary>
/// フォントを全体に反映させる
/// </summary>
/// <param name="f">設定するフォント構造体</param>
VOID SetDefaultFont(FONT f) 
{
	ChangeFont(f.name);	//名前	//※ChangeFontDXライブラリの関数で重い処理
	SetFontSize(f.size);		//サイズ
	SetFontThickness(f.thinck);	//太さ
	ChangeFontType(f.type);		//タイプ
}

//フォント削除
VOID FontDelete(VOID) 
{
	DeleteFontToHandle(fontdef.handle);

	DeleteFontToHandle(sampleFont1.handle);
	DeleteFontToHandle(sampleFont2.handle);
}

//ウィンドウに入っていない読み込んだフォント削除
VOID FontRemove(VOID) 
{
	//一時的に読み込んだフォントを削除(WinApi)
	RemoveFontResourceEx(FONT_JIYU_PATH, FR_PRIVATE, NULL);
	RemoveFontResourceEx(FONT_DOT_PATH, FR_PRIVATE, NULL);
	RemoveFontResourceEx(FONT_REGGAE_PATH, FR_PRIVATE, NULL);
}