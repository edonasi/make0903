//�w�b�_�t�@�C���ǂݍ���
#include "game.h"		//�Q�[���S�̂̃w�b�_�t�@�C��
#include "keyboard.h"	//�L�[�{�[�h�̏���
#include "FPS.h"		//FPS�̏���
#include "mouse.h"		//�}�E�X�̏���
#include "shape.h"		//�}�`�̏���

//�Ǝ��̃}�N����`

//�Ǝ��̗񋓌^�̒�`
enum MUKI
{
	muki_none,
	muki_ue,
	muki_hidari,
	muki_shita,
	muki_migi
};//�����̃T���v��

//�Ǝ��̍\���̂̒�`


//�������Q�[�����ʂ̃O���[�o���ϐ�������
//�V�[�����Ǘ�����ϐ�
GAME_SCENE GameScene;		//���݂̃Q�[���̃V�[��
GAME_SCENE OldGameScene;	//�O��̃Q�[���̃V�[��
GAME_SCENE NextGameScene;	//���̃Q�[���̃V�[��

//��ʂ̐؂�ւ�
BOOL IsFadeOut = FALSE;		//�t�F�[�h�A�E�g
BOOL IsFadeIn = FALSE;		//�t�F�[�h�C��

int fadeTimeMill = 2000;					//�؂�ւ��~���b
int fadeTimeMax = fadeTimeMill / 1000 * 60;	//�~���b���t���[���b�ɕϊ�

//�t�F�[�h�A�E�g
int fadeOutCntInit = 0;				//�����l
int fadeOutCnt = fadeOutCntInit;	//�t�F�[�h�A�E�g�̃J�E���^
int fadeOutCntMax = fadeTimeMax;	//�t�F�[�h�A�E�g�̃J�E���^MAX

//�t�F�[�h�C��
int fadeInCntInit = fadeTimeMax;	//�����l
int fadeInCnt = fadeInCntInit;		//�t�F�[�h�A�E�g�̃J�E���^
int fadeInCntMax = fadeTimeMax;		//�t�F�[�h�A�E�g�̃J�E���^MAX
//�������Q�[�����ʂ̃O���[�o���ϐ�������


//�Ǝ��̃O���[�o���ϐ�


//�������Q�[�����ʂ̃v���g�^�C�v�錾������
BOOL GameLoad(VOID);	//�f�[�^��Ǎ�
VOID GameInit(VOID);	//�f�[�^�̏�����
VOID GameDelete(VOID);	//�f�[�^���폜

VOID Title(VOID);		//�^�C�g�����
VOID TitleProc(VOID);	//�^�C�g�����(����)
VOID TitleDraw(VOID);	//�^�C�g�����(�`��)

VOID Play(VOID);		//�v���C���
VOID PlayProc(VOID);	//�v���C���(����)
VOID PlayDraw(VOID);	//�v���C���(�`��)

VOID End(VOID);			//�G���h���
VOID EndProc(VOID);		//�G���h���(����)
VOID EndDraw(VOID);		//�G���h���(�`��)

VOID Change(VOID);		//�؂�ւ����
VOID ChangeProc(VOID);	//�؂�ւ����(����)
VOID ChangeDraw(VOID);	//�؂�ւ����(�`��)

VOID ChangeScene(GAME_SCENE scene);		//�V�[���؂�ւ�
BOOL OnCollRect(RECT a, RECT b);		//��`�Ƌ�`�̓����蔻��
VOID CollUpdateImage(IMAGE* img);		//�摜�̓����蔻��̍X�V
VOID CollUpdateDivImage(DIVIMAGE* div);	//�����摜�̓����蔻��̍X�V
BOOL LoadImageMem(IMAGE* image, const char* path);										//�Q�[���̉摜��ǂݍ���
BOOL LoadAudio(AUDIO* audio, const char* path, int Volume, int playType);				//�Q�[���̉��y��ǂݍ���
BOOL LoadImageDivMem(DIVIMAGE* div, const char* path, int bunkatuYoko, int bunkatuTate);//�Q�[���̉摜�̕����ǂݍ���

VOID PlayAudio(AUDIO audio);					//���y�Đ�
int GetVolumeAudio(AUDIO audio);				//���y�̃{�����[���擾
VOID SetVolumeAudio(AUDIO* audio, int vol);		//���y�̃{�����[���ݒ�
VOID ChangeVolumeAudio(AUDIO* audio, int vol);	//���y�̃{�����[���ύX
VOID StopAudio(AUDIO* audio);					//���y��~

