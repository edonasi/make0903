//*--------------------------------------------------------------------------------*
//								XY関係管理
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"
//		自身のファイル
#include XY_HPP
using namespace n_xy;

//*--------------------------------------------------------------------------------*
//								コンストラクタ、デストラクタ、変数の初期化
//*--------------------------------------------------------------------------------*

const int POS_MIN = 0;	//座標の最小値

//xy(0,0)で初期化
XY::XY() {
	x = POS_MIN;
	y = POS_MIN;
}
//引数で初期化
XY::XY(int x_in, int y_in) {
	x = x_in;
	y = y_in;
}
XY::~XY() { return; }

//*--------------------------------------------------------------------------------*
//								関数
//*--------------------------------------------------------------------------------*

//左上端(0, 0)を取得
XY XY::GetPivot() {
	XY xy = XY();
	return xy;
}

/// <summary>
/// 指定した枢軸の座標を取得
/// </summary>
/// <param name="pivot"></param>
/// <returns></returns>
XY XY::GetPivot(PIVOT pivot) {
	//左上端の座標
	XY xy = XY();

	//X座標の計算
	switch (pivot){
		//左上端だったら処理終了
	case n_xy::XY::TOP_LEFT:return xy;break;

	case n_xy::XY::TOP_CENTER:
	case n_xy::XY::CENTER_CENTER:
	case n_xy::XY::BUTTOM_CENTER:
		xy.x = x / 2;
		break;

	case n_xy::XY::TOP_RIGHT:
	case n_xy::XY::CENTER_RIGHT:
	case n_xy::XY::BUTTOM_RIGHT:
		xy.x = x;
		break;

	default:break;
	}

	//Y座標の計算
	switch (pivot){
	case n_xy::XY::CENTER_LEFT:
	case n_xy::XY::CENTER_CENTER:
	case n_xy::XY::CENTER_RIGHT:
		xy.y = y / 2;
		break;

	case n_xy::XY::BUTTOM_LEFT:
	case n_xy::XY::BUTTOM_CENTER:
	case n_xy::XY::BUTTOM_RIGHT:
		xy.y = y;
		break;

	default:break;
	}

	return xy;
}



//X座標を取得
int XY::GetPivotX(ONE_PIVOT pivot_x) {
	switch (pivot_x){

	case n_xy::XY::HALF:
		return x / 2;
		break;

	case n_xy::XY::MAX:
		return x;
		break;

	default:
		return POS_MIN;
		break;
	}
}

//Y座標を取得
int XY::GetPivotY(ONE_PIVOT pivot_y) {
	switch (pivot_y){
	case n_xy::XY::HALF:
		return y / 2;
		break;
	case n_xy::XY::MAX:
		return y;
		break;
	default:
		return POS_MIN;
		break;
	}
}