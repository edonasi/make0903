#pragma once

//���X�̃L�[�̐�
#define MOUSE_BUTTON_CODE 129
#define BUTTON_TIME_INPUT_NUM 5

namespace n_mouse
{
	//�L�[�{�[�h�̓��͂��Ǘ�����
	class ClMouse
	{
		//*----------------------------------------------------------------------------*
		//							public��������
		//*----------------------------------------------------------------------------*

	public:
		//		�V���O���g������		
		//�C���X�^���X�擾(���߂ĎQ�Ƃ���Ƃ��̓C���X�^���X�𐶐�)
		static ClMouse* GetIns();
		//�I�u�W�F�N�g�̔j��
		VOID Destroy();

		//		���ʃN���X����
		class XY {
		public:
			XY();
			~XY();
			int x;
			int y;
		};

		//		�Ǝ��N���X����
		//�}�E�X�N���X�\����
		class MOUSE {
		public:
			MOUSE();
			~MOUSE();
			int input_value;		//GetMouseInput�̒l
			int wheel_value;		//�}�E�X�z�C�[���̉�]��(���{�@��O�|)
			n_mouse::ClMouse::XY point;	//�v���C��ʏ�̃}�E�X�̈ʒu
			int button[MOUSE_BUTTON_CODE];
		};

		//		�֐�
		//*------------------------------------------------*
		//		�}�E�X�̍X�V
		//*------------------------------------------------*
		int MouseUpdate();		//�}�E�X�̍X�V
		//*------------------------------------------------*
		//		�����蔻��Ȃ��N���b�N����
		//*------------------------------------------------*
		//�{�^���̓��͎��Ԃ�Ԃ�
		int GetButtonCnt(int mouse_input_);
		//�{�^����������Ă����Ԃ�(������Ă����ԂȂ�TRUE)
		BOOL GetIsButton(int mouse_input_);
		//�{�^���������ꂽ�u�Ԃ�(�����ꂽ�u�ԂȂ�TRUE)
		BOOL GetIsButtonDown(int mouse_input_);
		//�{�^���������ꂽ�u�Ԃ�(�����ꂽ�u�ԂȂ�TRUE)
		BOOL GetIsButtonUp(int mouse_input_);
		//�{�^���𗣂��Ă����Ԃ�(������Ă���Ȃ�TRUE)
		BOOL GetIsButtonAway(int mouse_input_);
		//�w�莞�ԉ����ꂽ��
		BOOL GetIsButtonTimeInput(int mouse_input_, float time);
		//�w�莞��(�~���b)(�𒴂��� / �ȏ� / �Ɠ��� / �ȉ� / ����)�{�^���������ꂽ��(��{�F�𒴂���)
		BOOL GetIsButtonTimeInput(int mouse_input_, float time, n_com::IF_CASE_TYPE mouse_case_type);
		//*------------------------------------------------*
		//		�f�o�b�N
		//*------------------------------------------------*
		VOID MousePosDraw();	//�}�E�X�̈ʒu����`�悷��

		//*----------------------------------------------------------------------------*
		//							private��������
		//*----------------------------------------------------------------------------*

	private:
		//		�V���O���g������
		//�V���O���g���ȃC���X�^���X
		static ClMouse* m_ins;
		//�R���X�g���N�^�A�L�[�̏�Ԃ�������
		ClMouse();
		//�R�s�[�R���X�g���N�^
		ClMouse(const ClMouse& src);
		ClMouse& operator=(const ClMouse& src);
		//�f�X�g���N�^
		virtual ~ClMouse();

		//		�����o�ϐ�
		MOUSE m_mouse;			//�}�E�X�ϐ�
		//�w��b�������ꂽ����ォ
		BOOL m_is_time_input_button_after[MOUSE_BUTTON_CODE][BUTTON_TIME_INPUT_NUM];

		//		�֐�
		//�}�E�X�R�[�h�ɑΉ������{�^����������Ă��邩�`�F�b�N
		VOID MmMouseCheck(MOUSE* mouse, int mouse_input_);	
	};
}