/* env.cpp : ���t�@�C�� */

#include "SuttonPS.h"

//#define TEST
/* 4��Ԃ̃e�X�g�����g���DSutton�̖��H�ɂ���ɂ́C�R�����g�A�E�g����D*/

#ifdef TEST
/* 4��Ԃ̃e�X�g�� */
#define LENGTH 1
#define WIDTH 4
#define N_STT 4  /* LENGTH * WIDTH */

/* ����\���z��D0:�ʘH�C1:��Q�� */
static int env[N_STT] = {
	0, 0, 0, 0
};

#define START 0
#define GOAL 3

#else
/* Sutton�̖��H�� */
#define LENGTH 6
#define WIDTH 9
#define N_STT 54  /* LENGTH * WIDTH */

/* ����\���z��D0:�ʘH�C1:��Q�� */
static int env[N_STT] = {
	0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 1, 0, 0, 0, 0, 1, 0,
	0, 0, 1, 0, 0, 0, 0, 1, 0,
	0, 0, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0
};

#define START 18
#define GOAL 8

#endif

int start(void) { return (int)START; }  /* �X�^�[�g��Ԃ̔ԍ���Ԃ� */
int goal(void) { return (int)GOAL; }  /* �S�[����Ԃ̔ԍ���Ԃ� */
int n_stt(void) { return (int)N_STT; }  /* �����̑S��Ԑ���Ԃ� */

int up_env(int stt) {  /* ���̏�Ԃ̊��i0:�ʘH�C1:��Q��or���O�j��Ԃ� */
	return (stt < WIDTH) ? 1 : env[stt - WIDTH];
}
int up_stt(int stt) {  /* ���̏�Ԃ̔ԍ���Ԃ��D-1�͊��O */
	return (stt < WIDTH) ? -1 : stt - WIDTH;
}
int right_env(int stt) {  /* ��E�̏�Ԃ̊��i0:�ʘH�C1:��Q��or���O�j��Ԃ� */
	return (stt % WIDTH == WIDTH - 1) ? 1 : env[stt + 1];
}
int right_stt(int stt) {  /* ��E�̏�Ԃ̔ԍ���Ԃ��D-1�͊��O */
	return (stt % WIDTH == WIDTH - 1) ? -1 : stt + 1;
}
int down_env(int stt) {  /* ����̏�Ԃ̊��i0:�ʘH�C1:��Q��or���O�j��Ԃ� */
	int down = stt + WIDTH;
	return (down >= N_STT) ? 1 : env[down];
}
int down_stt(int stt) {  /* ����̏�Ԃ̔ԍ���Ԃ��D-1�͊��O */
	int down = stt + WIDTH;
	return (down >= N_STT) ? -1 : down;
}
int left_env(int stt) {  /* ����̏�Ԃ̊��i0:�ʘH�C1:��Q��or���O�j��Ԃ� */
	return (!(stt % WIDTH)) ? 1 : env[stt - 1];
}
int left_stt(int stt) {  /* ����̏�Ԃ̔ԍ���Ԃ��D-1�͊��O */
	return (!(stt % WIDTH)) ? -1 : stt - 1;
}
