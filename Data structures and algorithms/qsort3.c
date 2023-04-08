#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define amax 10000
int N;

void gen_data(int a[], int n)     /* n個の整数をランダムに生成し、配列aに格納する */
{
	/*
	int i;
	for (i = 1; i <= n; i++) {
	a[i] = rand();
	}
	*/
	a[1] = 3;
	a[2] = 3;
	a[3] = 1;
	a[4] = 3;
	a[5] = 2;
	a[6] = 3;
	a[7] = 3;
	a[8] = 4;
	a[9] = 3;
	a[10] = 3;
	/*
	a[1] = 5;
	a[2] = 0;
	a[3] = 9;
	a[4] = 7;
	a[5] = 1;
	a[6] = 6;
	a[7] = 3;
	a[8] = 8;
	a[9] = 4;
	a[10] = 2;
	
	a[1] = 2;
	a[2] = 1;
	a[3] = 3;
	a[4] = 2;
	a[5] = 1;
	*/
}

void print_result(int a[], int n)           /* ソート結果を出力する */
{
	int i;

	for (i = 1; i <= n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

void swap(int* a, int* b)
{
	int temp;
	printf("swap *a=%d  *b=%d\n", *a, *b);
	temp = *a;
	*a = *b;
	*b = temp;
}


void partition(int a[], int p, int q, int* jp, int* ip) /* a[p..q]を分割する */
{
	int i, j, k = 1, s;
	char s1 = 'b';

	i = p;
	j = q;

	s = a[p];
	

	while ((p + k - 1) != q) {
		if (a[p + k] != s) {
			s1 = a[(p + k)];
			break;
		}
		k++;
	}

	if (s1 == 'b') {
		*jp = p;
		*ip = q;
		return;
	}else {
		if (s < s1) {
			s = s1;
		}
		while (i <= j) {
			while (a[i] < s) ++i;
			while (a[j] >= s) --j;
			if (i <= j) {
				swap(&a[i], &a[j]);
				++i;
				--j;
			}
		}
		*jp = j;
		*ip = i;
	}
}

void qsort(int a[], int p, int q) /* a[p..q]をソートする*/
{
	int i, j;
	printf("p=%d  q=%d\n", p, q);
	print_result(a, N);
	if (p < q) {
		partition(a, p, q, &j, &i);
		printf("j=%d  i=%d\n", j, i);
		qsort(a, p, j);
		qsort(a, i, q);
	}
}


int main() {
	int a[amax + 1];
	int n;
	clock_t c1, c2;

	//	n = 10000;
	n = 10;
	N = n;
	gen_data(a, n);
	print_result(a, n);
	c1 = clock();
	qsort(a, 1, n);
	c2 = clock();
	print_result(a, n);
	printf("time: %d\n", c2 - c1);
	return 0;
}
