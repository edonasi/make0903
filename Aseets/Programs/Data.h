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

extern CHARA_DATA_SAMPLE enemy[ENEMY_MAX];

extern BOOL LoadScvChara(const char* path, CHARA_DATA_SAMPLE* chara, int dataMax, BOOL isHeader);