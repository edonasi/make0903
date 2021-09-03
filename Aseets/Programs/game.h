#pragma once

//�Q�[���S�̂̃w�b�_�t�@�C��

//�w�b�_�[�t�@�C���̓ǂݍ���
#include "DxLib.h"		//DxLib���g���Ƃ��͕K�v
#include <math.h>		//���w�n
#include <string.h>		//������n
#include <time.h>		//���Ԍn

//�}�N����`
#define GAME_TITLE	"�Q�[���^�C�g��"	//�Q�[���^�C�g��
#define GAME_WIDTH	1280				//�Q�[����ʂ̕�(�E�B�h�X)
#define GAME_HEIGHT	720					//�Q�[����ʂ̍���(�n�C�g)
#define GAME_COLOR  32					//�Q�[���̐F��

#define GAME_ICON_ID	333				//�Q�[����ICON��ID

#define GAME_WINDOW_BAR	0				//�E�B���h�E�o�[�̎��

#define GAME_DEBUG	TRUE				//�f�o�b�O���[�h

#define PATH_MAX	255					//�p�X�̒���
#define STR_MAX		255					//�����̒���
#define IMGDIV_MAX	128					//�n���h���̍ő吔(�C��)

//�񋓌^
enum GAME_SCENE {
	GAME_SCENE_TITLE,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
	GAME_SCENE_CHANGE
};	//�Q�[���̃V�[��

//�摜�̍\����
struct IMAGE
{
	int handle = -1;		//�摜�̃n���h��(�Ǘ��ԍ�)
	char path[PATH_MAX];	//�摜�̏ꏊ(�p�X)

	int x = -1;				//X�ʒu
	int y = -1;				//Y�ʒu
	int width = -1;			//��
	int height = -1;		//����

	RECT coll;				//�����蔻��̗̈�(�l�p)

	BOOL IsDraw = FALSE;	//�摜���`��ł���H
};

//�A������摜�̍\����
struct DIVIMAGE
{
	int DivMax;						//������
	int handle[IMGDIV_MAX];			//�摜�n���h��
	int nowIndex = 0;				//���݂̃n���h���z��̃C���f�b�N�X
	char path[PATH_MAX];			//�p�X

	int x = -1;						//X�ʒu
	int y = -1;						//Y�ʒu
	int width = -1;					//��
	int height = -1;				//����

	int DivYoko = -1;				//���̕�����
	int DivTate = -1;				//�c�̕�����

	RECT coll;						//�����蔻��̗̈�(�l�p)

	BOOL IsDraw = FALSE;			//�`��ł��邩�H

	int AnimCnt = 0;				//�A�j���[�V�����J�E���^
	int AnimCntMAX = 2;				//�A�j���[�V�����J�E���^MAX
	BOOL IsAnimLoop = FALSE;		//�A�j���[�V���������[�v�����邩�H
};

//����̍\����
struct MOVIE
{
	int handle = -1;		//����̃n���h��
	char path[PATH_MAX];	//����̃p�X

	int x = -1;				//X�ʒu
	int y = -1;				//Y�ʒu
	int width = -1;			//��
	int height = -1;		//����

	int Volume;				//�{�����[���iMIN 0 �` 255 MAX�j�@
};

//���y�̍\����
struct AUDIO
{
	int handle = -1;		//���y�̃n���h��
	char path[PATH_MAX];	//���y�̃p�X

	int Volume = -1;		//�{�����[���iMIN 0 �` 255 MAX�j
	int playType = -1;		//BGM or SE
};

//########## �O���̃O���[�o���ϐ� ##########
extern DIVIMAGE samplePlayerImg;

//########## �v���g�^�C�v�錾 ##########
//��extern �́A�O���Ɋ֐�������܂���I�Ƃ����ڈ�ł��Ă��܂��B

extern BOOL GameLoad(VOID);	//�f�[�^��Ǎ�
extern VOID GameInit(VOID);	//�f�[�^�̏�����
extern VOID GameDelete(VOID);	//�f�[�^���폜

extern VOID Title(VOID);		//�^�C�g�����
extern VOID TitleProc(VOID);	//�^�C�g�����(����)
extern VOID TitleDraw(VOID);	//�^�C�g�����(�`��)

extern VOID Play(VOID);		//�v���C���
extern VOID PlayProc(VOID);	//�v���C���(����)
extern VOID PlayDraw(VOID);	//�v���C���(�`��)

extern VOID End(VOID);			//�G���h���
extern VOID EndProc(VOID);		//�G���h���(����)
extern VOID EndDraw(VOID);		//�G���h���(�`��)

extern VOID Change(VOID);		//�؂�ւ����
extern VOID ChangeProc(VOID);	//�؂�ւ����(����)
extern VOID ChangeDraw(VOID);	//�؂�ւ����(�`��)

extern VOID ChangeScene(GAME_SCENE scene);		//�V�[���؂�ւ�
extern BOOL OnCollRect(RECT a, RECT b);		//��`�Ƌ�`�̓����蔻��
extern VOID CollUpdateImage(IMAGE* img);		//�摜�̓����蔻��̍X�V
extern VOID CollUpdateDivImage(DIVIMAGE* div);	//�����摜�̓����蔻��̍X�V
extern BOOL LoadImageMem(IMAGE* image, const char* path);										//�Q�[���̉摜��ǂݍ���
extern BOOL LoadAudio(AUDIO* audio, const char* path, int Volume, int playType);				//�Q�[���̉��y��ǂݍ���
extern BOOL LoadImageDivMem(DIVIMAGE* div, const char* path, int bunkatuYoko, int bunkatuTate);//�Q�[���̉摜�̕����ǂݍ���

extern VOID PlayAudio(AUDIO audio);					//���y�Đ�
extern int GetVolumeAudio(AUDIO audio);				//���y�̃{�����[���擾
extern VOID SetVolumeAudio(AUDIO* audio, int vol);		//���y�̃{�����[���ݒ�
extern VOID ChangeVolumeAudio(AUDIO* audio, int vol);	//���y�̃{�����[���ύX
extern VOID StopAudio(AUDIO* audio);					//���y��~

extern VOID DrawImage(IMAGE image);							//�摜�`��
extern VOID DrawDivImage(DIVIMAGE* image);					//�����摜�̕`��
extern VOID DrawDivImageChara(DIVIMAGE* image);				//�����摜�̕`��