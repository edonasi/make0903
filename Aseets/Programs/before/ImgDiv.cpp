//*--------------------------------------------------------------------------------*
//								分割画像管理クラス
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*

//		CommonUseファイル
#include "IncludeFile.hpp"
//		自身のファイル
#include IMG_DIV_HPP
using namespace n_img_div;

//*--------------------------------------------------------------------------------*
//								コンストラクタ
//*--------------------------------------------------------------------------------*

ClImgDiv::ClImgDiv(){
	m_div = n_xy::XY();
	m_div_max = 0;
	m_cnt = n_cnt::ClCntArySec();
}
ClImgDiv::~ClImgDiv() { return; }

//*--------------------------------------------------------------------------------*
//								プロパティ
//*--------------------------------------------------------------------------------*

/// <summary>
/// 画像を表示/非表示状態にする
/// </summary>
/// <param name="is_draw">TRUEで表示状態</param>
VOID ClImgDiv::SetIsDraw(BOOL is_draw) {
	m_is_draw = is_draw;

	//カウンタを0に戻す
	if (is_draw == FALSE) { m_cnt.SetCnt(); }
}

//*--------------------------------------------------------------------------------*
//								関数
//*--------------------------------------------------------------------------------*

//*------------------------------------------------*
//		画像読み込み
//*------------------------------------------------*

const float DEFALT_ALL_DRAW_TIME = 1.0f;	//分割画像の最大値配列まで加算する時間

//*------------------------------------------------*
//		n_cnt::CNT_AFTER_TYPE cnt_afterなし系列
//*------------------------------------------------*

/// <summary>
/// 画像読み込み(1秒ループ、分割画像全表示)
/// </summary>
/// <param name="path">読み込み場所</param>
/// <param name="div_x">分割する数(横)</param>
/// <param name="div_y">分割する数(縦)</param>
/// <param name="div_max">分割総数</param>
/// <param name="cpp_name">読み込む場所のcpp名(ベタ打ち)</param>
/// <param name="ins_name">読み込むインスタンス名(ベタ打ち)</param>
/// <returns>TRUEで読み込み成功</returns>
BOOL ClImgDiv::Load(string path, int div_x, int div_y, int div_max,
	string cpp_name, string ins_name) {
	//FALSEなら読み込み失敗
	if (MmLoad(
		path, div_x, div_y, div_max,
		div_max, DEFALT_ALL_DRAW_TIME, n_cnt::CNT_AFTER_TYPE::LOOP,
		cpp_name, ins_name) == FALSE
		) {
		return FALSE;
	}

	return TRUE;	//読み込み成功
}

/// <summary>
/// 画像読み込み(1秒ループ、分割画像全表示)
/// </summary>
/// <param name="path">読み込み場所</param>
/// <param name="abs_speed">移動スピード絶対値</param>
/// <param name="div_x">分割する数(横)</param>
/// <param name="div_y">分割する数(縦)</param>
/// <param name="div_max">分割総数</param>
/// <param name="cpp_name">読み込む場所のcpp名(ベタ打ち)</param>
/// <param name="ins_name">読み込むインスタンス名(ベタ打ち)</param>
/// <returns>TRUEで読み込み成功</returns>
BOOL ClImgDiv::Load(string path, int abs_speed,
	int div_x, int div_y, int div_max,
	string cpp_name, string ins_name) {
	//FALSEなら読み込み失敗
	if (MmLoad(
		path, div_x, div_y, div_max,
		div_max, DEFALT_ALL_DRAW_TIME, n_cnt::CNT_AFTER_TYPE::LOOP,
		cpp_name, ins_name) == FALSE
		) {
		return FALSE;
	}

	SetAbsSpeed(abs_speed);		//速度の設定

	return TRUE;	//読み込み成功
}