VOID DrawImage(IMAGE image);					//�摜�`��
VOID DrawRect(RECT r, unsigned int color, bool b);	//RECT�`��
VOID DrawDivImage(DIVIMAGE* image);				//�����摜�̕`��
VOID DrawDivImageChara(DIVIMAGE* image);		//�����摜�̕`��

//�������Q�[�����ʂ̃v���g�^�C�v�錾������

//�T���v���̑f��
IMAGE sampleImg;
DIVIMAGE sampleDivImg;		//����
DIVIMAGE samplePlayerImg;	//�L�����N�^�[
MUKI muki = muki_shita;		//�T���v������

//�L�����摜
DIVIMAGE catDivImg;
MUKI catMuki = muki_shita;
int catStartX = 32;
int catStartY = 32;

AUDIO titleBGM;
AUDIO playBGM;
AUDIO endBGM;

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);				//Log.txt���o�͂��Ȃ�
	ChangeWindowMode(TRUE);								//�E�B���h�E���[�h�ɐݒ�
	SetMainWindowText(GAME_TITLE);						//�E�B���h�E�̃^�C�g���̕���
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�E�B���h�E�̉𑜓x��ݒ�
	SetWindowSize(GAME_WIDTH, GAME_HEIGHT);				//�E�B���h�E�̑傫����ݒ�
	SetBackgroundColor(255, 255, 255);					//�f�t�H���g�̔w�i�̐F
	SetWindowIconID(GAME_ICON_ID);						//�A�C�R���t�@�C����Ǎ�
	SetWindowStyleMode(GAME_WINDOW_BAR);				//�E�B���h�E�o�[�̏��
	SetWaitVSyncFlag(TRUE);								//�f�B�X�v���C�̐���������L���ɂ���
	SetAlwaysRunFlag(TRUE);								//�E�B���h�E�������ƃA�N�e�B�u�ɂ���

	//�c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		// �G���[���N�����璼���ɏI��
		return -1;
	}

	//�_�u���o�b�t�@�����O�L����
	SetDrawScreen(DX_SCREEN_BACK);

	//�ŏ��̃V�[���́A�^�C�g����ʂ���
	GameScene = GAME_SCENE_TITLE;

	//�Q�[���ǂݍ���
	if (!GameLoad())
	{
		//�f�[�^�̓ǂݍ��݂Ɏ��s�����Ƃ�
		GameDelete();	//�f�[�^�폜
		DxLib_End();	//DxLib�I��
		return -1;		//�ُ�I��
	}

	//�Q�[���̏�����
	GameInit();

	//�������[�v
	while (1)
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W���󂯎�葱����
		if (ClearDrawScreen() != 0) { break; }	//��ʂ���������

		//�L�[�{�[�h���͂̍X�V
		AllKeyUpdate();

		//�}�E�X���͂̍X�V
		MouseUpdate();

		//FPS�l�̍X�V
		FPSUpdate();

		//ESC�L�[�ŋ����I��
		if (KeyClick(KEY_INPUT_ESCAPE) == TRUE) { break; }

		//�ȑO�̃V�[�����擾
		if (GameScene != GAME_SCENE_CHANGE)
		{
			OldGameScene = GameScene;
		}

		//�V�[�����Ƃɏ������s��
		switch (GameScene)
		{
		case GAME_SCENE_TITLE:
			Title();			//�^�C�g�����
			break;
		case GAME_SCENE_PLAY:
			Play();				//�v���C���
			break;
		case GAME_SCENE_END:
			End();				//�G���h���
			break;
		case GAME_SCENE_CHANGE:
			Change();			//�؂�ւ����
			break;
		default:
			break;
		}

		//�V�[����؂�ւ���
		if (OldGameScene != GameScene)
		{
			//���݂̃V�[�����؂�ւ���ʂłȂ��Ƃ�
			if (GameScene != GAME_SCENE_CHANGE)
			{
				NextGameScene = GameScene;		//���̃V�[����ۑ�
				GameScene = GAME_SCENE_CHANGE;	//��ʐ؂�ւ��V�[���ɕς���
			}
		}

		//���݂̃}�E�X�̏���`��
		MouseDraw();

		//FPS�l��`��
		FPSDraw();

		//FPS�l��҂�
		FPSWait();

		ScreenFlip();	//�_�u���o�b�t�@�����O������ʂ�`��
	}

	//�f�[�^�폜
	GameDelete();

	//�c�w���C�u�����g�p�̏I������
	DxLib_End();

	return 0;	// �\�t�g�̏I�� 
}

