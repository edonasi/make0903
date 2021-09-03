//*-------------------------------------------------------------------------------*
//							�Q�[���̃V�[�����Ǘ�
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		���g�̃w�b�_�t�@�C��
#include GAME_SCENE_HPP
using namespace n_game_scene;
//		����w�b�_�t�@�C��
#include AUDIO_MULT_HPP
using namespace n_audio_mult;

//*--------------------------------------------------------------------------------*
//								�V���O���g������
//*--------------------------------------------------------------------------------*

//�V���O���g����GameStateManager�N���X�̃I�u�W�F�N�g
ClGameScene* ClGameScene::m_ins = nullptr;

/// <summary>
/// �R���X�g���N�^�A������
/// </summary>
ClGameScene::ClGameScene() { 
	m_scene = n_game_scene::ClGameScene::GAME_SCENE::LOAD;
	m_next_scene = n_game_scene::ClGameScene::GAME_SCENE::LOAD;
	m_back_scene = n_game_scene::ClGameScene::BACK_GAME_SCENE::NONE;
	m_is_change_secne = FALSE;
	m_fade = n_fade::ClFade();
	//�������~�߂邩
	m_is_load_proc_stop = FALSE;
	m_is_title_proc_stop = FALSE;
	m_is_play_proc_stop = FALSE;
	//�V�[�����ꂼ��̐i�s��
	m_load_state = n_game_scene::ClGameScene::SCENE_STATE::START;
	m_title_state = n_game_scene::ClGameScene::SCENE_STATE::END;
	m_play_state = n_game_scene::ClGameScene::SCENE_STATE::END;
	return; 
}

/// <summary>
/// �R�s�[�R���X�g���N�^
/// </summary>
/// <param name="src">�R�s�[���A�h���X</param>
ClGameScene::ClGameScene(const ClGameScene& src) {
	//�A�h���X���R�s�[���Ă���
	m_ins = src.m_ins;
}

