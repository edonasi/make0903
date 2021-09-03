#pragma once
//		�C���N���[�h�t�@�C��
#include "XY.hpp"	//XY�Ȃǂ��g�p

namespace n_win{

	//Window�̏��������s��
	class ClWin
	{
		//*----------------------------------------------------------------------------*
		//							public��������
		//*----------------------------------------------------------------------------*

	public:
		//		�R���X�g���N�^
		ClWin();	
		~ClWin();

		//		enum
		//�w�i�̐F�̎��
		enum BACK_COLOR_TYPE {
			BLACK,	//��
			WHITE,	//��
			OTHER	//���̑�
		};

		//		�v���p�e�B��������	
		n_xy::XY GetWinPivot();						//����[���擾
		n_xy::XY GetWinPivot(n_xy::XY::PIVOT pivot);	//�w�肵�������̍��W���擾
		//�Б���pivot�擾
		int GetWinPivotX(n_xy::XY::ONE_PIVOT pivot_x);
		int GetWinPivotY(n_xy::XY::ONE_PIVOT pivot_y);
		int GetWinHeight();		//�Q�[���̏c�����Q�Ƃ���
		int GetWinWidth();		//�Q�[���̉������Q�Ƃ���
		n_xy::XY GetWinSize();	//�Q�[���̉�ʃT�C�Y���擾
		int GetWinColor();		//�Q�[���̉𑜓x���Q�Ƃ���
		BOOL GetIsDebug();		//�f�o�b�N���[�h��	�Q��
		BACK_COLOR_TYPE GetBackColorType();//�w�i�F�̎�ނ��Q��

		//		�v���g�^�C�v�錾��������
		int Init();					//�Q�[���̏�����
		VOID BeforeInit();			//Init�O�̃Q�[��������
		VOID AfterInit();			//Init��̃Q�[��������

	//*----------------------------------------------------------------------------*
	//							private��������
	//*----------------------------------------------------------------------------*

	private:
		//		�����o�֐�
		VOID MmSetBackColorType();			//�w�i�F�̎�ނ�ݒ�
		BOOL MmIsNoChroma(int lightness);	//���ʐF��
		BACK_COLOR_TYPE M_BACK_COLOR_TYPE;	//�w�i�F�̎��

		//		�����o�ϐ�
		n_xy::XY m_size;
	};
}