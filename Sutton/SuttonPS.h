#pragma once
/* SuttonPS.h : �w�b�_�t�@�C�� */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int start(void);  /* �X�^�[�g��Ԃ̔ԍ���Ԃ� */
int goal(void);  /* �S�[����Ԃ̔ԍ���Ԃ� */
int n_stt(void);  /* �����̑S��Ԑ���Ԃ� */

int up_env(int stt);  /* ���̏�Ԃ̊��i0:�ʘH�C1:��Q��or���O�j��Ԃ� */
int up_stt(int stt);  /* ���̏�Ԃ̔ԍ���Ԃ��D-1�͊��O */
int right_env(int stt);  /* ��E�̏�Ԃ̊��i0:�ʘH�C1:��Q��or���O�j��Ԃ� */
int right_stt(int stt);  /* ��E�̏�Ԃ̔ԍ���Ԃ��D-1�͊��O */
int down_env(int stt);  /* ����̏�Ԃ̊��i0:�ʘH�C1:��Q��or���O�j��Ԃ� */
int down_stt(int stt);  /* ����̏�Ԃ̔ԍ���Ԃ��D-1�͊��O */
int left_env(int stt);  /* ����̏�Ԃ̊��i0:�ʘH�C1:��Q��or���O�j��Ԃ� */
int left_stt(int stt);  /* ����̏�Ԃ̔ԍ���Ԃ��D-1�͊��O */
