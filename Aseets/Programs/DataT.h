//��Data�n�̃w�b�_�t�@�C��
#pragma once

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########

//�Q�[���̃��C���w�b�_�t�@�C��
#include	"game.h"

//########## �}�N����` ##########

//�G���[���b�Z�[�W
#define CSV_LOAD_ERR_TITLE		TEXT("CSV�ǂݍ��݃G���[")
#define CSV_DATANUM_ERR_TITLE	TEXT("CSV�f�[�^���G���[")

//�L�����f�[�^�̃p�X
#define CSV_PATH_ENEMY		TEXT(".\\Aseets\\Data\\enemy.csv")	//ANSI�̕����R�[�h�Ńt�@�C���ۑ�

//�f�[�^�̏����w��q
//�L�����N�^�̏����w��q�i%[^,]�͕�����j
#define CSV_CHARA_FORMAT	TEXT("%d,%[^,],%d,%d,%d,%d,%d,%d,%d,%d")

//�G�f�[�^
#define ENEMY_MAX	8

//�G���[���b�Z�[�W
#define SCORE_CREATE_ERR_TITLE	TEXT("�X�R�A�f�[�^�쐬�G���[")
#define SCORE_LOAD_ERR_TITLE	TEXT("�X�R�A�f�[�^�Ǎ��G���[")
#define SCORE_CREATE_TITLE		TEXT("�X�R�A�f�[�^�쐬OK!!")
#define SCORE_SAVE_TITLE		TEXT("�X�R�A�f�[�^�ۑ�OK!!")
#define SCORE_DELETE_TITLE		TEXT("�X�R�A�f�[�^�폜OK!!")
#define SCORE_DELETE_ERR_TITLE	TEXT("�X�R�A�f�[�^�폜�G���[")

//�X�R�A�f�[�^�̃p�X�i�����Ċg���q���w���Ȃ̂ɂ��邱�ƂŁA�X�R�A�f�[�^�Ǝv���ɂ����I�H�j
#define SCORE_DATA_PATH		TEXT(".\\Aseets\\Data\\score.a")	//ANSI�̕����R�[�h�Ńt�@�C���ۑ�

//�f�[�^�̏����w��q
#define SCORE_DATA_FORMAT	TEXT("%[^,],%d,%[^,],%d,%[^,],%d")	//�X�R�A�f�[�^�̏����w��q�i%[^,]�͕�����j

//�L�����f�[�^�\����(�����܂ŃT���v��)
struct CHARA_DATA
{
	int No;					//No
	char Name[STR_MAX];		//���O

	//���ۂɎg���l
	int HP;					//HP
	int ATK;				//�U����
	int DEF;				//�h���
	int RAK;

	//�ő�l
	int MAX_HP;				//HP
	int MAX_ATK;			//�U����
	int MAX_DEF;			//�h���
	int MAX_RAK;
};

//�X�R�A�f�[�^�\����(�����܂ŃT���v��)
struct SCORE_DATA
{
	char path[PATH_MAX];	//�p�X
	char Name1[STR_MAX];	//���O�P
	int Score1;				//�X�R�A�P
	char Name2[STR_MAX];	//���O�Q
	int Score2;				//�X�R�A�Q
	char Name3[STR_MAX];	//���O�R
	int Score3;				//�X�R�A�R
};

//########## �O���̃O���[�o���ϐ� ##########
extern CHARA_DATA enemy[ENEMY_MAX];		//�G�f�[�^
extern SCORE_DATA score_data;			//�X�R�A�f�[�^
extern SCORE_DATA score_dataInit;		//�X�R�A�f�[�^(�������p)

//########## �v���g�^�C�v�錾 ##########
//��extern �́A�O���Ɋ֐�������܂���I�Ƃ����ڈ�ł��Ă��܂��B

extern BOOL LoadCSVChara(const char* path, CHARA_DATA* chara, int DataMax, BOOL IsHeader);
extern BOOL LoadScoreData(const char* path, SCORE_DATA* score, BOOL IsHeader);

extern BOOL CreateScoreData(VOID);
extern BOOL SaveScoreData(VOID);
extern BOOL DeleteScoreData(VOID);
extern const char* GetScoreDataPath(VOID);
extern VOID SetScoreDataPath(const char* path);