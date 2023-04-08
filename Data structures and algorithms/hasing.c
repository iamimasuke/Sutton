#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define m 11      /* 配列サイズ*/


/*   リストの基本操作　*/

struct element {
	int data;
	struct element* next;
};

struct element* newl()     /* メモリー上にセルの領域を確保　*/
{
	return((struct element*)malloc(sizeof(struct element)));
}

struct element* create()   /* 空リストを生成 */
{
	struct element* p;

	p = newl();
	p->next = NULL;
	return(p);
}

void insert(struct element* l, int k, int x) /* リストのk番目にxを挿入　*/
{
	struct element* p;

	if (k > 1)
		insert(l->next, k - 1, x);
	else {
		p = newl();
		p->data = x;
		p->next = l->next;
		l->next = p;
	}
}

int member(struct element* l, int x)  /* リスト中に整数xがあるかを判定　*/
{
	if (l->next == NULL)
		return 0;
	if (l->next->data == x)
		return 1;
	else
		member(l->next, x);
}

void deleteall(struct element* l, int x)  /* リストから整数xをすべて削除する*/
{
	struct element* tmp;
	if (l->next == NULL)
		return;
	if (l->next->data == x) {
		tmp = l->next;
		l->next = l->next->next;
		free(tmp);
		deleteall(l, x);
	}
	else deleteall(l->next, x);
}

void printlist(struct element* l)    /* リスト内のデータををすべて印刷する*/
{
	if (l->next != NULL) {
		printf(" %d", l->next->data);
		printlist(l->next);
	}
}



/*  ハッシュ表の基本操作　*/



int h(int x)       /*  ハッシュ関数　*/
{
	return(x % m);
}

void initializehash(struct element* a[], int x) /*  ハッシュ表の初期化　*/
{
	if (a[h(x)]->next == NULL) {
		a[h(x)] = create();
	}
}



//void initializehash(struct element* a[]) /*  ハッシュ表の初期化　*/
//{
//	for (int i = 0; i <= m - 1; i++) {
//			a[i] = create();
//	}
//}



void inserthash(struct element* a[], int x)  /*  ハッシュ表にxを挿入　*/
{
	insert(a[h(x)], 1, x);
}

void deletehash(struct element *a[], int x)  /* ハッシュ表からxを削除する */
{
		deleteall(a[h(x)], x);
}

int memberhash(struct element* a[], int x) /* ハッシュ表にxがあるかを判定 */
{
	return(member(a[h(x)], x));
}

void printhash(struct element* a[])  /* ハッシュ表を印刷する */
{
	int i;
	for (i = 0; i < m; i++) {
		printf("a[%d", i);
		printf("] = ");
		printlist(a[i]);
		printf("\n");
	}
}

void deleteList(struct element* l)
{
	if (l != NULL) {
		deleteList(l->next);
		free(l);
	}
	else {
		return;
	}
}

void deleteallhash(struct element* a[]) 
{
	for (int i = 0; i < m; i++)
		if(a[i]->next != NULL)
		deleteList(a[i]);
}

void deleteEmptyList(struct element* a[]) 
{
	struct element* p;
	int i;

	for (i = 0; i < m; i++) {
		p = a[i]->next;
		if (p == NULL)
			deleteList(a[i]);
	}
}



int main()
{
	int x;
	struct element* a[m];
	//initializehash(a);
	printf("Next integer(0:end) = ");
	scanf("%d", &x);          /* コンソールから整数xを読みこむ */
	while (x != 0) {
		initializehash(a,x);
		inserthash(a, x);              /* ハッシュ表に挿入する */
		printf("Next integer(0:end) = ");
		scanf(" %d", &x);
	}
	//deleteEmptyList(a);
	printhash(a);
	printf("Member integer(0:end) = ");
	scanf("%d", &x);          /* コンソールから整数xを読みこむ */
	while (x != 0) {
		printf("%d", memberhash(a, x));  /* 1:ハッシュ表にxがある 0:ない */
		printf("\nMember integer(0:end) = ");
		scanf(" %d", &x);
	}
	printhash(a);
	printf("Delete integer(0:end) = ");
	scanf("%d", &x);          /* コンソールから整数xを読みこむ */
	while (x != 0) {
		deletehash(a, x);     /* ハッシュ表からxを削除する */
		printhash(a);
		printf("Delete integer(0:end) = ");
		scanf(" %d", &x);
	}
	deleteallhash(a);
}
