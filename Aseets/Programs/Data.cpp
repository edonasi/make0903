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

/// <summary>
/// �}�b�vcsv�t�@�C����ǂݍ���
/// </summary>
/// <param name="imgPath">�}�b�v�`�b�v�摜�t�@�C���̃p�X</param>
/// <param name="downPath">�����C���[�t�@�C���̃p�X</param>
/// <param name="centerPath">�����C���[�̃t�@�C���̃p�X</param>
/// <param name="centerColliderPath">�������蔻�背�C���[�̃t�@�C���p�X</param>
/// <param name="upPath">�ヌ�C���[�̃t�@�C���p�X</param>
/// <param name="map">�}�b�v�f�[�^�\���̂̐擪�A�h���X</param>
/// <param name="divX">���̕�����</param>
/// <param name="divY">�c�̕�����</param>
/// <returns></returns>
BOOL LoadCsvMap(const char* imgPath,
	const char* downPath, const char* centerPath, const char* centerColliderPath, const char* upPath,
	MAP_DATA_SAMPLE* map, int divYoko, int divTate) {
	//�}�b�v�`�b�v�̓ǂݍ���
	int isLoad = -1;

	//�ꎞ�I�ɉ摜�̃n���h����p�ӂ���
	int tempHandle = LoadGraph(imgPath);

	//�ǂݍ��݃G���[
	if (tempHandle == -1) {
		MessageBox(
			GetMainWindowHandle(),
			imgPath,
			"�摜�ǂݍ��݃G���[",
			MB_OK
		);
		return FALSE;
	}

	//�摜�̕��ƍ������擾
	int width = -1;
	int height = -1;
	GetGraphSize(tempHandle, &width, &height);

	//�������ēǂݍ���
	isLoad = LoadDivGraph(
		imgPath,
		divYoko * divTate,
		divYoko, divTate,
		width / divYoko, height / divTate,
		map->handle
	);

	//�����G���[
	if (isLoad == -1) {
		MessageBox(
			GetMainWindowHandle(),
			imgPath,
			"�摜�����G���[",
			MB_OK
		);

		return FALSE;
	}

	//����ݒ�
	map->divMax = divYoko * divTate;
	GetGraphSize(map->handle[0], &map->width, &map->height);

	//�摜��`�悷��
	map->isDraw = TRUE;

	//�ꎞ�I�ɓǂݍ��񂾃n���h�������
	DeleteGraph(tempHandle);

	//==========================================

	FILE* fp;					//�t�@�C���|�C���^
	char getChar = '\0';		//�擾���镶��
	int loopCnt = 0;			//���[�v�J�E���^
	errno_t fileErr = NULL;		//�t�@�C���ǂݍ��݃G���[���m�F
	int isEOF = NULL;			//�t�@�C���̏I��肩�`�F�b�N

	//��CSV�ǂݍ���==========================================

	fileErr = fopen_s(&fp, downPath, "r");	//�t�@�C����ǂݍ��݃��[�h(r)�ŊJ��
	if (fileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), downPath, CSV_LOAD_ERR_TITLE, MB_OK);	//�ǂݍ��݃G���[
		return FALSE;
	}

	//	���������琳��ɓǂݍ��߂����̏���

	loopCnt = 0;			//���[�v�J�E���^
	isEOF = NULL;		//�t�@�C���ǂݍ��݃G���[���m�F

	//���ۂɃf�[�^���i�[����
	while (isEOF != EOF)	//�t�@�C���̍Ō�ł͂Ȃ��Ƃ��J��Ԃ�
	{
		//csv�̃f�[�^��1�s����ǂݎ��
		//fp = �J�[�\���̃C���[�W
		isEOF = fscanf_s(
			fp,
			CSV_MAP_FORMAT,
			&map->csvDown[loopCnt / MAP1_YOKO_MAX][loopCnt % MAP1_YOKO_MAX]
		);

		//���̃f�[�^��
		loopCnt++;
	}

	fclose(fp);	//�t�@�C�������

	//��CSV�ǂݍ���==========================================

	fileErr = fopen_s(&fp, centerPath, "r");	//�t�@�C����ǂݍ��݃��[�h(r)�ŊJ��
	if (fileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), centerPath, CSV_LOAD_ERR_TITLE, MB_OK);	//�ǂݍ��݃G���[
		return FALSE;
	}

	//	���������琳��ɓǂݍ��߂����̏���

	loopCnt = 0;			//���[�v�J�E���^
	isEOF = NULL;		//�t�@�C���ǂݍ��݃G���[���m�F

	//���ۂɃf�[�^���i�[����
	while (isEOF != EOF)	//�t�@�C���̍Ō�ł͂Ȃ��Ƃ��J��Ԃ�
	{
		//csv�̃f�[�^��1�s����ǂݎ��
		//fp = �J�[�\���̃C���[�W
		isEOF = fscanf_s(
			fp,
			CSV_MAP_FORMAT,
			&map->csvCenter[loopCnt / MAP1_YOKO_MAX][loopCnt % MAP1_YOKO_MAX]
		);

		//���̃f�[�^��
		loopCnt++;
	}

	fclose(fp);	//�t�@�C�������

	//�������蔻��CSV�ǂݍ���==========================================

	fileErr = fopen_s(&fp, centerColliderPath, "r");	//�t�@�C����ǂݍ��݃��[�h(r)�ŊJ��
	if (fileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), centerColliderPath, CSV_LOAD_ERR_TITLE, MB_OK);	//�ǂݍ��݃G���[
		return FALSE;
	}

	//	���������琳��ɓǂݍ��߂����̏���

	loopCnt = 0;			//���[�v�J�E���^
	isEOF = NULL;		//�t�@�C���ǂݍ��݃G���[���m�F

	//���ۂɃf�[�^���i�[����
	while (isEOF != EOF)	//�t�@�C���̍Ō�ł͂Ȃ��Ƃ��J��Ԃ�
	{
		//csv�̃f�[�^��1�s����ǂݎ��
		//fp = �J�[�\���̃C���[�W
		isEOF = fscanf_s(
			fp,
			CSV_MAP_FORMAT,
			&map->csvCenterCollider[loopCnt / MAP1_YOKO_MAX][loopCnt % MAP1_YOKO_MAX]
		);

		//���̃f�[�^��
		loopCnt++;
	}

	fclose(fp);	//�t�@�C�������

	//��CSV�ǂݍ���==========================================

	fileErr = fopen_s(&fp, upPath, "r");	//�t�@�C����ǂݍ��݃��[�h(r)�ŊJ��
	if (fileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), upPath, CSV_LOAD_ERR_TITLE, MB_OK);	//�ǂݍ��݃G���[
		return FALSE;
	}

	//	���������琳��ɓǂݍ��߂����̏���

	loopCnt = 0;			//���[�v�J�E���^
	isEOF = NULL;		//�t�@�C���ǂݍ��݃G���[���m�F

	//���ۂɃf�[�^���i�[����
	while (isEOF != EOF)	//�t�@�C���̍Ō�ł͂Ȃ��Ƃ��J��Ԃ�
	{
		//csv�̃f�[�^��1�s����ǂݎ��
		//fp = �J�[�\���̃C���[�W
		isEOF = fscanf_s(
			fp,
			CSV_MAP_FORMAT,
			&map->csvUp[loopCnt / MAP1_YOKO_MAX][loopCnt % MAP1_YOKO_MAX]
		);

		//���̃f�[�^��
		loopCnt++;
	}

	fclose(fp);	//�t�@�C�������

	//�}�b�v�̓����蔻����쐬
	for (int y = 0; y < MAP1_TATE_MAX; y++) {
		for (int x = 0; x < MAP1_YOKO_MAX; x++) {
			if (map->csvCenterCollider[y][x] == MAP_STOP_ID) {
			//�����蔻����쐬
				map->coll[y][x].left = (x + 0) * map->width + 1;
				map->coll[y][x].right = (x + 1) * map->width - 1;
				map->coll[y][x].top = (y + 0) * map->height + 1;
				map->coll[y][x].bottom = (y + 1) * map->height - 1;
			}
			else {
				map->coll[y][x].left = 	  0;
				map->coll[y][x].right =	  0;
				map->coll[y][x].top = 	  0;
				map->coll[y][x].bottom=   0;
			}

			//�}�b�v�̏ꏊ��ݒ�
			map->x[y][x] = (x + 0) * map->width;
			map->y[y][x] = (y + 0) * map->height;
		}
	}

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

