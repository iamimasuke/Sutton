#pragma once
/* SuttonPS.h : ヘッダファイル */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int start(void);  /* スタート状態の番号を返す */
int goal(void);  /* ゴール状態の番号を返す */
int n_stt(void);  /* 環境中の全状態数を返す */

int up_env(int stt);  /* 一つ上の状態の環境（0:通路，1:障害物or環境外）を返す */
int up_stt(int stt);  /* 一つ上の状態の番号を返す．-1は環境外 */
int right_env(int stt);  /* 一つ右の状態の環境（0:通路，1:障害物or環境外）を返す */
int right_stt(int stt);  /* 一つ右の状態の番号を返す．-1は環境外 */
int down_env(int stt);  /* 一つ下の状態の環境（0:通路，1:障害物or環境外）を返す */
int down_stt(int stt);  /* 一つ下の状態の番号を返す．-1は環境外 */
int left_env(int stt);  /* 一つ左の状態の環境（0:通路，1:障害物or環境外）を返す */
int left_stt(int stt);  /* 一つ左の状態の番号を返す．-1は環境外 */
