#pragma once

namespace n_xy {
	//XYクラス構造体
	class XY{
	public:
		//コンストラクタ
		XY();
		XY(int x_in,int y_in);
		~XY();

		//enum
		//枢軸							
		enum PIVOT {
			TOP_LEFT,		//左上　
			TOP_CENTER,		//　上
			TOP_RIGHT,		//右上
			CENTER_LEFT,	//左
			CENTER_CENTER,	//真ん中
			CENTER_RIGHT,	//右
			BUTTOM_LEFT,	//左下
			BUTTOM_CENTER,	//　下
			BUTTOM_RIGHT	//右下
		};

		enum ONE_PIVOT{
			MIN,	//右/上
			HALF,	//真ん中
			MAX		//左/下
		};

		//		関数
		XY GetPivot();			//左上端を取得
		XY GetPivot(PIVOT pivot);	//指定した枢軸の座標を取得
		//片側のpivot取得
		int GetPivotX(ONE_PIVOT pivot_x);
		int GetPivotY(ONE_PIVOT pivot_y);
		
		//		変数
		int x;
		int y;
	};
}