/// <summary>
/// �R�s�[�R���X�g���N�^
/// </summary>
/// <param name="src">�R�s�[���A�h���X</param>
/// <returns>���̃C���X�^���X�̃A�h���X</returns>
ClGameScene& ClGameScene::operator=(const ClGameScene& src) {
	//�A�h���X���R�s�[���Ă���
	m_ins = src.m_ins;
	return *this;
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ClGameScene::~ClGameScene() { return; }

/// <summary>
/// �C���X�^���X�擾(���߂ĎQ�Ƃ���Ƃ��̓C���X�^���X�𐶐�)
/// </summary>
/// <returns><�V���O���g���ȃC���X�^���X/returns>
ClGameScene* ClGameScene::GetIns() {
	//���߂Ď擾���鎞�A���̃I�u�W�F�N�g�𐶐��𐶐�
	if (m_ins == nullptr)
	{
		//�������̊m��
		m_ins = new ClGameScene();
	}

	return m_ins;
}

/// <summary>
/// �I�u�W�F�N�g�̔j��
/// </summary>
VOID ClGameScene::Destroy() {
	//�������̔j��
	delete m_ins;
	m_ins = nullptr;
}

//*--------------------------------------------------------------------------------*
//								�v���p�e�B
//*--------------------------------------------------------------------------------*

//���[�h��ʂɐ؂�ւ�
VOID ClGameScene::ChangeSceneLoad() { MmChangeScene(GAME_SCENE::LOAD); }

//�^�C�g����ʂɐ؂�ւ�
VOID ClGameScene::ChangeSceneTitle() { MmChangeScene(GAME_SCENE::TITLE); }

//�v���C��ʂɐ؂�ւ�
VOID ClGameScene::ChangeScenePlay() { MmChangeScene(GAME_SCENE::PLAY); }

//const float FADE_TIME = 0.25f;	//�t�F�[�h���鎞��
const float FADE_TIME = 2.0f;	//�t�F�[�h���鎞��

/// <summary>
/// �V�[���ύX�J�n����
/// </summary>
/// <param name="next_scene">���̃V�[��</param>
VOID ClGameScene::MmChangeScene(GAME_SCENE next_scene) {
	//�V�[���ύX���͕ύX�ς����Ȃ�
	if (m_is_change_secne == TRUE) { return; }

	//�t�F�[�h�A�E�g���鏀��
	m_next_scene = next_scene;
	m_is_change_secne = TRUE;
	m_back_scene = n_game_scene::ClGameScene::BACK_GAME_SCENE::BACK_LOAD;
	m_fade.FadeUpStart(FADE_TIME);
	ClAudioMult::GetIns()->SetFadeDownStart(FADE_TIME);

	//�t�F�[�h�O�̃V�[���̕`��ȊO�̏������~������
	MmSetProcStopState(m_scene, TRUE);

	//�t�F�[�h��̃V�[���̕`��ȊO�̏������~������
	MmSetProcStopState(m_next_scene, TRUE);

	//�J�n������������
	MmSetSceneState(m_next_scene, n_game_scene::ClGameScene::SCENE_STATE::START);

	//�t�F�[�h�A�b�v�J�n�n�_�����J�n�̃t���O�𗧂Ă�
	MmSetSceneState(m_scene, n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START);
}

/// <summary>
/// �`��ȊO�̏������~������t���O�̐ݒ�
/// </summary>
/// <param name="scene">�Q�Ƃ���Q�[���V�[��</param>
/// <param name="is_stop">��~�����邩</param>
VOID ClGameScene::MmSetProcStopState(GAME_SCENE scene, BOOL is_stop) {
	switch (scene){
		//���[�h��ʎ�
	case n_game_scene::ClGameScene::LOAD:
		m_is_load_proc_stop = is_stop;
		break;

		//�^�C�g����ʎ�
	case n_game_scene::ClGameScene::TITLE:
		m_is_title_proc_stop = is_stop;
		break;

		//�v���C��ʎ�
	case n_game_scene::ClGameScene::PLAY:
		m_is_play_proc_stop = is_stop;
		break;

	default:break;
	}
}

/// <summary>
/// �Q�ƃV�[���̐i�s��Ԃ�ύX����
/// </summary>
/// <param name="scene">�Q�ƃV�[��</param>
/// <param name="set_state">�i�s��ԁA�ύX��</param>
VOID ClGameScene::MmSetSceneState(GAME_SCENE scene, SCENE_STATE set_state) {
	switch (scene){
	case n_game_scene::ClGameScene::LOAD:
		m_load_state = set_state;
		break;
	case n_game_scene::ClGameScene::TITLE:
		m_title_state = set_state;
		break;
	case n_game_scene::ClGameScene::PLAY:
		m_play_state = set_state;
		break;
	default:
		break;
	}
}

//*--------------------------------------------------------------------------------*
//								�֐�
//*--------------------------------------------------------------------------------*

//�Q�[�����J�n�O�̏���
VOID ClGameScene::GameInit() {

	//*---------- �������珈�� ----------*

}

//���݂̃Q�[���V�[���ɂ���ď�����ς���
VOID ClGameScene::GameSceneSwitch() {
	switch (m_scene){
		//���[�h���
	case n_game_scene::ClGameScene::LOAD:
		MmLoadProc();	//����
		MmLoadDraw();	//�`��
		break;

		//�^�C�g�����
	case n_game_scene::ClGameScene::TITLE:
		MmTitleProc();	//����
		MmTitleDraw();	//�`��
		break;

		//�v���C���
	case n_game_scene::ClGameScene::PLAY:
		MmPlayProc();	//����
		MmPlayDraw();	//�`��
		break;

	default:break;
	}

	//���ǂݍ��݂��s����
	switch (m_back_scene){
		//�Ȃɂ��s��Ȃ�
	case n_game_scene::ClGameScene::BACK_GAME_SCENE::NONE:
		MmBackNoneDebug();	//�f�o�b�N
		break;

		//�����[�h���s��
	case n_game_scene::ClGameScene::BACK_LOAD:
		MmBackLoadProc();	//����
		MmBackLoadDebug();	//�f�o�b�N
		break;

	default:break;
	}
}

//*------------------------------------------------*
//		���[�h���
//*------------------------------------------------*

//���[�h����
VOID ClGameScene::MmLoadProc() {
	if (MmIsLoadProcDo() == FALSE) { return; }	//���̐�̏����͍s��Ȃ�

	//*---------- ����������s���� ----------*

}

//���[�h�������s����
BOOL ClGameScene::MmIsLoadProcDo() {
	MmSceneChangeProc();				//�V�[���ύX
	MmLoadStart();						//�V�[���؂�ւ���ŏ��̏���
	MmLoadProcEnd();					//�t�F�[�h�A�E�g�J�n�n�_����
	MmLoadEnd();						//�t�F�[�h�A�E�g�����n�_����
	if (m_is_load_proc_stop == TRUE) {	//���̐�̏����͍s��Ȃ�
		return FALSE; 
	}
	MmLoadProcStart();					//�t�F�[�h�C����̍ŏ��̏���

	return TRUE;
}

//���[�h�V�[���J�n����(m_scene���ύX�����Ƃ���1�x�̂�)
VOID ClGameScene::MmLoadStart() {
	//1�x�݂̂̏���
	if (m_load_state != n_game_scene::ClGameScene::SCENE_STATE::START) { return; }
	m_load_state = n_game_scene::ClGameScene::SCENE_STATE::START_AFTER;

	//*---------- ��������J�n���� ----------*
}		

//���[�h�����J�n����(�t�F�[�h�C���I�������1�x�̂�)
VOID ClGameScene::MmLoadProcStart() {
	//1�x�݂̂̏���
	if (m_load_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END) { return; }
	m_load_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END_AFTER;

	//*---------- ��������J�n���� ----------*
}

//�t�F�[�h�A�E�g�J�n�n�_����(�t�F�[�h�A�E�g�J�n��1�x�̂�)
VOID ClGameScene::MmLoadProcEnd() {
	//1�x�݂̂̏���
	if (m_load_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START) { return; }
	m_load_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START_AFTER;

	//*---------- ��������J�n���� ----------*
}

//�t�F�[�h�A�E�g�����n�_����(�t�F�[�h�A�E�g������1�x�̂�)
VOID ClGameScene::MmLoadEnd() {
	MmEnd(&m_load_state);		//�V�[���I���n�_�J�n�O����

	//*---------- ��������J�n���� ----------*

}

//���[�h�`��
VOID ClGameScene::MmLoadDraw() {

	//*---------- ���`�揈���͏�ɏ����� ----------*
	//�t�F�[�h����
	if (m_is_change_secne == TRUE) { m_fade.FadeSameDraw(); }

	//*---------- ��������f�o�b�N���� ----------*

	if (ClWin().GetIsDebug() == FALSE) { return; }	//�f�o�b�N��Ԃł͂Ȃ��Ȃ珈�����s��Ȃ�
	
	//���݂̉�ʏ�Ԃ�\��
	DrawString(ClWin().GetWinPivot().x, ClWin().GetWinPivot().y, "Load", ClCom().GetFlipColor());
}

//*------------------------------------------------*
//		�^�C�g�����
//*------------------------------------------------*

//�^�C�g������
VOID ClGameScene::MmTitleProc() {
	if (MmIsTitleProcDo() == FALSE) { return; }		//���̐�̏����͍s��Ȃ�

	//*---------- ����������s���� ----------*

	
}

//�^�C�g���������s����
BOOL ClGameScene::MmIsTitleProcDo() {
	MmSceneChangeProc();				//�V�[���ύX
	MmTitleStart();						//�V�[���؂�ւ���ŏ��̏���
	MmTitleProcEnd();					//�t�F�[�h�A�E�g�J�n�n�_����
	MmTitleEnd();						//�t�F�[�h�A�E�g�����n�_����
	if (m_is_title_proc_stop == TRUE) {	//���̐�̏����͍s��Ȃ�
		return FALSE;
	}
	MmTitleProcStart();					//�t�F�[�h�C����̍ŏ��̏���

	return TRUE;
}

//�^�C�g���V�[���J�n����(m_scene���ύX�����Ƃ���1�x�̂�)
VOID ClGameScene::MmTitleStart() {
	//1�x�݂̂̏���
	if (m_title_state != n_game_scene::ClGameScene::SCENE_STATE::START) { return; }
	m_title_state = n_game_scene::ClGameScene::SCENE_STATE::START_AFTER;

	//*---------- ��������J�n���� ----------*

}

//�^�C�g���V�[�������J�n����(�t�F�[�h�C���I�������1�x�̂�)
VOID ClGameScene::MmTitleProcStart() {
	//1�x�݂̂̏���
	if (m_title_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END) { return; }
	m_title_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END_AFTER;

	//*---------- ��������J�n���� ----------*
}

//�t�F�[�h�A�E�g�����J�n�n�_����
VOID ClGameScene::MmTitleProcEnd() {
	//1�x�݂̂̏���
	if (m_title_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START) { return; }
	m_title_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START_AFTER;

	//*---------- ��������J�n���� ----------*
}

//�V�[���I���n�_����
VOID ClGameScene::MmTitleEnd() {
	MmEnd(&m_title_state);		//�V�[���I���n�_�J�n�O����

	//*---------- ��������J�n���� ----------*
}

//�^�C�g���`��
VOID ClGameScene::MmTitleDraw() {

	//*---------- ���`�揈���͏�ɏ����� ----------*
	//�t�F�[�h����
	if (m_is_change_secne == TRUE) { m_fade.FadeSameDraw(); }

	//*---------- ��������f�o�b�N���� ----------*

	if (ClWin().GetIsDebug() == FALSE) { return; }	//�f�o�b�N��Ԃł͂Ȃ��Ȃ珈�����s��Ȃ�

	//���݂̉�ʏ�Ԃ�\��
	DrawString(ClWin().GetWinPivot().x, ClWin().GetWinPivot().y, "Title", ClCom().GetFlipColor());
}

//*------------------------------------------------*
//		�v���C���
//*------------------------------------------------*

//�v���C����
VOID ClGameScene::MmPlayProc() {
	if (MmIsPlayProcDo() == FALSE) { return; }		//���̐�̏����͍s��Ȃ�

	//*---------- ����������s���� ----------*
}

//�v���C�������s����
BOOL ClGameScene::MmIsPlayProcDo() {
	MmSceneChangeProc();				//�V�[���ύX
	MmPlayStart();						//�V�[���؂�ւ���ŏ��̏���
	MmPlayProcEnd();					//�t�F�[�h�A�E�g�J�n�n�_����
	MmPlayEnd();						//�t�F�[�h�A�E�g�����n�_����
	if (m_is_play_proc_stop == TRUE) {	//���̐�̏����͍s��Ȃ�
		return FALSE;
	}
	MmPlayProcStart();					//�t�F�[�h�C����̍ŏ��̏���

	return TRUE;
}

//�v���C�V�[���J�n����(m_scene���ύX�����Ƃ���1�x�̂�)
VOID ClGameScene::MmPlayStart() {
	//1�x�݂̂̏���
	if (m_play_state != n_game_scene::ClGameScene::SCENE_STATE::START) { return; }
	m_play_state = n_game_scene::ClGameScene::SCENE_STATE::START_AFTER;

	//*---------- ��������J�n���� ----------*
}

//�v���C�V�[�������J�n����(�t�F�[�h�C���I�������1�x�̂�)
VOID ClGameScene::MmPlayProcStart() {
	//1�x�݂̂̏���
	if (m_play_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END) { return; }
	m_play_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END_AFTER;

	//*---------- ��������J�n���� ----------*
}

//�t�F�[�h�A�E�g�����J�n�n�_����
VOID ClGameScene::MmPlayProcEnd() {
	//1�x�݂̂̏���
	if (m_play_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START) { return; }
	m_play_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START_AFTER;

	//*---------- ��������J�n���� ----------*
}

//�V�[���I���n�_����
VOID ClGameScene::MmPlayEnd() {
	MmEnd(&m_play_state);		//�V�[���I���n�_�J�n�O����

	//*---------- ��������J�n���� ----------*
}

//�v���C�`��
VOID ClGameScene::MmPlayDraw() {

	//*---------- ���`�揈���͏�ɏ����� ----------*
	//�t�F�[�h����
	if (m_is_change_secne == TRUE) { m_fade.FadeSameDraw(); }

	//*---------- ��������f�o�b�N���� ----------*

	if (ClWin().GetIsDebug() == FALSE) { return; }	//�f�o�b�N��Ԃł͂Ȃ��Ȃ珈�����s��Ȃ�

	//���݂̉�ʏ�Ԃ�\��
	DrawString(ClWin().GetWinPivot().x, ClWin().GetWinPivot().y, "Play", ClCom().GetFlipColor());
}

VOID ClGameScene::MmEnd(SCENE_STATE* scene_state) {
	if (*scene_state != n_game_scene::ClGameScene::SCENE_STATE::END) { return; }
	*scene_state = n_game_scene::ClGameScene::SCENE_STATE::NEXT_SCENE;

	m_scene = m_next_scene;	//���̃V�[����
	MmSetSceneState(m_scene, n_game_scene::ClGameScene::SCENE_STATE::START);

	m_fade.FadeDownStart(FADE_TIME);					//��ʃt�F�[�h�_�E���J�n
	ClAudioMult::GetIns()->SetFadeUpStart(FADE_TIME);	//���ʃt�F�[�h�A�b�v�J�n
}

//*------------------------------------------------*
//		���ʊ֐�
//*------------------------------------------------*

//�V�[���ύX����
VOID ClGameScene::MmSceneChangeProc() {
	//�V�[���ύX���s���Ȃ��Ȃ珈�����s��Ȃ�
	if (m_is_change_secne == FALSE) { return; }
		
	//�t�F�[�h���X�V
	m_fade.FadeProc();
	ClAudioMult::GetIns()->FadeProc();

	//�t�F�[�h�A�E�g�������I��������
	if (m_fade.GetIsFadeNone() == TRUE && m_fade.GetFadeType() == n_fade::ClFade::FADE_TYPE::FADE_UP_TYPE) {
		//�t�F�[�h�A�E�g�J�n�n�_�����̃t���O�𗧂Ă�
		MmSetSceneState(m_scene, n_game_scene::ClGameScene::SCENE_STATE::END);
	}

	//�t�F�[�h�C���������I��������
	if (m_fade.GetIsFadeNone() == TRUE && m_fade.GetFadeType() == n_fade::ClFade::FADE_TYPE::FADE_DOWN_TYPE) {
		m_back_scene = n_game_scene::ClGameScene::BACK_GAME_SCENE::NONE;	//�����[�h������

		//�t�F�[�h�C���I����J�n�����̏�Ԃɂ���
		MmSetSceneState(m_scene, n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END);

		m_is_change_secne = FALSE;			//�V�[���؂�ւ��t���O������

		//�V�[�����Ƃ̏������~������t���O������
		MmSetProcStopState(m_scene, FALSE);
	}
}

//*------------------------------------------------*
//		���V�[��
//*------------------------------------------------*

//���V�[�����Ȃ��Ƃ��̃f�o�b�N����
VOID ClGameScene::MmBackNoneDebug() {
	//�f�o�b�N��Ԃł͂Ȃ��Ȃ珈�����s��Ȃ�
	if (ClWin().GetIsDebug() == FALSE) { return; }

	//���݂̗���ʏ�Ԃ�\��
	DrawString(
		ClWin().GetWinPivot().x, ClWin().GetWinPivot().y + ClCom().GetDefalutFontSize(),
		"BackNone", ClCom().GetFlipColor()
	);
}

//�����[�h����
VOID ClGameScene::MmBackLoadProc() {}

//�����[�h�f�o�b�N����
VOID ClGameScene::MmBackLoadDebug() {
	//�f�o�b�N��Ԃł͂Ȃ��Ȃ珈�����s��Ȃ�
	if (ClWin().GetIsDebug() == FALSE) { return; }

	//���݂̗���ʏ�Ԃ�\��
	DrawString(
		ClWin().GetWinPivot().x, ClWin().GetWinPivot().y + ClCom().GetDefalutFontSize(),
		"BackLoad", ClCom().GetFlipColor()
	);
}
