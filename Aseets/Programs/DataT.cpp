//��Data�n�̃\�[�X�t�@�C��

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "game.h"
#include "DataT.h"
#include "shape.h"		//�}�`�̏���

//########## �O���[�o���ϐ� ##########
CHARA_DATA enemy[ENEMY_MAX];	//�G�f�[�^

SCORE_DATA score_data;			//�X�R�A�f�[�^
SCORE_DATA score_dataInit = { SCORE_DATA_PATH,"NAME1",-1,"NAME2",-1, "NAME3",-1 };	//�X�R�A�f�[�^(�������p)

//########## �֐� ##########

/// <summary>
/// CSV�t�@�C����ǂݍ��ށiCHARA_DATA�j
/// </summary>
/// <param name="path">CSV�t�@�C���̃p�X</param>
/// <param name="chara">�L�����f�[�^�\���̂̐擪�A�h���X</param>
/// <param name="DataMax">CSV�t�@�C���̍ő吔</param>
/// <param name="IsHeader">CSV�t�@�C���̂P�s�ڂ��w�b�_�Ȃ�TRUE</param>
/// <returns>TRUE�͓ǂݍ��߂�/FALSE�͎��s����</returns>
BOOL LoadCSVChara(const char* path, CHARA_DATA* chara, int DataMax, BOOL IsHeader = FALSE)
{
	FILE* fp;				//�t�@�C���|�C���^
	char GetChar = '\0';	//�擾���镶��
	int LoopCnt = 0;		//���[�v�J�E���^
	errno_t FileErr = NULL;	//�t�@�C���ǂݍ��݃G���[���m�F
	int IsEOF = NULL;		//�t�@�C���̏I��肩�`�F�b�N

	FileErr = fopen_s(&fp, path, "r");	//�t�@�C����ǂݍ��݃��[�h(r)�ŊJ��
	if (FileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), path, CSV_LOAD_ERR_TITLE, MB_OK);	//�ǂݍ��݃G���[
		return FALSE;
	}

	//�������琳��ɓǂݍ��߂��Ƃ��̏���****************************************

	//CSV��1�s�ڂ��w�b�_�̂Ƃ�
	if (IsHeader == TRUE)
	{
		//�P���������o���A���s���q���g�ɂP�s�ڂ�ǂݔ�΂�
		while (GetChar != '\n')
		{ 
			GetChar = fgetc(fp); 
		}
	}

	//���ۂɃf�[�^���i�[����
	while (IsEOF != EOF)	//End Of File�i�t�@�C���̍Ō�j�ł͂Ȃ��Ƃ��J��Ԃ�
	{
		//CSV�̃f�[�^�̂P�s����ǂݎ��
		IsEOF = fscanf_s(
			fp,
			CSV_CHARA_FORMAT,
			&(chara + LoopCnt)->No,
			&(chara + LoopCnt)->Name[0], STR_MAX,
			&(chara + LoopCnt)->HP,
			&(chara + LoopCnt)->ATK,
			&(chara + LoopCnt)->DEF,
			&(chara + LoopCnt)->RAK,
			&(chara + LoopCnt)->MAX_HP,
			&(chara + LoopCnt)->MAX_ATK,
			&(chara + LoopCnt)->MAX_DEF,
			&(chara + LoopCnt)->MAX_RAK
		);

		//���̃f�[�^��
		LoopCnt++;
	}

	//�f�[�^�̐����Ⴄ�Ƃ�
	if (LoopCnt - 1 != DataMax)
	{
		MessageBox(GetMainWindowHandle(), path, CSV_DATANUM_ERR_TITLE, MB_OK);	//�ǂݍ��݃G���[
		return FALSE;
	}

	fclose(fp);	//�t�@�C�������

	return TRUE;
}

