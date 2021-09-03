//*--------------------------------------------------------------------------------*
//								XY�֌W�Ǘ�
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		���g�̃t�@�C��
#include XY_HPP
using namespace n_xy;

//*--------------------------------------------------------------------------------*
//								�R���X�g���N�^�A�f�X�g���N�^�A�ϐ��̏�����
//*--------------------------------------------------------------------------------*

const int POS_MIN = 0;	//���W�̍ŏ��l

//xy(0,0)�ŏ�����
XY::XY() {
	x = POS_MIN;
	y = POS_MIN;
}
//�����ŏ�����
XY::XY(int x_in, int y_in) {
	x = x_in;
	y = y_in;
}
XY::~XY() { return; }

//*--------------------------------------------------------------------------------*
//								�֐�
//*--------------------------------------------------------------------------------*

//����[(0, 0)���擾
XY XY::GetPivot() {
	XY xy = XY();
	return xy;
}

/// <summary>
/// �w�肵�������̍��W���擾
/// </summary>
/// <param name="pivot"></param>
/// <returns></returns>
XY XY::GetPivot(PIVOT pivot) {
	//����[�̍��W
	XY xy = XY();

	//X���W�̌v�Z
	switch (pivot){
		//����[�������珈���I��
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

	//Y���W�̌v�Z
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



//X���W���擾
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

//Y���W���擾
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