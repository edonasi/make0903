#pragma once

//ゲームのメインヘッダファイル
#include "game.h"

//define
//フォント系
#define FONT_JIYU_PATH		TEXT(".\\Aseets\\Fonts\\Jiyucho.ttf")		//フォントの場所
#define FONT_JIYU_NAME		TEXT("じゆうちょうフォント")	//フォントの名前

#define FONT_DOT_PATH		TEXT(".\\Aseets\\Fonts\\DotGothic16-Regular.ttf")		//フォントの場所
#define FONT_DOT_NAME		TEXT("DotGothic16")				//フォントの名前

#define FONT_REGGAE_PATH		TEXT(".\\Aseets\\Fonts\\ReggaeOne-Regular.ttf")		//フォントの場所
#define FONT_REGGAE_NAME		TEXT("Reggae One")				//フォントの名前

#define FONT_MSGOTH_NAME	TEXT("MS　ゴシック")			//フォント名

#define DEF_FONT_NAME	FONT_JIYU_NAME				//デフォルトのフォント名
#define DEF_FONT_SIZE	20							//デフォルトのサイズ
#define DEF_FONT_THINCK	1							//デフォルトの太さ
#define DEF_FONT_TYPE	DX_FONTTYPE_ANTIALIASING	//デフォルトのタイプ

//エラーメッセージ
#define FONT_INSTALL_ERR_TITLE	TEXT("フォントインストールエラー")
#define FONT_CREATE_ERR_TITLE	TEXT("フォント作成エラー")

//構造体
//フォント構造体
struct FONT
{
	int handle;		//フォントハンドル
	int size;		//フォントのサイズ
	int thinck;		//フォントの太さ
	int type = DX_FONTTYPE_ANTIALIASING;	//フォントのタイプ
	char name[STR_MAX];	//フォントの名前
};

//フォント関連
extern FONT fontdef;
extern FONT sampleFont1;
extern FONT sampleFont2;
extern FONT dotFont;		//ドットのフォント
extern FONT reggaeFont;		//追加のフォント

extern BOOL FontAdd(VOID);		//フォントの読み込み
extern BOOL FontCreate(VOID);	//フォントの作成
extern VOID SetFont(			//フォント設定
	FONT* f, const char* name, int size, int thinck, int type);
extern BOOL FontCreateHandle(FONT* f);	//フォントハンドルを作絵師
extern VOID SetDefaultFont(FONT f);	//フォントを全体に反映させる
extern VOID FontDelete(VOID);			//フォント削除
extern VOID FontRemove(VOID);			//フォント削除