/// <summary>
/// �Q�[���̃f�[�^��ǂݍ���
/// </summary>
/// <returns>�ǂݍ��߂���TRUE / �ǂݍ��߂Ȃ�������FALSE</returns>
BOOL GameLoad(VOID)
{
	//�T���v���摜��ǂݍ���
	if (LoadImageMem(&sampleImg, ".\\Aseets\\Images\\player.png") == FALSE) { return FALSE; }

	//�T���v�������摜��ǂݍ���
	if (LoadImageDivMem(&sampleDivImg, ".\\Aseets\\Images\\baku1.png", 8, 2) == FALSE) { return FALSE; }

	//�T���v�������摜��ǂݍ���
	if (LoadImageDivMem(&samplePlayerImg, ".\\Aseets\\Images\\charachip.png", 3, 4) == FALSE) { return FALSE; }

	//�L�����摜��ǂݍ���
	if (LoadImageDivMem(&catDivImg, "./Aseets/Images/pipo-charachip010a.png", 3, 4) == FALSE) { return FALSE; }

	//BGM��ǂݍ���
	if (LoadAudio(&titleBGM, ".\\Aseets\\Audios\\�u���L��PARADE.mp3", 128, DX_PLAYTYPE_LOOP) == FALSE) { return FALSE; }
	if (LoadAudio(&playBGM, ".\\Aseets\\Audios\\PlayBgm.mp3", 128, DX_PLAYTYPE_LOOP) == FALSE) { return FALSE; }
	if (LoadAudio(&endBGM, ".\\Aseets\\Audios\\EndBgm.mp3", 128, DX_PLAYTYPE_LOOP) == FALSE) { return FALSE; }

	return TRUE;	//�S�ēǂݍ��݂��I
}

/// <summary>
/// �Q�[���̃f�[�^���폜
/// </summary>
VOID GameDelete(VOID)
{
	//�T���v���摜���폜
	DeleteGraph(sampleImg.handle);

	//�T���v�������摜���폜
	for (int i = 0; i < sampleDivImg.DivMax; i++) { DeleteGraph(sampleDivImg.handle[i]); }

	//�T���v�������摜���폜
	for (int i = 0; i < samplePlayerImg.DivMax; i++) { DeleteGraph(samplePlayerImg.handle[i]); }

	//�L�����摜���폜
	for (int i = 0; i < catDivImg.DivMax; i++) { DeleteGraph(catDivImg.handle[i]); }

	//�T���v�����y���폜
	DeleteMusicMem(titleBGM.handle);

	return;
}

/// <summary>
/// �Q�[���f�[�^��������
/// </summary>
/// <param name=""></param>
VOID GameInit(VOID)
{
	//�L�摜�����ʒu������
	catDivImg.x = catStartX;
	catDivImg.y = catStartY;

	//�Q�[�������ԃ��Z�b�g
	ResetGameTime();

	return;
}

/// <summary>
/// �V�[����؂�ւ���֐�
/// </summary>
/// <param name="scene">�V�[��</param>
VOID ChangeScene(GAME_SCENE scene)
{
	GameScene = scene;	//�V�[����؂�ւ�
	IsFadeIn = FALSE;	//�t�F�[�h�C�����Ȃ�
	IsFadeOut = TRUE;	//�t�F�[�h�A�E�g����

	return;
}

/// <summary>
/// �^�C�g�����
/// </summary>
VOID Title(VOID)
{
	TitleProc();	//����
	TitleDraw();	//�`��

	return;
}