/// <summary>
/// 画像読み込み(1秒ループ、分割画像全表示)
/// </summary>
/// <param name="path">読み込み場所</param>
/// <param name="abs_speed">移動スピード絶対値</param>
/// <param name="is_draw">描画するか</param>
/// <param name="div_x">分割する数(横)</param>
/// <param name="div_y">分割する数(縦)</param>
/// <param name="div_max">分割総数</param>
/// <param name="cpp_name">読み込む場所のcpp名(ベタ打ち)</param>
/// <param name="ins_name">読み込むインスタンス名(ベタ打ち)</param>
/// <returns>TRUEで読み込み成功</returns>
BOOL ClImgDiv::Load(string path, int abs_speed, BOOL is_draw,
	int div_x, int div_y, int div_max,
	string cpp_name, string ins_name) {
	//FALSEなら読み込み失敗
	if (MmLoad(
		path, div_x, div_y, div_max,
		div_max, DEFALT_ALL_DRAW_TIME, n_cnt::CNT_AFTER_TYPE::LOOP,
		cpp_name, ins_name) == FALSE
		) {
		return FALSE;
	}

	SetAbsSpeed(abs_speed);		//速度の設定
	n_img_div::ClImgDiv::SetIsDraw(is_draw);	//描画するかを設定

	return TRUE;	//読み込み成功
}

/// <summary>
/// 画像読み込み(1秒ループ、分割画像全表示)
/// </summary>
/// <param name="path">読み込み場所</param>
/// <param name="div_x">分割する数(横)</param>
/// <param name="div_y">分割する数(縦)</param>
/// <param name="div_max">分割総数</param>
/// <param name="cpp_name">読み込む場所のcpp名(ベタ打ち)</param>
/// <param name="ins_name">読み込むインスタンス名(ベタ打ち)</param>
/// <param name="is_draw">描画するか</param>
/// <returns>TRUEで読み込み成功</returns>
BOOL ClImgDiv::Load(string path, int div_x, int div_y, int div_max,
	string cpp_name, string ins_name, BOOL is_draw) {
	//FALSEなら読み込み失敗
	if (MmLoad(
		path, div_x, div_y, div_max,
		div_max, DEFALT_ALL_DRAW_TIME, n_cnt::CNT_AFTER_TYPE::LOOP,
		cpp_name, ins_name) == FALSE
		) {
		return FALSE;
	}

	n_img_div::ClImgDiv::SetIsDraw(is_draw);	//描画するかを設定

	return TRUE;	//読み込み成功
}

//*------------------------------------------------*
//		n_cnt::CNT_AFTER_TYPE cnt_afterあり系列
//*------------------------------------------------*

/// <summary>
/// 画像読み込み(1秒指定カウント方法、分割画像全表示)
/// </summary>
/// <param name="path">読み込み場所</param>
/// <param name="div_x">分割する数(横)</param>
/// <param name="div_y">分割する数(縦)</param>
/// <param name="div_max">分割総数</param>
/// <param name="cnt_after">カウントの方法</param>
/// <param name="cpp_name">読み込む場所のcpp名(ベタ打ち)</param>
/// <param name="ins_name">読み込むインスタンス名(ベタ打ち)</param>
/// <returns>TRUEで読み込み成功</returns>
BOOL ClImgDiv::Load(string path, int div_x, int div_y, int div_max,
	n_cnt::CNT_AFTER_TYPE cnt_after,
	string cpp_name, string ins_name) {
	//FALSEなら読み込み失敗
	if (MmLoad(
		path, div_x, div_y, div_max,
		div_max, DEFALT_ALL_DRAW_TIME, cnt_after,
		cpp_name, ins_name) == FALSE
		) {
		return FALSE;
	}

	return TRUE;	//読み込み成功
}

