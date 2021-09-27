#include "Data.h"
#include "game.h"
#include "shape.h"

/*
http://www.isl.ne.jp/pcsp/beginC/C_Language_16.html
https://9cguide.appspot.com/17-01.html
*/

CHARA_DATA_SAMPLE enemy[ENEMY_MAX];	//�G�f�[�^
SCORE_DATA_SAMPLE scoreData;			//�X�R�A�f�[�^
SCORE_DATA_SAMPLE scoreDataInit;		//�X�R�A�f�[�^(�������p)

/// <summary>
/// SCV�t�@�C����ǂݍ���
/// </summary>
/// <param name="path">CSV�t�@�C���̃p�X</param>
/// <param name="chara">�L�����f�[�^�\���̂̐擪�A�h���X</param>
/// <param name="dataMax">CSV�t�@�C���̍ő�l</param>
/// <param name="isHeader">CSV�t�@�C����1�s�ڂ��w�b�_�Ȃ�TRUE</param>
/// <returns>TRUE�œǂݍ��߂�</returns>
BOOL LoadScvChara(const char* path, CHARA_DATA_SAMPLE* chara, int dataMax, BOOL isHeader) 
{
	FILE* fp;					//�t�@�C���|�C���^
	char getChar = '\0';		//�擾���镶��
	int loopCnt = 0;			//���[�v�J�E���^
	errno_t fileErr = NULL;		//�t�@�C���ǂݍ��݃G���[���m�F
	int isEOF = NULL;			//�t�@�C���̏I��肩�`�F�b�N

	fileErr = fopen_s(&fp, path, "r");	//�t�@�C����ǂݍ��݃��[�h(r)�ŊJ��
	if (fileErr != NULL) 
	{
		MessageBox(GetMainWindowHandle(), path, CSV_LOAD_ERR_TITLE, MB_OK);	//�ǂݍ��݃G���[
		return FALSE;
	}

	//	���������琳��ɓǂݍ��߂����̏���

	//csv��1�s�ڂ��w�b�_�̂Ƃ�
	if (isHeader == TRUE) 
	{
		//1���������o���A���s���q���g��1�s�ڂ�ǂݔ�΂�
		while (getChar != '\n') { getChar = fgetc(fp); }
	}

	//���ۂɃf�[�^���i�[����
	while (isEOF != EOF)	//�t�@�C���̍Ō�ł͂Ȃ��Ƃ��J��Ԃ�
	{
		//csv�̃f�[�^��1�s����ǂݎ��
		//fp = �J�[�\���̃C���[�W
		isEOF = fscanf_s(
			fp,
			CSV_CHARA_FORMAT,
			&(chara + loopCnt)->no,
			&(chara + loopCnt)->name[0], STR_MAX,
			&(chara + loopCnt)->hp,
			&(chara + loopCnt)->atk,
			&(chara + loopCnt)->def,
			&(chara + loopCnt)->rak,
			&(chara + loopCnt)->hpMax,
			&(chara + loopCnt)->atkMax,
			&(chara + loopCnt)->defMax,
			&(chara + loopCnt)->rakMax
			);

		//���̃f�[�^��
		loopCnt++;
	}

	//�f�[�^�̐����Ⴄ�Ƃ�
	if (loopCnt - 1 != dataMax) 
	{
		MessageBox(GetMainWindowHandle(), path, CSV_DATA_ERR_TITLE, MB_OK);
		return FALSE;
	}

	fclose(fp);	//�t�@�C�������

	return TRUE;
}

