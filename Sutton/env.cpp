/* env.cpp : 環境ファイル */

#include "SuttonPS.h"

//#define TEST
/* 4状態のテスト環境を使う．Suttonの迷路にするには，コメントアウトする．*/

#ifdef TEST
/* 4状態のテスト環境 */
#define LENGTH 1
#define WIDTH 4
#define N_STT 4  /* LENGTH * WIDTH */

/* 環境を表す配列．0:通路，1:障害物 */
static int env[N_STT] = {
	0, 0, 0, 0
};

#define START 0
#define GOAL 3

#else
/* Suttonの迷路環境 */
#define LENGTH 6
#define WIDTH 9
#define N_STT 54  /* LENGTH * WIDTH */

/* 環境を表す配列．0:通路，1:障害物 */
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

int start(void) { return (int)START; }  /* スタート状態の番号を返す */
int goal(void) { return (int)GOAL; }  /* ゴール状態の番号を返す */
int n_stt(void) { return (int)N_STT; }  /* 環境中の全状態数を返す */

int up_env(int stt) {  /* 一つ上の状態の環境（0:通路，1:障害物or環境外）を返す */
	return (stt < WIDTH) ? 1 : env[stt - WIDTH];
}
int up_stt(int stt) {  /* 一つ上の状態の番号を返す．-1は環境外 */
	return (stt < WIDTH) ? -1 : stt - WIDTH;
}
int right_env(int stt) {  /* 一つ右の状態の環境（0:通路，1:障害物or環境外）を返す */
	return (stt % WIDTH == WIDTH - 1) ? 1 : env[stt + 1];
}
int right_stt(int stt) {  /* 一つ右の状態の番号を返す．-1は環境外 */
	return (stt % WIDTH == WIDTH - 1) ? -1 : stt + 1;
}
int down_env(int stt) {  /* 一つ下の状態の環境（0:通路，1:障害物or環境外）を返す */
	int down = stt + WIDTH;
	return (down >= N_STT) ? 1 : env[down];
}
int down_stt(int stt) {  /* 一つ下の状態の番号を返す．-1は環境外 */
	int down = stt + WIDTH;
	return (down >= N_STT) ? -1 : down;
}
int left_env(int stt) {  /* 一つ左の状態の環境（0:通路，1:障害物or環境外）を返す */
	return (!(stt % WIDTH)) ? 1 : env[stt - 1];
}
int left_stt(int stt) {  /* 一つ左の状態の番号を返す．-1は環境外 */
	return (!(stt % WIDTH)) ? -1 : stt - 1;
}