/// <summary>
/// �^�C�g����ʂ̏���
/// </summary>
VOID TitleProc(VOID)
{
	if (KeyClick(KEY_INPUT_RETURN) == TRUE)
	{
		//�V�[���؂�ւ�
		//���̃V�[���̏������������ōs���Ɗy

		//�Q�[���̏�����
		GameInit();

		//BGM�̒�~
		StopAudio(&titleBGM);

		//�v���C��ʂɐ؂�ւ�
		ChangeScene(GAME_SCENE_PLAY);

		return;
	}

	PlayAudio(titleBGM);	//BGM��炷

	//�v���C���[�̓���T���v��
	{
		muki = muki_none;	//�ŏ��͌����𖳂��ɂ���
		if (KeyDown(KEY_INPUT_W)) { muki = muki_ue; samplePlayerImg.y--; }
		else if (KeyDown(KEY_INPUT_S)) { muki = muki_shita; samplePlayerImg.y++; }
		if (KeyDown(KEY_INPUT_A)) { muki = muki_hidari; samplePlayerImg.x--; }
		else if (KeyDown(KEY_INPUT_D)) { muki = muki_migi; samplePlayerImg.x++; }
		CollUpdateDivImage(&samplePlayerImg);	//�����蔻��̍X�V
	}

	//�L����
	catMuki = muki_none;
	if (KeyDown(KEY_INPUT_W)) { muki = muki_ue; catDivImg.y--; }
	else if (KeyDown(KEY_INPUT_S)) { muki = muki_shita; catDivImg.y++; }
	if (KeyDown(KEY_INPUT_A)) { muki = muki_hidari; catDivImg.x--; }
	else if (KeyDown(KEY_INPUT_D)) { muki = muki_migi; catDivImg.x++; }
	CollUpdateDivImage(&catDivImg);	//�����蔻��̍X�V

	return;
}

const float REST_TIME = 30.0f;


/// <summary>
/// �^�C�g����ʂ̕`��
/// </summary>
VOID TitleDraw(VOID)
{

	DrawImage(sampleImg);				//�T���v���摜�̕`��
	DrawDivImage(&sampleDivImg);		//�T���v�������摜�̕`��

	//�v���C���[�̓���T���v��
	{
		DrawDivImageChara(&samplePlayerImg);//�T���v�������摜�̕`��
	}

	//�L�`��
	DrawDivImageChara(&catDivImg);

	//�Q�[��������
	DrawFormatString(500, 50, GetColor(0, 0, 0), "TIME:%3.2f", GetGameTime());

	//�������Ԃ�\��
	DrawFormatString(500, 90, GetColor(0, 0, 0), "DOWN:%3.2f", REST_TIME-GetGameTime());
	

	//���݂̓��t�Ǝ���
	DrawFormatString(500, 70, GetColor(0, 0, 0), "DATE:%4d/%2d/%2d %2d:%2d:%2d", fps.NowDataTime.Year, fps.NowDataTime.Mon, fps.NowDataTime.Day, fps.NowDataTime.Hour, fps.NowDataTime.Min, fps.NowDataTime.Sec);

	DrawString(0, 0, "�^�C�g�����", GetColor(0, 0, 0));
	return;
}

/// <summary>
/// �v���C���
/// </summary>
VOID Play(VOID)
{
	PlayProc();	//����
	PlayDraw();	//�`��

	return;
}

/// <summary>
/// �v���C��ʂ̏���
/// </summary>
VOID PlayProc(VOID)
{
	if (KeyClick(KEY_INPUT_RETURN) == TRUE)
	{
		StopAudio(&playBGM);	//bgm��~

		//�v���C��ʂɐ؂�ւ�
		ChangeScene(GAME_SCENE_END);
		return;
	}

	PlayAudio(playBGM);	//bgm�Đ�

	return;
}

/// <summary>
/// �v���C��ʂ̕`��
/// </summary>
VOID PlayDraw(VOID)
{

	DrawString(0, 0, "�v���C���", GetColor(0, 0, 0));
	return;
}

/// <summary>
/// �G���h���
/// </summary>
VOID End(VOID)
{
	EndProc();	//����
	EndDraw();	//�`��

	return;
}

/// <summary>
/// �G���h��ʂ̏���
/// </summary>
VOID EndProc(VOID)
{
	if (KeyClick(KEY_INPUT_RETURN) == TRUE)
	{
		StopAudio(&endBGM);	//bgm��~

		//�^�C�g����ʂɐ؂�ւ�
		ChangeScene(GAME_SCENE_TITLE);

		return;
	}

	PlayAudio(endBGM);	//bgm�Đ�

	return;
}

/// <summary>
/// �G���h��ʂ̕`��
/// </summary>
VOID EndDraw(VOID)
{
	DrawString(0, 0, "�G���h���", GetColor(0, 0, 0));
	return;
}

