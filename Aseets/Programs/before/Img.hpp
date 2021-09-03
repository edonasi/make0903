#pragma once
//インクルードファイル
#include XY_HPP	//XYやPIVOTなど

namespace n_img {

	//画像管理の基底クラス
	class ClImg
	{
		//*----------------------------------------------------------------------------*
		//							publicここから
		//*----------------------------------------------------------------------------*

	public:
		//		コンストラクタ、デストラクタ、変数の初期化
		ClImg();
		~ClImg();

		//		enum
		//移動方向
		enum MOVE_LINE_TYPE {
			UP_LEFT,	//左上　
			UP,			//　上
			UP_RIGHT,	//右上
			LEFT,		//左
			STOP,		//停止
			RIGHT,		//右
			DOWN_LEFT,	//左下
			DOWN,		//　下
			DOWN_RIGHT	//右下
		};

		//移動する時、移動方向係数以外でどの変数を係数にするか					
		enum MOVE_MULT {
			ABS_SPEED,	//m_abs_speedの変数を係数として移動(deltaは関係なし)
			DELTA		//m_abs_speedの変数を係数としてdeltaをかけて移動
		};

		//		プロパティ
		virtual VOID SetIsDraw(BOOL is_draw);		//描画するかしないか
		VOID SetAbsSpeed(int abs_speed);			//正の値のスピードを設定

		//		関数
		//画像読み込み
		virtual BOOL Load(string path, string cpp_name, string ins_name);
		virtual BOOL Load(string path, int abs_speed,
			string cpp_name, string ins_name);
		virtual BOOL Load(string path, int abs_speed, BOOL is_draw,
			string cpp_name, string ins_name);
		virtual BOOL Load(
			string path, string cpp_name, string ins_name, BOOL is_draw);

		//
		virtual VOID Draw();		//透過描画
		virtual VOID Delete();		//画像メモリ消去

		//		移動
		VOID Move(int x_mult, int y_mult);		//画像の移動
		VOID Move(
			int x_mult, int y_mult, MOVE_MULT move_mult);
		VOID Move(MOVE_LINE_TYPE move_type);//直線方向に移動	

		//		画面相対位置に画像の位置を設定
		//(画面)左上端：左上端
		VOID SetPos();
		//(画面)左上端：左上端 + margin
		VOID SetPos(int margin_x, int margin_y);
		//(画面)Pivot：Pivot
		VOID SetPos(n_xy::XY::PIVOT win_pivot, n_xy::XY::PIVOT img_pivot);
		//(画面)Pivot：Pivot + margin
		VOID SetPos(n_xy::XY::PIVOT win_pivot, n_xy::XY::PIVOT img_pivot,
			int margin_x, int margin_y
		);

		//		指定画像の相対位置に画像の位置を設定
		//(基点画像)左上端：左上端
		VOID SetPos(ClImg base_img);
		//(基点画像)左上端：左上端 + margin
		VOID SetPos(ClImg base_img, int margin_x, int margin_y);
		//(基点画像)Pivot：Pivot
		VOID SetPos(ClImg base_img,
			n_xy::XY::PIVOT base_pivot, n_xy::XY::PIVOT this_pivot);
		//(基点画像)Pivot：Pivot + margin
		VOID SetPos(ClImg base_img,
			n_xy::XY::PIVOT base_pivot, n_xy::XY::PIVOT this_pivot,
			int margin_x, int margin_y);

		//*----------------------------------------------------------------------------*
		//							protectedここから
		//*----------------------------------------------------------------------------*

	protected:
		//		プロテクト関数
		//共通画像の読み込み
		virtual BOOL MmLoad(string path, string cpp_name, string ins_name);

		//		プロテクト変数
		int m_handle;			//画像ハンドル
		string m_path;			//パス
		n_xy::XY m_pos;			//位置
		n_xy::XY m_size;		//サイズ
		int m_abs_speed;		//移動スピード
		float m_over_speed;		//移動スピードの小数点以下
		BOOL m_is_draw;			//描画するか
	};
}