/// <summary>
/// 画像読み込み(1秒指定カウント方法、分割画像全表示)
/// </summary>
/// <param name="path">読み込み場所</param>
/// <param name="abs_speed">移動スピード絶対値</param>
/// <param name="div_x">分割する数(横)</param>
/// <param name="div_y">分割する数(縦)</param>
/// <param name="div_max">分割総数</param>
/// <param name="cnt_after">カウントの方法</param>
/// <param name="cpp_name">読み込む場所のcpp名(ベタ打ち)</param>
/// <param name="ins_name">読み込むインスタンス名(ベタ打ち)</param>
/// <returns>TRUEで読み込み成功</returns>
BOOL ClImgDiv::Load(string path, int abs_speed,
	int div_x, int div_y, int div_max,
	n_cnt::CNT_AFTER_TYPE cnt_after,
	string cpp_name, string ins_name) {
	//FALSEなら読み込み失敗
	if (MmLoad(
		path, div_x, div_y, div_max,
		div_max, DEFALT_ALL_DRAW_TIME, cnt_after,
		cpp_name, ins_name) == FALSE
		) {
		return FALSE;
	}

	SetAbsSpeed(abs_speed);		//速度の設定

	return TRUE;	//読み込み成功
}

/// <summary>
/// 画像読み込み(1秒指定カウント方法、分割画像全表示)
/// </summary>
/// <param name="path">読み込み場所</param>
/// <param name="abs_speed">移動スピード絶対値</param>
/// <param name="is_draw">描画するか</param>
/// <param name="div_x">分割する数(横)</param>
/// <param name="div_y">分割する数(縦)</param>
/// <param name="div_max">分割総数</param>
/// <param name="cnt_after">カウントの方法</param>
/// <param name="cpp_name">読み込む場所のcpp名(ベタ打ち)</param>
/// <param name="ins_name">読み込むインスタンス名(ベタ打ち)</param>
/// <returns>TRUEで読み込み成功</returns>
BOOL ClImgDiv::Load(string path, int abs_speed, BOOL is_draw,
	int div_x, int div_y, int div_max,
	n_cnt::CNT_AFTER_TYPE cnt_after,
	string cpp_name, string ins_name) {
	//FALSEなら読み込み失敗
	if (MmLoad(
		path, div_x, div_y, div_max,
		div_max, DEFALT_ALL_DRAW_TIME, cnt_after,
		cpp_name, ins_name) == FALSE
		) {
		return FALSE;
	}

	SetAbsSpeed(abs_speed);		//速度の設定
	n_img_div::ClImgDiv::SetIsDraw(is_draw);	//描画するかを設定

	return TRUE;	//読み込み成功
}

/// <summary>
/// 画像読み込み(1秒指定カウント方法、分割画像全表示)
/// </summary>
/// <param name="path">読み込み場所</param>
/// <param name="div_x">分割する数(横)</param>
/// <param name="div_y">分割する数(縦)</param>
/// <param name="div_max">分割総数</param>
/// <param name="cnt_after">カウントの方法</param>
/// <param name="cpp_name">読み込む場所のcpp名(ベタ打ち)</param>
/// <param name="ins_name">読み込むインスタンス名(ベタ打ち)</param>
/// <param name="is_draw">描画するか</param>
/// <returns>TRUEで読み込み成功</returns>
BOOL ClImgDiv::Load(string path, int div_x, int div_y, int div_max,
	n_cnt::CNT_AFTER_TYPE cnt_after,
	string cpp_name, string ins_name, BOOL is_draw) {
	//FALSEなら読み込み失敗
	if (MmLoad(
		path, div_x, div_y, div_max,
		div_max, DEFALT_ALL_DRAW_TIME, cnt_after,
		cpp_name, ins_name) == FALSE
		) {
		return FALSE;
	}

	n_img_div::ClImgDiv::SetIsDraw(is_draw);	//描画するかを設定

	return TRUE;	//読み込み成功
}