/// <summary>
/// �؂�ւ����
/// </summary>
VOID Change(VOID)
{
	ChangeProc();	//����
	ChangeDraw();	//�`��

	return;
}

/// <summary>
/// �؂�ւ���ʂ̏���
/// </summary>
VOID ChangeProc(VOID)
{

	//�t�F�[�h�C��
	if (IsFadeIn == TRUE)
	{
		if (fadeInCnt > fadeInCntMax)
		{
			fadeInCnt--;	//�J�E���^�����炷
		}
		else
		{
			//�t�F�[�h�C���������I�����

			fadeInCnt = fadeInCntInit;	//�J�E���^������
			IsFadeIn = FALSE;			//�t�F�[�h�C�������I��
		}
	}

	//�t�F�[�h�A�E�g
	if (IsFadeOut == TRUE)
	{
		if (fadeOutCnt < fadeOutCntMax)
		{
			fadeOutCnt++;	//�J�E���^�𑝂₷
		}
		else
		{
			//�t�F�[�h�A�E�g�������I�����

			fadeOutCnt = fadeOutCntInit;	//�J�E���^������
			IsFadeOut = FALSE;				//�t�F�[�h�A�E�g�����I��
		}
	}

	//�؂�ւ������I��
	if (IsFadeIn == FALSE && IsFadeOut == FALSE)
	{
		//�t�F�[�h�C�����Ă��Ȃ��A�t�F�[�h�A�E�g�����Ă��Ȃ��Ƃ�
		GameScene = NextGameScene;	//���̃V�[���ɐ؂�ւ�
		OldGameScene = GameScene;	//�ȑO�̃Q�[���V�[���X�V
	}


	return;
}

/// <summary>
/// �؂�ւ���ʂ̕`��
/// </summary>
VOID ChangeDraw(VOID)
{
	//�ȑO�̃V�[����`��
	switch (OldGameScene)
	{
	case GAME_SCENE_TITLE:
		TitleDraw();	//�^�C�g����ʂ̕`��
		break;
	case GAME_SCENE_PLAY:
		PlayDraw();		//�v���C��ʂ̕`��
		break;
	case GAME_SCENE_END:
		EndDraw();		//�G���h��ʂ̕`��
		break;
	default:
		break;
	}

	//�t�F�[�h�C��
	if (IsFadeIn == TRUE)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((float)fadeInCnt / fadeInCntMax) * 255);
	}

	//�t�F�[�h�A�E�g
	if (IsFadeOut == TRUE)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((float)fadeOutCnt / fadeOutCntMax) * 255);
	}

	//�l�p��`��
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 0, 0), TRUE);

	//�������I��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(0, 0, "�؂�ւ����", GetColor(0, 0, 0));
	return;
}

/// <summary>
/// �����蔻��̗̈�X�V�i�摜�j
/// </summary>
/// <param name="img">�摜�\���̂̃|�C���^</param>
VOID CollUpdateImage(IMAGE* img)
{
	img->coll.left = img->x;
	img->coll.top = img->y;

	img->coll.right = img->x + img->width;
	img->coll.bottom = img->y + img->height;

	return;
}

/// <summary>
/// �����蔻��̗̈�X�V�i�����摜�j
/// </summary>
/// <param name="img">�摜�\���̂̃|�C���^</param>
VOID CollUpdateDivImage(DIVIMAGE* div)
{
	div->coll.left = div->x;
	div->coll.top = div->y;

	div->coll.right = div->x + div->width;
	div->coll.bottom = div->y + div->height;

	return;
}

/// <summary>
/// ��`�Ƌ�`�̓����蔻��
/// </summary>
/// <param name="a">��`A</param>
/// <param name="b">��`B</param>
/// <returns>����������TRUE/������Ȃ��Ȃ�FALSE</returns>
BOOL OnCollRect(RECT a, RECT b)
{
	if (
		a.left < b.right &&		//�@��`A�̍���X���W < ��`B�̉E��X���W�@����
		a.right > b.left &&		//�@��`A�̉E��X���W > ��`B�̍���X���W�@����
		a.top  < b.bottom &&	//�@��`A�̏��Y���W < ��`B�̉���Y���W�@����
		a.bottom > b.top		//�@��`A�̉���Y���W > ��`B�̏��Y���W
		)
	{
		//�������Ă���Ƃ�
		return TRUE;
	}
	else
	{
		//�������Ă��Ȃ��Ƃ�
		return FALSE;
	}
}


