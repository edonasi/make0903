//*--------------------------------------------------------------------------------*
//								丸
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"
//		自身のファイル
#include CIRCLE_HPP
using namespace n_circle;

//*--------------------------------------------------------------------------------*
//								コンストラクタ
//*--------------------------------------------------------------------------------*

ClCircle::ClCircle(){
	m_center = n_xy::XY();
	m_radius = 0;
}
ClCircle::~ClCircle() { return; }