BOOL CollMap(RECT rect, MAP_DATA_SAMPLE map) {
	for (int y = 0; y < MAP1_TATE_MAX; y++) {
		for (int x = 0; x < MAP1_YOKO_MAX; x++) {
			if (CheckCollRectToRect(rect, map.coll[y][x]) == TRUE) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

VOID DrawMap(MAP_DATA_SAMPLE map) {
	//�}�b�v���`��ł���Ƃ���
	if (map.isDraw == TRUE) {
		//�����C���[�`��
		for (int y = 0; y < MAP1_TATE_MAX; y++) {
			for (int x = 0; x < MAP1_YOKO_MAX; x++) {
				//�`��
				DrawGraph(
					map.x[y][x],
					map.y[y][x],
					map.handle[map.csvDown[y][x]], TRUE
					//&map->csvDown[loopCnt / MAP1_YOKO_MAX][loopCnt % MAP1_YOKO_MAX]
				);
				
			}
		}

		//�����C���[�̕`��`��
		for (int y = 0; y < MAP1_TATE_MAX; y++) {
			for (int x = 0; x < MAP1_YOKO_MAX; x++) {
				//�`��
				DrawGraph(
					map.x[y][x],
					map.y[y][x],
					map.handle[map.csvCenter[y][x]], TRUE
				);
			}
		}

		//�v���C���[�̉摜��`�悷��
		DrawDivImageChara(&samplePlayerImg);

		//�ヌ�C���[�̕`��
		for (int y = 0; y < MAP1_TATE_MAX; y++) {
			for (int x = 0; x < MAP1_YOKO_MAX; x++) {
				//�`��
				DrawGraph(
					map.x[y][x],
					map.y[y][x],
					map.handle[map.csvUp[y][x]], TRUE
				);
			}
		}

		//�f�o�b�N���[�h�ł͂Ȃ��Ƃ������ŏ����I��
		if (GAME_DEBUG == FALSE) { return; }

		//�����蔻���`��
		for (int y = 0; y < MAP1_TATE_MAX; y++) {
			for (int x = 0; x < MAP1_YOKO_MAX; x++) {
				//�`��
				DrawRect(map.coll[y][x], GetColor(255, 255, 255), FALSE);
			}
		}
	}
	return;
}