/// <summary>
/// �摜�𕪊����ă������ɓǂݍ���
/// </summary>
/// <param name="handle">�n���h���z��̐擪�A�h���X</param>
/// <param name="path">�摜�̃p�X</param>
/// <param name="bunkatuYoko">��������Ƃ��̉��̐�</param>
/// <param name="bunkatuTate">��������Ƃ��̏c�̐�</param>
/// <returns></returns>
BOOL LoadImageDivMem(DIVIMAGE* div, const char* path, int bunkatuYoko, int bunkatuTate)
{
	int IsLoad = -1;	//�摜���ǂݍ��݂����H

	//�ꎞ�I�ɉ摜�̃n���h����p�ӂ���
	int TempHandle = LoadGraph(path);

	//�ǂݍ��݃G���[
	if (TempHandle == -1)
	{
		MessageBox(
			GetMainWindowHandle(),	//�E�B���h�E�n���h��
			path,					//�{��
			"�摜�ǂݍ��݃G���[",	//�^�C�g��
			MB_OK					//�{�^��
		);

		return FALSE;	//�ǂݍ��ݎ��s
	}

	//�摜�̕��ƍ������擾
	int Width = -1;		//��
	int Height = -1;	//����
	GetGraphSize(TempHandle, &Width, &Height);

	//�������ēǂݍ���
	IsLoad = LoadDivGraph(
		path,							//�摜�̃p�X
		bunkatuYoko * bunkatuTate,		//��������
		bunkatuYoko, bunkatuTate,					//���̕���,�c�̕���
		Width / bunkatuYoko, Height / bunkatuTate,	//�摜1���̕�,����
		div->handle									//�A���ŊǗ�����z��̐擪�A�h���X
	);

	//�����G���[
	if (IsLoad == -1)
	{
		MessageBox(
			GetMainWindowHandle(),	//�E�B���h�E�n���h��
			path,					//�{��
			"�摜�����G���[",		//�^�C�g��
			MB_OK					//�{�^��
		);

		return FALSE;	//�ǂݍ��ݎ��s
	}

	//����ݒ�
	div->DivYoko = bunkatuYoko;
	div->DivTate = bunkatuTate;
	div->DivMax = div->DivYoko * div->DivTate;
	div->x = 0;
	div->y = 0;
	GetGraphSize(div->handle[0], &div->width, &div->height);
	div->AnimCnt = 0;
	div->IsAnimLoop = FALSE;
	div->nowIndex = 0;

	//�����蔻��̍X�V
	CollUpdateDivImage(div);

	//�摜��`�悷��
	div->IsDraw = TRUE;

	//�ꎞ�I�ɓǂݍ��񂾃n���h�������
	DeleteGraph(TempHandle);

	return TRUE;
}

/// <summary>
/// �摜���������ɓǂݍ���
/// </summary>
/// <param name="image">�摜�\���̂̃A�h���X</param>
/// <param name="path">�摜�̃p�X</param>
/// <returns></returns>
BOOL LoadImageMem(IMAGE* image, const char* path)
{
	//�S�[���̉摜��ǂݍ���
	strcpyDx(image->path, path);			//�p�X�̃R�s�[
	image->handle = LoadGraph(image->path);	//�摜�̓ǂݍ���

	//�摜���ǂݍ��߂Ȃ������Ƃ��́A�G���[(-1)������
	if (image->handle == -1)
	{
		MessageBox(
			GetMainWindowHandle(),	//���C���̃E�B���h�E�n���h��
			image->path,			//���b�Z�[�W�{��
			"�摜�ǂݍ��݃G���[�I",	//���b�Z�[�W�^�C�g��
			MB_OK					//�{�^��
		);

		return FALSE;	//�ǂݍ��ݎ��s
	}

	//�摜�̕��ƍ������擾
	GetGraphSize(image->handle, &image->width, &image->height);

	//�摜�̈ʒu��������
	image->x = 0; image->y = 0;

	//�����蔻��̍X�V
	CollUpdateImage(image);

	//�摜��`�悷��
	image->IsDraw = TRUE;

	//�ǂݍ��߂�
	return TRUE;
}