/// <summary>
/// �X�R�A�f�[�^��ǂݍ��ށiSCORE_DATA�j
/// </summary>
/// <param name="path">�X�R�A�f�[�^�̃p�X</param>
/// <param name="chara">�X�R�A�f�[�^�\���̂̐擪�A�h���X</param>
/// <param name="IsHeader">CSV�t�@�C���̂P�s�ڂ��w�b�_�Ȃ�TRUE</param>
/// <returns>TRUE�͓ǂݍ��߂�/FALSE�͎��s����</returns>
BOOL LoadScoreData(const char* path, SCORE_DATA* score, BOOL IsHeader = FALSE)
{
	FILE* fp;				//�t�@�C���|�C���^
	char GetChar = '\0';	//�擾���镶��
	errno_t FileErr = NULL;	//�t�@�C���ǂݍ��݃G���[���m�F
	int IsEOF = NULL;		//�t�@�C���̏I��肩�`�F�b�N

	//�p�X�̃R�s�[
	SetScoreDataPath(path);

	FileErr = fopen_s(&fp, path, "r");	//�t�@�C����ǂݍ��݃��[�h(r)�ŊJ��
	if (FileErr != NULL)
	{
		//�X�R�A�f�[�^�쐬
		if (CreateScoreData() == FALSE) { return FALSE; }

		//�R�R�܂ł̏����ŁA�X�R�A�f�[�^�͍��ꂽ�n�Y�I

		FileErr = fopen_s(&fp, path, "r");	//�t�@�C����ǂݍ��݃��[�h(r)�ŊJ��
		if (FileErr != NULL)
		{
			MessageBox(GetMainWindowHandle(), path, SCORE_LOAD_ERR_TITLE, MB_OK);	//�Ǎ��G���[
			return FALSE;
		}
	}

	//�������琳��ɓǂݍ��߂��Ƃ��̏���****************************************

	//CSV��1�s�ڂ��w�b�_�̂Ƃ�
	if (IsHeader == TRUE)
	{
		//�P���������o���A���s���q���g�ɂP�s�ڂ�ǂݔ�΂�
		while (GetChar != '\n') { GetChar = fgetc(fp); }
	}

	//���ۂɃf�[�^���i�[����
	while (IsEOF != EOF)	//End Of File�i�t�@�C���̍Ō�j�ł͂Ȃ��Ƃ��J��Ԃ�
	{
		//CSV�̃f�[�^�̂P�s����ǂݎ��
		IsEOF = fscanf_s(
			fp,
			SCORE_DATA_FORMAT,	//�f�[�^���u��s=���R�[�h�v�ŏ�����Ă���̂��|�C���g�I
			&(score)->Name1, STR_MAX,	//�������ǂݍ��ނƂ��́A���̈����ŕ�����ő吔���w�肷��
			&(score)->Score1,
			&(score)->Name2, STR_MAX,	//�������ǂݍ��ނƂ��́A���̈����ŕ�����ő吔���w�肷��
			&(score)->Score2,
			&(score)->Name3, STR_MAX,	//�������ǂݍ��ނƂ��́A���̈����ŕ�����ő吔���w�肷��
			&(score)->Score3
		);
	}

	fclose(fp);	//�t�@�C�������

	return TRUE;
}

/// <summary>
/// �X�R�A�f�[�^�쐬
/// </summary>
/// <returns></returns>
BOOL CreateScoreData(VOID)
{
	//�Ȃ�������X�R�A�f�[�^�����
	FILE* creFp;
	errno_t creFileErr = NULL;	//�t�@�C���ǂݍ��݃G���[���m�F
	creFileErr = fopen_s(&creFp, GetScoreDataPath(), "w");	//�t�@�C�����������݃��[�h(w)�ŊJ��(�쐬����)
	if (creFileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_CREATE_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�w�b�_����������
	fprintf_s(creFp,
		"Name1,Score1,Name2,Score2,Name3,Score3\n"
	);

	//��̃X�R�A�f�[�^����������
	fprintf_s(creFp,
		"%s,%d,%s,%d,%s,%d",
		score_dataInit.Name1, score_dataInit.Score1,
		score_dataInit.Name2, score_dataInit.Score2,
		score_dataInit.Name3, score_dataInit.Score3
	);

	fclose(creFp);	//�X�R�A�f�[�^�����

	MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_CREATE_TITLE, MB_OK);
	return TRUE;
}

/// <summary>
/// �X�R�A�f�[�^�ۑ�
/// </summary>
/// <returns></returns>
BOOL SaveScoreData(VOID)
{
	//�Ȃ�������X�R�A�f�[�^�����
	FILE* creFp;
	errno_t creFileErr = NULL;	//�t�@�C���ǂݍ��݃G���[���m�F
	creFileErr = fopen_s(&creFp, GetScoreDataPath(), "w");	//�t�@�C�����������݃��[�h(w)�ŊJ��(�쐬����)
	if (creFileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_CREATE_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�w�b�_����������
	fprintf_s(creFp,
		"Name1,Score1,Name2,Score2,Name3,Score3\n"
	);

	//�X�R�A�f�[�^����������
	fprintf_s(creFp,
		"%s,%d,%s,%d,%s,%d",
		score_data.Name1, score_data.Score1,
		score_data.Name2, score_data.Score2,
		score_data.Name3, score_data.Score3
	);

	fclose(creFp);	//�X�R�A�f�[�^�����

	MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_SAVE_TITLE, MB_OK);
	return TRUE;
}

/// <summary>
/// �X�R�A�f�[�^�̍폜
/// </summary>
/// <param name="path">�X�R�A�f�[�^�̃p�X</param>
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

	//�X�R�A�f�[�^���쐬
	return CreateScoreData();
}

/// <summary>
/// �X�R�A�f�[�^�̃p�X��Ԃ�
/// </summary>
/// <returns></returns>
const char* GetScoreDataPath(VOID)
{
	return score_data.path;
}

/// <summary>
/// �X�R�A�f�[�^�̃p�X��ݒ肷��
/// </summary>
/// <returns></returns>
VOID SetScoreDataPath(const char* path)
{
	strcpyDx(score_data.path, path);
	return;
}