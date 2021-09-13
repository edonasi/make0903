#pragma once

//�Q�[���̃��C���w�b�_�t�@�C��
#include "game.h"

//define
//�t�H���g�n
#define FONT_JIYU_PATH		TEXT(".\\Aseets\\Fonts\\Jiyucho.ttf")		//�t�H���g�̏ꏊ
#define FONT_JIYU_NAME		TEXT("���䂤���傤�t�H���g")	//�t�H���g�̖��O

#define FONT_DOT_PATH		TEXT(".\\Aseets\\Fonts\\DotGothic16-Regular.ttf")		//�t�H���g�̏ꏊ
#define FONT_DOT_NAME		TEXT("DotGothic16")				//�t�H���g�̖��O

#define FONT_REGGAE_PATH		TEXT(".\\Aseets\\Fonts\\ReggaeOne-Regular.ttf")		//�t�H���g�̏ꏊ
#define FONT_REGGAE_NAME		TEXT("Reggae One")				//�t�H���g�̖��O

#define FONT_MSGOTH_NAME	TEXT("MS�@�S�V�b�N")			//�t�H���g��

#define DEF_FONT_NAME	FONT_JIYU_NAME				//�f�t�H���g�̃t�H���g��
#define DEF_FONT_SIZE	20							//�f�t�H���g�̃T�C�Y
#define DEF_FONT_THINCK	1							//�f�t�H���g�̑���
#define DEF_FONT_TYPE	DX_FONTTYPE_ANTIALIASING	//�f�t�H���g�̃^�C�v

//�G���[���b�Z�[�W
#define FONT_INSTALL_ERR_TITLE	TEXT("�t�H���g�C���X�g�[���G���[")
#define FONT_CREATE_ERR_TITLE	TEXT("�t�H���g�쐬�G���[")

//�\����
//�t�H���g�\����
struct FONT
{
	int handle;		//�t�H���g�n���h��
	int size;		//�t�H���g�̃T�C�Y
	int thinck;		//�t�H���g�̑���
	int type = DX_FONTTYPE_ANTIALIASING;	//�t�H���g�̃^�C�v
	char name[STR_MAX];	//�t�H���g�̖��O
};

//�t�H���g�֘A
extern FONT fontdef;
extern FONT sampleFont1;
extern FONT sampleFont2;
extern FONT dotFont;		//�h�b�g�̃t�H���g
extern FONT reggaeFont;		//�ǉ��̃t�H���g

extern BOOL FontAdd(VOID);		//�t�H���g�̓ǂݍ���
extern BOOL FontCreate(VOID);	//�t�H���g�̍쐬
extern VOID SetFont(			//�t�H���g�ݒ�
	FONT* f, const char* name, int size, int thinck, int type);
extern BOOL FontCreateHandle(FONT* f);	//�t�H���g�n���h������G�t
extern VOID SetDefaultFont(FONT f);	//�t�H���g��S�̂ɔ��f������
extern VOID FontDelete(VOID);			//�t�H���g�폜
extern VOID FontRemove(VOID);			//�t�H���g�폜