/// <summary>
/// �摜�`��
/// </summary>
/// <param name="image">�`�悷��摜�\����</param>
/// <returns></returns>
/// <returns></returns>
VOID DrawImage(IMAGE image)
{
	//�摜���`��ł���Ƃ���
	if (image.IsDraw == TRUE)
	{
		DrawGraph(image.x, image.y, image.handle, TRUE);
	}

	//�f�o�b�O���[�h�̂Ƃ���
	if (GAME_DEBUG == TRUE)
	{
		//�����蔻���`��
		DrawRect(image.coll, GetColor(255, 255, 255), FALSE);
	}
	return;
}

/// <summary>
/// �����摜�̕`��
/// </summary>
/// <param name="image">�`�悷��摜�\����</param>
/// <returns></returns>
/// <returns></returns>
VOID DrawDivImage(DIVIMAGE* image)
{
	//�摜���`��ł���Ƃ���
	if (image->IsDraw == TRUE)
	{
		DrawGraph(image->x, image->y, image->handle[image->nowIndex], TRUE);

		//�A�j���[�V�����̃J�E���g�A�b�v
		if (image->AnimCnt < image->AnimCntMAX) { image->AnimCnt++; }
		else
		{
			//���ׂẴA�j���[�V������`�悵�I�������
			if (image->nowIndex == image->DivMax - 1)
			{
				//�A�j���[�V�������J��Ԃ��Ȃ��Ȃ��
				if (image->IsAnimLoop == FALSE)
				{
					image->IsDraw = FALSE;	//�`����~�߂�
				}
				image->AnimCnt = 0;		//�J�E���^0�N���A
				image->nowIndex = 0;	//�擪�ɖ߂�
			}
			//���̕����摜������Ƃ���
			else if (image->nowIndex < image->DivMax - 1)
			{
				image->nowIndex++; //���̉摜��
			}
			image->AnimCnt = 0;	//�J�E���^0�N���A
		}
	}

	//�f�o�b�O���[�h�̂Ƃ���
	if (GAME_DEBUG == TRUE)
	{
		//�����蔻���`��
		DrawRect(image->coll, GetColor(255, 255, 255), FALSE);
	}
	return;
}

/// <summary>
/// �����摜�̕`��(�L�����Ȃ�)
/// </summary>
/// <param name="image">�`�悷��摜�\����</param>
/// <returns></returns>
/// <returns></returns>
VOID DrawDivImageChara(DIVIMAGE* image)
{
	//�摜���`��ł���Ƃ���
	if (image->IsDraw == TRUE)
	{
		DrawGraph(image->x, image->y, image->handle[image->nowIndex], TRUE);

		//�A�j���[�V�����̃J�E���g�A�b�v
		if (image->AnimCnt < image->AnimCntMAX) { image->AnimCnt++; }
		else
		{

			//�E�����̂Ƃ�(�摜�ɂ���Đ������Ⴄ�̂ŁA���킹�邱�ƁI)
			if (muki == muki_migi)
			{
				if (image->nowIndex >= 6 && image->nowIndex < 8)
				{
					image->nowIndex++;
				}
				else
				{
					image->nowIndex = 6;
				}
			}

			//�������̂Ƃ�(�摜�ɂ���Đ������Ⴄ�̂ŁA���킹�邱�ƁI)
			if (muki == muki_hidari)
			{
				if (image->nowIndex >= 3 && image->nowIndex < 5)
				{
					image->nowIndex++;
				}
				else
				{
					image->nowIndex = 3;
				}
			}

			//������̂Ƃ�(�摜�ɂ���Đ������Ⴄ�̂ŁA���킹�邱�ƁI)
			if (muki == muki_ue)
			{
				if (image->nowIndex >= 9 && image->nowIndex < 11)
				{
					image->nowIndex++;
				}
				else
				{
					image->nowIndex = 9;
				}
			}

			//�������̂Ƃ�(�摜�ɂ���Đ������Ⴄ�̂ŁA���킹�邱�ƁI)
			if (muki == muki_shita)
			{
				if (image->nowIndex >= 0 && image->nowIndex < 2)
				{
					image->nowIndex++;
				}
				else
				{
					image->nowIndex = 0;
				}
			}

			//���������̂Ƃ��́A���O�̌����̐^�񒆂̉摜�ɂ���(�摜�ɍ��킹�Č��߂ăl)
			if (muki == muki_none)
			{
				if (image->nowIndex >= 6 && image->nowIndex <= 8) { image->nowIndex = 7; }
				if (image->nowIndex >= 3 && image->nowIndex <= 5) { image->nowIndex = 4; }
				if (image->nowIndex >= 9 && image->nowIndex <= 11) { image->nowIndex = 10; }
				if (image->nowIndex >= 0 && image->nowIndex <= 2) { image->nowIndex = 1; }
			}

			image->AnimCnt = 0;	//�J�E���^0�N���A
		}
	}

	//�f�o�b�O���[�h�̂Ƃ���
	if (GAME_DEBUG == TRUE)
	{
		//�����蔻���`��
		DrawRect(image->coll, GetColor(255, 255, 255), FALSE);
	}
	return;
}