/// <summary>
/// 画像読み込み共通関数
/// </summary>
/// <param name="path">読み込み場所</param>
/// <param name="div_x">分割する数(横)</param>
/// <param name="div_y">分割する数(縦)</param>
/// <param name="div_max">分割総数</param>
/// <param name="cnt_size">カウントの最大値</param>
/// <param name="all_time">cnt_size枚描画するのにかかる時間(秒)</param>
/// <param name="cnt_after">カウントの方法</param>
/// <param name="cpp_name">cpp名_引数</param>
/// <param name="ins_name">インスタンス名_引数</param>
/// <returns>TRUEで読み込み成功</returns>
BOOL ClImgDiv::MmLoad(string path, int div_x, int div_y, int div_max,
	int cnt_size, float all_time, n_cnt::CNT_AFTER_TYPE cnt_after,
	string cpp_name, string ins_name) {
	//パス
	string all_path = ClCom().GetImagesPath() + path;
	m_path = all_path;						//パスをコピー

	//*------------------------------------------------*

	//単一画像として取得
	int img_handle = ClCom().GetHandleError();
	img_handle = LoadGraph(all_path.c_str());

	//単一画像の読み込みエラー判定
	if (img_handle == ClCom().GetHandleError()) {
		//エラーメッセージ
		string error_meg
			= cpp_name + ".cpp : " + ins_name + " : " + "分割- 元 -画像読み込みエラー";

		MessageBox(
			GetMainWindowHandle(), all_path.c_str(),
			error_meg.c_str(), MB_OK
		);
		return FALSE;	//読み込み失敗
	}

	//単一画像としてサイズを取得
	n_xy::XY img_size = n_xy::XY();
	GetGraphSize(img_handle, &img_size.x, &img_size.y);

	//*------------------------------------------------*

	//vectorの要素を確保
	m_div_handle.resize(div_max);

	//エラー判定用ハンドル
	int load_div_handle = ClCom().GetHandleError();

	//分割画像の読み込み
	load_div_handle = LoadDivGraph(
		all_path.c_str(), div_max, div_x, div_y,
		img_size.x / div_x, img_size.y / div_y, &m_div_handle[0]);

	//分割画像の読み込みエラー判定
	if (load_div_handle == ClCom().GetHandleError()) {
		//エラーメッセージ
		string error_meg
			= cpp_name + ".cpp : " + ins_name + " : " + "分割画像読み込みエラー";

		MessageBox(
			GetMainWindowHandle(), all_path.c_str(),
			error_meg.c_str(), MB_OK
		);
		return FALSE;	//読み込み失敗
	}

	//分割画像の分割数とサイズを取得
	m_div.x = div_x;
	m_div.y = div_y;
	m_div_max = div_max;
	m_size.x = img_size.x / div_x;
	m_size.y = img_size.y / div_y;

	//カウントの設定
	m_cnt.SetCnt(cnt_size, all_time, cnt_after);

	//単一画像ハンドルの役割はなくなるので消去
	DeleteGraph(img_handle);

	return TRUE;	//読み込み成功
}

//*------------------------------------------------*

const int HANDLE_VEC_EMPTY = 0;	//ハンドルのベクターが空のとき

//画像の描画
VOID ClImgDiv::Draw() {
	if (m_is_draw == FALSE) { return; }
	m_cnt.Proc();
	if (m_div_handle.size() == HANDLE_VEC_EMPTY) { return; }
	DrawGraph(m_pos.x, m_pos.y, m_div_handle[m_cnt.GetIndex()], TRUE);
}	

//画像のメモリ消去
VOID ClImgDiv::Delete() {
	for (unsigned int i = 0; i < m_div_handle.size(); i++) {
		DeleteGraph(m_div_handle[i]);
	}
}

//*--------------------------------------------------------------------------------*
//								virtual private移行
//*--------------------------------------------------------------------------------*

BOOL ClImgDiv::Load(string path, string cpp_name, string ins_name) {
	ClCom().VirtualError();
	return FALSE;
}

BOOL ClImgDiv::Load(string path, int abs_speed,
	string cpp_name, string ins_name) {
	ClCom().VirtualError();
	return FALSE;
}

BOOL ClImgDiv::Load(string path, int abs_speed, BOOL is_draw,
	string cpp_name, string ins_name) {
	ClCom().VirtualError();
	return FALSE;
}

BOOL ClImgDiv::Load(string path, string cpp_name, string ins_name, BOOL is_draw) {
	ClCom().VirtualError();
	return FALSE;
}

BOOL ClImgDiv::MmLoad(string path, string cpp_name, string ins_name) {
	ClCom().VirtualError();
	return FALSE;
}