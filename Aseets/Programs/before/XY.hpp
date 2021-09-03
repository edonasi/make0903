#pragma once

namespace n_xy {
	//XY�N���X�\����
	class XY{
	public:
		//�R���X�g���N�^
		XY();
		XY(int x_in,int y_in);
		~XY();

		//enum
		//����							
		enum PIVOT {
			TOP_LEFT,		//����@
			TOP_CENTER,		//�@��
			TOP_RIGHT,		//�E��
			CENTER_LEFT,	//��
			CENTER_CENTER,	//�^��
			CENTER_RIGHT,	//�E
			BUTTOM_LEFT,	//����
			BUTTOM_CENTER,	//�@��
			BUTTOM_RIGHT	//�E��
		};

		enum ONE_PIVOT{
			MIN,	//�E/��
			HALF,	//�^��
			MAX		//��/��
		};

		//		�֐�
		XY GetPivot();			//����[���擾
		XY GetPivot(PIVOT pivot);	//�w�肵�������̍��W���擾
		//�Б���pivot�擾
		int GetPivotX(ONE_PIVOT pivot_x);
		int GetPivotY(ONE_PIVOT pivot_y);
		
		//		�ϐ�
		int x;
		int y;
	};
}