/// <summary>
/// ���y���������ɓǂݍ���
/// </summary>
/// <param name="audio">Audio�\���̕ϐ��̃A�h���X</param>
/// <param name="path">Audio�̉��y�p�X</param>
/// <param name="volume">�{�����[��</param>
/// <param name="playType">DX_PLAYTYPE_LOOP or DX_PLAYTYPE_BACK</param>
/// <returns></returns>
BOOL LoadAudio(AUDIO* audio, const char* path, int Volume, int playType)
{
	//���y�̓ǂݍ���
	strcpyDx(audio->path, path);					//�p�X�̃R�s�[
	audio->handle = LoadSoundMem(audio->path);		//���y�̓ǂݍ���

	//���y���ǂݍ��߂Ȃ������Ƃ��́A�G���[(-1)������
	if (audio->handle == -1)
	{
		MessageBox(
			GetMainWindowHandle(),	//���C���̃E�B���h�E�n���h��
			audio->path,			//���b�Z�[�W�{��
			"���y�ǂݍ��݃G���[�I",		//���b�Z�[�W�^�C�g��
			MB_OK					//�{�^��
		);

		return FALSE;	//�ǂݍ��ݎ��s
	}

	//���̑��̐ݒ�
	audio->Volume = Volume;
	audio->playType = playType;

	return TRUE;
}

/// <summary>
/// ���y�Đ�
/// </summary>
/// <param name="audio">�Đ����鉹�y�\����</param>
/// <returns></returns>
VOID PlayAudio(AUDIO audio)
{
	//���[�v�Đ��łȂ���΁A���̂܂܍Đ�����
	if (audio.playType == DX_PLAYTYPE_BACK)
	{
		PlaySoundMem(audio.handle, audio.playType);//���y�̍Đ�
	}
	//���[�v�Đ��̂Ƃ��́A���y���Đ�����Ă��Ȃ���΁A�Đ�����
	else if (audio.playType == DX_PLAYTYPE_LOOP)
	{
		if (CheckSoundMem(audio.handle) == 0)
		{
			PlaySoundMem(audio.handle, audio.playType);//���y�̍Đ�
		}
	}

	return;
}

/// <summary>
/// ���y�̃{�����[���擾
/// </summary>
/// <param name="audio">�擾���鉹�y�\����</param>
/// <param name = "volume">�{�����[��(0�`255)</param>
/// <returns></returns>
int GetVolumeAudio(AUDIO audio)
{
	//���ʂ��擾
	return audio.Volume;
}

/// <summary>
/// ���y�̃{�����[���ݒ�
/// </summary>
/// <param name="audio">�ݒ肷�鉹�y�\����</param>
/// <param name = "volume">�{�����[��(0�`255)</param>
/// <returns></returns>
VOID SetVolumeAudio(AUDIO* audio, int vol)
{
	//���ʂ�ݒ�
	audio->Volume = vol;
	ChangeVolumeSoundMem(audio->Volume, audio->handle);

	return;
}

/// <summary>
/// ���y�̃{�����[���ύX
/// </summary>
/// <param name="audio">�ύX���鉹�y�\����</param>
/// <param name = "volume">�{�����[��(0�`255)</param>
/// <returns></returns>
VOID ChangeVolumeAudio(AUDIO* audio, int vol)
{
	//���ʂ�ݒ�i�\���̂̃{�����[���͕ύX���Ȃ��j
	ChangeVolumeSoundMem(vol, audio->handle);

	return;
}

/// <summary>
/// ���y��~
/// </summary>
/// <param name="audio">��~���鉹�y�\����</param>
/// <returns></returns>
VOID StopAudio(AUDIO* audio)
{
	//���y�̒�~
	StopSoundMem(audio->handle);

	return;
}