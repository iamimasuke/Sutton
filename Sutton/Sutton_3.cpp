#include <stdio.h>
#include <random>
#include <math.h>
#include "SuttonPS.h"

#define N_ACT 4//行動数
#define EPTIMES 100//エピソード数
#define REWARD 10.0//報酬量
#define WARIBIKI 0.2//割引率
#define JIKKEN 200//実験回数
#define SHOKICHI 1.0 * pow(10,-16) //価値の初期値
double value[100][N_ACT];//価値を格納する二次元配列[状態数][行動数]

/*乱数の設定*/
std::mt19937 mt;
std::random_device rnd;
std::uniform_real_distribution<double> rand1(0.0, 1.0);

/*ルーレット選択*/
int select_roullet(int stt, double tmp) {
	double div[100][N_ACT];//価値の合計
	div[stt][0] = value[stt][0];
	for (int k = 1; k < n_stt(); k++) {
		div[stt][k] = div[stt][k - 1] + value[stt][k];
	}
	/*価値の合計を1にする*/
	for (int k = 0; k < N_ACT; k++) {
		div[stt][k] = div[stt][k] / div[stt][N_ACT - 1];
	}
	/*乱数の値によって返り値を返す*/
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
	int act;//乱数から得た行動を格納
	int total;//ステップ数
	int fptotal;//fpで使用するステップ数(totalは価値の分配で使用し、初期化されてしまうため)
	double ntotal;//単位行動あたりの獲得報酬量を格納
	double tm;//乱数の収納
	int history_stt[10000];//状態の履歴
	int history_act[10000];//行動の履歴
	double sptotal[EPTIMES][JIKKEN];//[エピソード数][実験回数]

	/*ファイルへの書き込み*/
	FILE* fp;
	fopen_s(&fp, "Sutton_3.csv", "w");
	fprintf(fp, "エピソード数,単位行動あたりの獲得報酬量\n");
	/*ファイルがない場合、‐1を返す*/
	if (fp == NULL) {
		printf("error!");
		return -1;
	}
	/*指定された分の実験を繰り返す*/
	for (int n = 0; n < JIKKEN; n++) {
		mt.seed(n + 1);//実験回数を種とする決定的な乱数
		/*指定された分のエピソードを繰り返す*/
		for (int i = 0; i < EPTIMES; i++) {
			int stt = start();
			/*エピソード1において価値の初期値を代入*/
			if (i == 0) {
				for (int j = 0; j < n_stt(); j++) {
					for (int k = 0; k < N_ACT; k++) {
						value[j][k] = { SHOKICHI };
					}
				}
			}
			total = 0;//ステップ数の初期化
			/*1エピソード分開始*/
			while (stt != goal()) {
				tm = rand1(mt);
				int stt1 = stt;
				act = select_roullet(stt, tm);//行動の決定(0～3)
				/*決定された行動をもとに行動する*/
				/*0が上、1が右、2が下、3が左*/
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
				/*状態と行動の履歴*/
				history_stt[total] = stt1;
				history_act[total] = act;
				total++;
			}
			fptotal = total;//totalの値が変わる前にfptotalにステップ数を格納
			/*ステップ数から価値の配分*/
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
	/*エピソード数と単位行動あたりの獲得報酬量をファイルに書き込む*/
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