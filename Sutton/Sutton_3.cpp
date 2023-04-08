#include <stdio.h>
#include <random>
#include <math.h>
#include "SuttonPS.h"

#define N_ACT 4//�s����
#define EPTIMES 100//�G�s�\�[�h��
#define REWARD 10.0//��V��
#define WARIBIKI 0.2//������
#define JIKKEN 200//������
#define SHOKICHI 1.0 * pow(10,-16) //���l�̏����l
double value[100][N_ACT];//���l���i�[����񎟌��z��[��Ԑ�][�s����]

/*�����̐ݒ�*/
std::mt19937 mt;
std::random_device rnd;
std::uniform_real_distribution<double> rand1(0.0, 1.0);

/*���[���b�g�I��*/
int select_roullet(int stt, double tmp) {
	double div[100][N_ACT];//���l�̍��v
	div[stt][0] = value[stt][0];
	for (int k = 1; k < n_stt(); k++) {
		div[stt][k] = div[stt][k - 1] + value[stt][k];
	}
	/*���l�̍��v��1�ɂ���*/
	for (int k = 0; k < N_ACT; k++) {
		div[stt][k] = div[stt][k] / div[stt][N_ACT - 1];
	}
	/*�����̒l�ɂ���ĕԂ�l��Ԃ�*/
	if (tmp <= div[stt][0]) {
		return 0;
	}
	for (int k = 1; k < N_ACT; k++) {
		if (div[stt][k - 1] < tmp && tmp <= div[stt][k]) {
			return   k;
		}
	}
}

int main(void)
{
	int act;//�������瓾���s�����i�[
	int total;//�X�e�b�v��
	int fptotal;//fp�Ŏg�p����X�e�b�v��(total�͉��l�̕��z�Ŏg�p���A����������Ă��܂�����)
	double ntotal;//�P�ʍs��������̊l����V�ʂ��i�[
	double tm;//�����̎��[
	int history_stt[10000];//��Ԃ̗���
	int history_act[10000];//�s���̗���
	double sptotal[EPTIMES][JIKKEN];//[�G�s�\�[�h��][������]

	/*�t�@�C���ւ̏�������*/
	FILE* fp;
	fopen_s(&fp, "Sutton_3.csv", "w");
	fprintf(fp, "�G�s�\�[�h��,�P�ʍs��������̊l����V��\n");
	/*�t�@�C�����Ȃ��ꍇ�A�]1��Ԃ�*/
	if (fp == NULL) {
		printf("error!");
		return -1;
	}
	/*�w�肳�ꂽ���̎������J��Ԃ�*/
	for (int n = 0; n < JIKKEN; n++) {
		mt.seed(n + 1);//�����񐔂���Ƃ��錈��I�ȗ���
		/*�w�肳�ꂽ���̃G�s�\�[�h���J��Ԃ�*/
		for (int i = 0; i < EPTIMES; i++) {
			int stt = start();
			/*�G�s�\�[�h1�ɂ����ĉ��l�̏����l����*/
			if (i == 0) {
				for (int j = 0; j < n_stt(); j++) {
					for (int k = 0; k < N_ACT; k++) {
						value[j][k] = { SHOKICHI };
					}
				}
			}
			total = 0;//�X�e�b�v���̏�����
			/*1�G�s�\�[�h���J�n*/
			while (stt != goal()) {
				tm = rand1(mt);
				int stt1 = stt;
				act = select_roullet(stt, tm);//�s���̌���(0�`3)
				/*���肳�ꂽ�s�������Ƃɍs������*/
				/*0����A1���E�A2�����A3����*/
				switch (act) {
				case 0:
					if (up_env(stt) == 0) {
						stt = up_stt(stt);
					}
					else {
						break;
					}
					break;
				case 1:
					if (right_env(stt) == 0) {
						stt = right_stt(stt);
					}
					else {
						break;
					}
					break;
				case 2:
					if (down_env(stt) == 0) {
						stt = down_stt(stt);
					}
					else {
						break;
					}
					break;
				default:
					if (left_env(stt) == 0) {
						stt = left_stt(stt);
					}
				}
				/*��Ԃƍs���̗���*/
				history_stt[total] = stt1;
				history_act[total] = act;
				total++;
			}
			fptotal = total;//total�̒l���ς��O��fptotal�ɃX�e�b�v�����i�[
			/*�X�e�b�v�����牿�l�̔z��*/
			int l = 1;
			total = total - 1;
			while (total >= 0) {
				value[history_stt[total]][history_act[total]] += pow(WARIBIKI, l) * REWARD;
				total--;
				l++;
			}
			sptotal[i][n] = REWARD / fptotal;
		}
	}
	/*�G�s�\�[�h���ƒP�ʍs��������̊l����V�ʂ��t�@�C���ɏ�������*/
	for (int i = 0; i < EPTIMES; i++) {
		ntotal = 0;
		for (int n = 0; n < JIKKEN; n++) {
			ntotal += sptotal[i][n] / JIKKEN;
		}
		fprintf(fp, "%d,%lf\n", i + 1, ntotal);
	}
	fclose(fp);
	return 0;
}