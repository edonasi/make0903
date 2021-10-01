#pragma once

//�Q�[���̃��C���w�b�_�t�@�C��
#include "game.h"

//	�}�N����`
//�G���[���b�Z�[�W
#define CSV_LOAD_ERR_TITLE TEXT("CSV�ǂݍ��݃G���[")

//�L�����N�^�[�f�[�^�̃p�X
#define CSV_PATH_ENEMY TEXT("./Aseets/Data/enemy.csv")

//�f�[�^�̏����w��q
//�L�����N�^�̏����w��q(%[^,]�͕�����(,������܂�))
#define CSV_CHARA_FORMAT TEXT("%d,%[^,],%d,%d,%d,%d,%d,%d,%d,%d")

//�ǂݍ��ݐ��G���[���b�Z�[�W
#define CSV_DATA_ERR_TITLE TEXT("CSV���G���[")

//�G�f�[�^
#define ENEMY_MAX 8

//�G���[���b�Z�[�W
#define SCORE_CREATE_ERR_TITLE TEXT("�X�R�A�f�[�^�쐬�G���[")
#define SCORE_LOAD_ERR_TITLE TEXT("�X�R�A�f�[�^�ǂݍ��݃G���[")
#define SCORE_CREATE_TITLE TEXT("�X�R�A�f�[�^�쐬OK")
#define SCORE_SAVE_TITLE TEXT("�X�R�A�f�[�^�ۑ�OK")
#define SCORE_DELETE_TITLE TEXT("�X�R�A�f�[�^�폜OK")
#define SCORE_DELETE_ERR_TITLE TEXT("�X�R�A�f�[�^�폜�G���[")

//�X�R�A�f�[�^�̃p�X(�g���q��ςȂ��̂ɂ��邱�ƂŃ`�[�g�΍�H)
#define SCORE_DATA_PATH TEXT("./Aseets/Data/questionTest")

//�f�[�^�̏����w��q
#define SCORE_DATA_FORMAT TEXT("%[^,],%d,%[^,],%d,%[^,],%d")

//�}�b�v�`�b�v�摜�t�@�C���p�X
#define IMG_PATH_MAP1		TEXT("./Aseets/Maps/testMap.png")

//�}�b�v�f�[�^�̃t�@�C���p�X
#define CSV_PATH_MAP1_DOWN TEXT("./Aseets/Maps/testMap_test_map_down.csv")
#define CSV_PATH_MAP1_CENTER TEXT("./Aseets/Maps/testMap_test_map_center.csv")
#define CSV_PATH_MAP1_CENTER_COLLIDER TEXT("./Aseets/Maps/testMap_test_map_center_collder.csv")
#define CSV_PATH_MAP1_UP TEXT("./Aseets/Maps/testMap_test_map_up.csv")

//�}�b�v�̏����w��q
#define CSV_MAP_FORMAT	TEXT("%d,")

#define MAP1_YOKO_MAX		20//�}�b�v���T�C�Y
#define MAP1_TATE_MAX		15//�}�b�v�c�T�C�Y
#define MAP1_YOKO_DIV		60//�}�b�v�c�T�C�Y
#define MAP1_TATE_DIV		60//�}�b�v�c�T�C�Y

#define MAP_MOVE_ID		56	//�ʂ��}�b�vID
#define MAP_STOP_ID		57	//�ʂ�Ȃ��}�b�vID
#define MAP_NONE_ID		58	//�����Ȃ��}�b�vID

//�L�����f�[�^�\����(�T���v��)
struct CHARA_DATA_SAMPLE
{
	int no;					//�ԍ�
	char name[STR_MAX];		//���O

	//���ۂɎg���l
	int hp;					//HP
	int atk;				//�U����
	int def;				//�h���
	int rak;				//�K�^

	//�ő�l
	int hpMax;				//�ő�HP
	int atkMax;				//�ő�U����
	int defMax;				//�ő�h���
	int rakMax;				//�ő�K�^
};

//�X�R�A�f�[�^�\����(�T���v��)
struct SCORE_DATA_SAMPLE
{
	char path[PATH_MAX];	//�X�R�A�f�[�^������p�X

	char name1[STR_MAX];	//���O1
	int score1;				//�X�R�A1

	char name2[STR_MAX];	//���O2
	int score2;				//�X�R�A2

	char name3[STR_MAX];	//���O3
	int score3;				//�X�R�A3
};

//�}�b�v�f�[�^�\����(�T���v��)
struct MAP_DATA_SAMPLE
{
	//csv�f�[�^
	int csvDown[MAP1_TATE_MAX][MAP1_YOKO_MAX];
	int csvCenter[MAP1_TATE_MAX][MAP1_YOKO_MAX];
	int csvCenterCollider[MAP1_TATE_MAX][MAP1_YOKO_MAX];
	int csvUp[MAP1_TATE_MAX][MAP1_YOKO_MAX];

	//�}�b�v�̃n���h��
	int handle[MAP1_TATE_DIV * MAP1_YOKO_DIV];

	//�}�b�v�̏ꏊ
	int x[MAP1_TATE_MAX][MAP1_YOKO_MAX];
	int y[MAP1_TATE_MAX][MAP1_YOKO_MAX];

	int width;
	int height;

	int divMax;

	BOOL isDraw = FALSE;

	//�����蔻��
	RECT coll[MAP1_TATE_MAX][MAP1_YOKO_MAX];
};

//�ϐ�
extern CHARA_DATA_SAMPLE enemy[ENEMY_MAX];	//�G�f�[�^
extern SCORE_DATA_SAMPLE scoreData;			//�X�R�A�f�[�^
extern SCORE_DATA_SAMPLE scoreDataInit;		//�X�R�A�f�[�^(�������p)


//�֐�
extern BOOL LoadScvChara(const char* path, CHARA_DATA_SAMPLE* chara, int dataMax, BOOL isHeader);
extern BOOL LoadScoreData(const char* path, SCORE_DATA_SAMPLE* score, BOOL isHeader);
extern BOOL LoadCsvMap(	/*�}�b�v*/
	const char* imgPath,
	const char* downPath,
	const char* centerPath,
	const char* centerColliderPath,
	const char* upPath,
	MAP_DATA_SAMPLE* map,
	int divYoko,
	int divTate
);
extern BOOL CreateScoreData(VOID);
extern BOOL SaveScoreData(VOID);
extern BOOL DeleteScoreData(VOID);
extern const char* GetScoreDataPath(VOID);
extern VOID SetScoreDataPath(const char* path);
//�}�b�v
extern BOOL CollMap(RECT rect, MAP_DATA_SAMPLE map);
extern VOID DrawMap(MAP_DATA_SAMPLE map);
