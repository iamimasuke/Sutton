#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define m 11      /* �z��T�C�Y*/


/*   ���X�g�̊�{����@*/

struct element {
	int data;
	struct element* next;
};

struct element* newl()     /* �������[��ɃZ���̗̈���m�ہ@*/
{
	return((struct element*)malloc(sizeof(struct element)));
}

struct element* create()   /* �󃊃X�g�𐶐� */
{
	struct element* p;

	p = newl();
	p->next = NULL;
	return(p);
}

void insert(struct element* l, int k, int x) /* ���X�g��k�Ԗڂ�x��}���@*/
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

int member(struct element* l, int x)  /* ���X�g���ɐ���x�����邩�𔻒�@*/
{
	if (l->next == NULL)
		return 0;
	if (l->next->data == x)
		return 1;
	else
		member(l->next, x);
}

void deleteall(struct element* l, int x)  /* ���X�g���琮��x�����ׂč폜����*/
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

void printlist(struct element* l)    /* ���X�g���̃f�[�^�������ׂĈ������*/
{
	if (l->next != NULL) {
		printf(" %d", l->next->data);
		printlist(l->next);
	}
}



/*  �n�b�V���\�̊�{����@*/



int h(int x)       /*  �n�b�V���֐��@*/
{
	return(x % m);
}

void initializehash(struct element* a[], int x) /*  �n�b�V���\�̏������@*/
{
	if (a[h(x)]->next == NULL) {
		a[h(x)] = create();
	}
}



//void initializehash(struct element* a[]) /*  �n�b�V���\�̏������@*/
//{
//	for (int i = 0; i <= m - 1; i++) {
//			a[i] = create();
//	}
//}



void inserthash(struct element* a[], int x)  /*  �n�b�V���\��x��}���@*/
{
	insert(a[h(x)], 1, x);
}

void deletehash(struct element *a[], int x)  /* �n�b�V���\����x���폜���� */
{
		deleteall(a[h(x)], x);
}

int memberhash(struct element* a[], int x) /* �n�b�V���\��x�����邩�𔻒� */
{
	return(member(a[h(x)], x));
}

void printhash(struct element* a[])  /* �n�b�V���\��������� */
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
	scanf("%d", &x);          /* �R���\�[�����琮��x��ǂ݂��� */
	while (x != 0) {
		initializehash(a,x);
		inserthash(a, x);              /* �n�b�V���\�ɑ}������ */
		printf("Next integer(0:end) = ");
		scanf(" %d", &x);
	}
	//deleteEmptyList(a);
	printhash(a);
	printf("Member integer(0:end) = ");
	scanf("%d", &x);          /* �R���\�[�����琮��x��ǂ݂��� */
	while (x != 0) {
		printf("%d", memberhash(a, x));  /* 1:�n�b�V���\��x������ 0:�Ȃ� */
		printf("\nMember integer(0:end) = ");
		scanf(" %d", &x);
	}
	printhash(a);
	printf("Delete integer(0:end) = ");
	scanf("%d", &x);          /* �R���\�[�����琮��x��ǂ݂��� */
	while (x != 0) {
		deletehash(a, x);     /* �n�b�V���\����x���폜���� */
		printhash(a);
		printf("Delete integer(0:end) = ");
		scanf(" %d", &x);
	}
	deleteallhash(a);
}
