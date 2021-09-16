#include "Data.h"
#include "game.h"
#include "shape.h"

/*
http://www.isl.ne.jp/pcsp/beginC/C_Language_16.html
https://9cguide.appspot.com/17-01.html
*/

CHARA_DATA_SAMPLE enemy[ENEMY_MAX];	//�G�f�[�^

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