#pragma once

namespace n_fps {

	//FPS���Ǘ�����
	class ClFps {

		//*----------------------------------------------------------------------------*
		//							public��������
		//*----------------------------------------------------------------------------*

	public:

		//		�V���O���g������
		static ClFps* GetIns();		//�C���X�^���X�擾

		//		�v���p�e�B��������
		//*------------------------------------------------*
		//		Fps�l�̊Ǘ�
		//*------------------------------------------------*
		int GetFpsIntValue();		//FPS�l(int)���擾
		int GetFpsIntFix(			//speed��fps�ɍ��킹�Ē���
			int speed, float* over);
		float GetFpsFloatValue();	//FPS�l(float)���擾
		float GetDeltaTime();		//deltaTime���Q��

		//		�v���g�^�C�v�錾�������� 
		VOID Destroy();			//�C���X�^���X�̔j��
		//*------------------------------------------------*
		//		Fps�l�̊Ǘ�
		//*------------------------------------------------*
		VOID FpsUpdate();		//Fps�l�𑪒肵�A�l���X�V����
		int FpsWait();			//FPS�ŏ�����҂�
		//*------------------------------------------------*
		//		Fps�l�̕`��
		//*------------------------------------------------*
		VOID FpsDraw();			//�f�o�b�N�p�̕���FPS�l�����F�ŉ�ʍ����ɕ`�悷��
		VOID FpsDraw(			//�ʒu��ݒ肵�ăf�o�b�N�p�̍��F�ŕ���FPS�l��`�悷��
			int draw_x,
			int draw_y
		);

		//*----------------------------------------------------------------------------*
		//							private��������
		//*----------------------------------------------------------------------------*

	private:

		//		�V���O���g������
		static ClFps* m_ins;		//�V���O���g���ȃC���X�^���X
		ClFps();						//�R���X�g���N�^
		ClFps(const ClFps& src);		//�R�s�[�R���X�g���N�^
		ClFps& operator=(const ClFps& src);
		virtual ~ClFps();				//�f�X�g���N�^

		//		�����o�ϐ���������
		//*------------------------------------------------*
		//		Fps�l�̊Ǘ�
		//*------------------------------------------------*
		BOOL m_is_init;				//�ŏ��̑���J�n�t���O
		LONGLONG m_start_time;		//�J�n�J�n����
		LONGLONG m_now_time;		//���݂̎���
		LONGLONG m_old_time;		//�ȑO�̎���
		int m_int_value;			//FPS(int)�̒l
		float m_float_value;		//FPS(float)�̒l
		float m_delta_time;			//�o�ߎ���
		int m_cnt;					//���݂̃t���[����
		int m_sample_rote;			//���ς����T���v���l
		//*------------------------------------------------*
		//		Fps�l�̕`��
		//*------------------------------------------------*
		//		�����o�v���g�^�C�v�錾��������
		VOID MmMemberVarInit();	//�����o�ϐ��̏�����
		//*------------------------------------------------*
		//		Fps�l�̕`��
		//*------------------------------------------------*
		int MmFpsDrawPosLimit(int num, int m_max);	//Fps�`��̈ʒu����
	};
}