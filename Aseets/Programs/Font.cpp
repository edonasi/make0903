//�w�b�_�t�@�C���ǂݍ���
#include "Font.h"
#include "game.h"

/*
���t�H���g���ꎞ�I�ɃC���X�g�[��

�@���n���h���Ńt�H���g���Ǘ�

�@��

�@���n���h�������

���t�H���g���ꎞ�I�ɃA���C���X�g�[��
*/

//�O���[�o���ϐ�
FONT fontdef;		//�f�t�H���g�̃t�H���g
FONT sampleFont1;	//�T���v���̃t�H���g
FONT sampleFont2;	//�T���v���̃t�H���g(�ǂݍ���)
FONT dotFont;
FONT reggaeFont;

/// <summary>
/// �t�H���g�̓ǂݍ���
/// </summary>
/// <param name=""></param>
/// <returns></returns>
BOOL FontAdd(VOID) 
{
	//�t�H���g���ꎞ�I�ɓǂݍ���(WinApi)
	if (AddFontResourceEx(FONT_JIYU_PATH, FR_PRIVATE, NULL) == 0)
	{
		//�G���[���b�Z�[�W
		MessageBox(
			GetMainWindowHandle(),
			FONT_JIYU_NAME,
			FONT_INSTALL_ERR_TITLE,
			MB_OK
		);

		return FALSE;
	}

	//�t�H���g���ꎞ�I�ɓǂݍ���(WinApi)
	if (AddFontResourceEx(FONT_DOT_PATH, FR_PRIVATE, NULL) == 0)
	{
		//�G���[���b�Z�[�W
		MessageBox(
			GetMainWindowHandle(),
			FONT_DOT_NAME,
			FONT_INSTALL_ERR_TITLE,
			MB_OK
		);

		return FALSE;
	}

	//�t�H���g���ꎞ�I�ɓǂݍ���(WinApi)
	if (AddFontResourceEx(FONT_REGGAE_PATH, FR_PRIVATE, NULL) == 0)
	{
		//�G���[���b�Z�[�W
		MessageBox(
			GetMainWindowHandle(),
			FONT_REGGAE_NAME,
			FONT_INSTALL_ERR_TITLE,
			MB_OK
		);

		return FALSE;
	}

	//�ǂݍ��ݐ���
	return TRUE;
}

//�t�H���g�̍쐬
BOOL FontCreate(VOID) 
{
	//�f�t�H���g�̃t�H���g�̏���������
	SetFont(
		&fontdef,			//�ݒ肷��t�H���g
		DEF_FONT_NAME,		//�t�H���g�̖��O���R�s�[
		DEF_FONT_SIZE,		//�t�H���g�̃T�C�Y
		DEF_FONT_THINCK,	//�t�H���g�̑���
		DEF_FONT_TYPE		//�t�H���g�̃^�C�v
	);

	//�f�t�H���g�t�H���g�̃n���h�����쐬
	if (FontCreateHandle(&fontdef) == FALSE) { return FALSE; }

	//�f�t�H���g�t�H���g��S�̂ɔ��f
	SetDefaultFont(fontdef);

	//�T���v���t�H���g�̏���ݒ�
	SetFont(
		&sampleFont1,
		FONT_MSGOTH_NAME,
		32,
		5,
		DX_FONTTYPE_ANTIALIASING
	);

	//�T���v���t�H���g�̃n���h�����쐬
	if (FontCreateHandle(&sampleFont1) == FALSE) { return FALSE; }

	//�T���v���t�H���g�̏���ݒ�
	SetFont(
		&sampleFont2,
		FONT_JIYU_NAME,
		64,
		1,
		DX_FONTTYPE_ANTIALIASING
	);

	//�T���v���t�H���g�̃n���h�����쐬
	if (FontCreateHandle(&sampleFont2) == FALSE) { return FALSE; }

	//�h�b�g�T���v���t�H���g�̏���ݒ�
	SetFont(
		&dotFont,
		FONT_DOT_NAME,
		32,
		1,
		DX_FONTTYPE_ANTIALIASING
	);

	//�h�b�g�T���v���t�H���g�̃n���h�����쐬
	if (FontCreateHandle(&dotFont) == FALSE) { return FALSE; }

	//�h�b�g�T���v���t�H���g�̏���ݒ�
	SetFont(
		&reggaeFont,
		FONT_REGGAE_NAME,
		32,
		1,
		DX_FONTTYPE_ANTIALIASING
	);

	//�h�b�g�T���v���t�H���g�̃n���h�����쐬
	if (FontCreateHandle(&reggaeFont) == FALSE) { return FALSE; }

	return TRUE;
}

/// <summary>
/// �����̃t�H���g�\���̂֐ݒ肷��
/// </summary>
/// <param name="f">�ݒ肷��t�H���g�\����</param>
/// <param name="name">�t�H���g��</param>
/// <param name="size">�t�H���g�̃T�C�Y</param>
/// <param name="thinck">�t�H���g�̑���</param>
/// <param name="type">�t�H���g�̃^�C�v</param>
VOID SetFont(FONT* f, const char* name, int size, int thinck, int type) 
{
	strcpy_sDx(f->name, STR_MAX, name);	//���O
	f->size = size;						//�T�C�Y
	f->thinck = thinck;					//����
	f->type = type;						//�^�C�v
	return;
}

/// <summary>
/// �t�H���g�n���h�����쐬
/// </summary>
/// <param name="f">�t�H���g�\����</param>
/// <returns></returns>
BOOL FontCreateHandle(FONT* f) 
{
	//��CreateFontToHandle��DX���C�u�����̊֐�
	f->handle = CreateFontToHandle(
		f->name,
		f->size,
		f->thinck,
		f->type
	);

	//�n���h�����ǂݍ��܂�Ȃ��Ȃ玸�s
	if (f->handle == -1) { return FALSE; }

	return TRUE;
}

/// <summary>
/// �t�H���g��S�̂ɔ��f������
/// </summary>
/// <param name="f">�ݒ肷��t�H���g�\����</param>
VOID SetDefaultFont(FONT f) 
{
	ChangeFont(f.name);	//���O	//��ChangeFontDX���C�u�����̊֐��ŏd������
	SetFontSize(f.size);		//�T�C�Y
	SetFontThickness(f.thinck);	//����
	ChangeFontType(f.type);		//�^�C�v
}

//�t�H���g�폜
VOID FontDelete(VOID) 
{
	DeleteFontToHandle(fontdef.handle);

	DeleteFontToHandle(sampleFont1.handle);
	DeleteFontToHandle(sampleFont2.handle);
}

//�E�B���h�E�ɓ����Ă��Ȃ��ǂݍ��񂾃t�H���g�폜
VOID FontRemove(VOID) 
{
	//�ꎞ�I�ɓǂݍ��񂾃t�H���g���폜(WinApi)
	RemoveFontResourceEx(FONT_JIYU_PATH, FR_PRIVATE, NULL);
	RemoveFontResourceEx(FONT_DOT_PATH, FR_PRIVATE, NULL);
	RemoveFontResourceEx(FONT_REGGAE_PATH, FR_PRIVATE, NULL);
}