/// <summary>
/// �X�R�A�f�[�^��ǂݍ���
/// </summary>
/// <param name="path">�X�R�A�f�[�^�̃p�X</param>
/// <param name="chara">�X�R�A�f�[�^�\���̂̐擪�A�h���X</param>
/// <param name="isHeader">CSV�t�@�C����1�s�ڂ��w�b�_�Ȃ�TRUE</param>
/// <returns>TRUE�œǂݎ�萬��</returns>
BOOL LoadScoreData(const char* path, SCORE_DATA_SAMPLE* score, BOOL isHeader = FALSE) 
{
	FILE* fp;					//�t�@�C���|�C���^
	char getChar = '\0';		//�擾���镶��
	errno_t fileErr = NULL;		//�t�@�C���ǂݍ��݃G���[���m�F
	int isEOF = NULL;			//�t�@�C���̏I��肩�`�F�b�N

	SetScoreDataPath(path);		//�p�X�̃R�s�[

	fileErr = fopen_s(&fp, path, "r");	//�t�@�C����ǂݍ��݃��[�h(r)�ŊJ��
	if (fileErr != NULL)
	{
		//�X�R�A�f�[�^�̍쐬
		if (CreateScoreData() == FALSE) { return FALSE; }

		//�����܂ł̏����ŃX�R�A�f�[�^�͕K�������

		fileErr = fopen_s(&fp, path, "r");
		if (fileErr != NULL)
		{
			MessageBox(GetMainWindowHandle(), path, SCORE_LOAD_ERR_TITLE, MB_OK);	//�ǂݍ��݃G���[
			return FALSE;
		}
	}

	//	���������琳��ɓǂݍ��߂����̏���

	//csv��1�s�ڂ��w�b�_�̂Ƃ�
	if (isHeader == TRUE)
	{
		//1���������o���A���s���q���g��1�s�ڂ�ǂݔ�΂�
		while (getChar != '\n') { getChar = fgetc(fp); }
	}

	//���ۂɃf�[�^���i�[����
	isEOF = fscanf_s(
		fp,
		SCORE_DATA_FORMAT,	//�f�[�^���u��s=���R�[�h�v�ŏ�����Ă���̂��|�C���g�I
		&(score)->name1, STR_MAX,	//�������ǂݍ��ނƂ��́A���̈����ŕ�����ő吔���w�肷��
		&(score)->score1,
		&(score)->name2, STR_MAX,	//�������ǂݍ��ނƂ��́A���̈����ŕ�����ő吔���w�肷��
		&(score)->score2,
		&(score)->name3, STR_MAX,	//�������ǂݍ��ނƂ��́A���̈����ŕ�����ő吔���w�肷��
		&(score)->score3
	);

	fclose(fp);	//�t�@�C�������

	return TRUE;
}

//�X�R�A�f�[�^�쐬
BOOL CreateScoreData(VOID) 
{
	//����������X�R�A�f�[�^�����
	FILE* creFp;
	errno_t creFileErr = NULL;	//�t�@�C���ǂݍ��݃G���[���m�F

	//�t�@�C�����������݃��[�h�ŊJ��(�쐬����)
	creFileErr = fopen_s(&creFp, GetScoreDataPath(), "w");
	if (creFileErr != NULL) 
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_CREATE_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�w�b�_����������
	fprintf_s(
		creFp, "Name1,Score1,Name2,Score2,Name3,Score3\n"
	);

	//��̃X�R�A�f�[�^����������
	fprintf_s(
		creFp, "%s,%d,%s,%d,%s,%d",
		scoreDataInit.name1, scoreDataInit.score1,
		scoreDataInit.name2, scoreDataInit.score2,
		scoreDataInit.name3, scoreDataInit.score3
	);

	//�X�R�A�f�[�^�����
	fclose(creFp);

	MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_CREATE_TITLE, MB_OK);
	return TRUE;
}

//�X�R�A�f�[�^�ۑ�
BOOL SaveScoreData(VOID) 
{
	//����������X�R�A�f�[�^�����
	FILE* creFp;
	errno_t creFileErr = NULL;	//�t�@�C���ǂݍ��݃G���[���m�F

	//�t�@�C�����������݃��[�h�ŊJ��(�쐬����)
	creFileErr = fopen_s(&creFp, GetScoreDataPath(), "w");
	if (creFileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_CREATE_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�w�b�_����������
	fprintf_s(
		creFp, "Name1,Score1,Name2,Score2,Name3,Score3\n"
	);

	//��̃X�R�A�f�[�^����������
	fprintf_s(
		creFp, "%s,%d,%s,%d,%s,%d",
		scoreData.name1, scoreData.score1,
		scoreData.name2, scoreData.score2,
		scoreData.name3, scoreData.score3
	);

	//�X�R�A�f�[�^�����
	fclose(creFp);

	MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_SAVE_TITLE, MB_OK);
	return TRUE;
}

//�X�R�A�f�[�^�폜
BOOL DeleteScoreData(VOID) 
{
//�t�@�C���폜
	if (remove(GetScoreDataPath()) != 0)
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_DELETE_ERR_TITLE, MB_OK);
	}
	else 
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_DELETE_TITLE, MB_OK);
	}

	//�X�R�A�f�[�^�쐬
	return CreateScoreData();
}

//�X�R�A�f�[�^�̃p�X��Ԃ�
const char* GetScoreDataPath(VOID) 
{
	return scoreData.path;
}

/// <summary>
/// �X�R�A�f�[�^�̃p�X��ݒ肷��
/// </summary>
/// <param name="path"></param>
VOID SetScoreDataPath(const char* path) 
{
	strcpyDx(scoreData.path, path);
	return;
}