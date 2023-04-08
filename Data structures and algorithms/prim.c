#include <stdio.h>
#include <stdlib.h>
#define ASIZE 12  /* �z��T�C�Y�i���_�j*/
#define ESIZE 40  /* �z��T�C�Y�i�Ӂj*/


struct edge { /*  ��(u,v)�Ƃ��̏d�� */
	int u;
	int v;
	int weight;

};


/*   �d�ݕt���O���t�̗אڃ��X�g�@*/

struct element {
	int vertex;
	int weight;
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

void append(struct element* l, int v, int w) /* ���X�g�̍Ō���ɒ��_v�Əd��w��}���@*/
{
	struct element* p;

	if (l->next != NULL)
		append(l->next, v, w);
	else {
		p = newl();
		p->vertex = v;
		p->weight = w;
		p->next = NULL;
		l->next = p;
	}
}

void printlist(struct element* l)    /* ���X�g�̃f�[�^���������*/
{
	if (l->next != NULL) {
		printf(" (v%d,%d)", l->next->vertex, l->next->weight);
		printlist(l->next);
	}
}


/* �אڃ��X�g�̑��� */

void createadjlist(struct element* a[], int n)
{
	int i;

	for (i = 1; i <= n; i++)
		a[i] = create();
}


void printadjlist(struct element* a[], int n)  /* �אڃ��X�g�̈�� */
{
	int i;

	for (i = 1; i <= n; i++) {
		printf("a[v%d", i);
		printf("] = ");
		printlist(a[i]);
		printf("\n");
	}
}


int makegraph(struct element* a[]) /* �אڃ��X�g�̍쐬 */
{
	createadjlist(a, 5);
	append(a[1], 2, 1);
	append(a[1], 3, 3);
	append(a[1], 5, 5);
	append(a[2], 1, 1);
	append(a[2], 3, 2);
	append(a[2], 5, 2);
	append(a[3], 1, 3);
	append(a[3], 2, 2);
	append(a[3], 4, 7);
	append(a[4], 3, 7);
	append(a[4], 5, 4);
	append(a[5], 1, 5);
	append(a[5], 2, 2);
	append(a[5], 4, 4);
	return 5;
}


int makegraph2(struct element* a[]) /* �אڃ��X�g�̍쐬2 */
{
	createadjlist(a, 10);
	append(a[1], 2, 4);
	append(a[1], 10, 3);
	append(a[2], 4, 1);
	append(a[2], 3, 2);
	append(a[2], 5, 1);
	append(a[2], 1, 4);
	append(a[3], 2, 2);
	append(a[3], 4, 3);
	append(a[4], 2, 1);
	append(a[4], 3, 3);
	append(a[5], 2, 1);
	append(a[5], 10, 3);
	append(a[5], 6, 4);
	append(a[6], 5, 4);
	append(a[6], 7, 5);
	append(a[6], 8, 3);
	append(a[6], 9, 6);
	append(a[7], 6, 5);
	append(a[7], 8, 4);
	append(a[8], 6, 3);
	append(a[8], 7, 4);
	append(a[8], 9, 2);
	append(a[9], 6, 6);
	append(a[9], 8, 2);
	append(a[10], 1, 3);
	append(a[10], 5, 3);
	return 10;
}

int makeedgearray(struct element* a[], struct edge E[], int n)
{
	int i, j;
	struct element* p;

	j = 0;
	for (i = 1; i <= n; i++) {
		p = a[i]->next;
		while (p != NULL) {
			E[++j].u = i;
			E[j].v = p->vertex;
			E[j].weight = p->weight;
			p = p->next;
		}
	}
	return j;
}

void printedgearray(struct edge E[], int m)
{
	int i;

	for (i = 1; i <= m; i++)
		printf("(%d,%d) %d\n", E[i].u, E[i].v, E[i].weight);
	printf("\n");
}


void swap(struct edge* e1, struct edge* e2)
{
	struct edge temp;

	temp = *e1;
	*e1 = *e2;
	*e2 = temp;
}


void sortedgearray(struct edge E[], int m)   /* �I��@�Ń\�[�g���� */
{
	int i, j, min;

	for (j = 1; j <= m - 1; j++) {
		min = j;
		for (i = j + 1; i <= m; i++)
			if (E[min].weight > E[i].weight)
				min = i;
		swap(&E[j], &E[min]);
	}
}

void reachability(struct element* T[], int reachable[], int n, int u) /* T�̓O���t�̗אڃ��X�g�\�� */
{
	int w;
	struct element* p;
	reachable[u] = 1;
	for (p = T[u]->next; p != NULL; p = p->next) {
		w = p->vertex;
		if (!reachable[w]) {			
			reachability(T, reachable, n, w);
		}
	}
}


void add(struct element* T[], struct edge e)
{
	append(T[e.u], e.v, e.weight);
	append(T[e.v], e.u, e.weight);
}


void clearreachable(int reachable[], int n)
{
	int i;

	for (i = 1; i <= n; i++)
		reachable[i] = 0;
}



/*P��T�̒��Ɋ��ɒǉ�����Ă���ӂ̒��_�ɂȂ���ӂ��i�[����֐�*/
int collect(struct edge P[],struct element *a[], struct element* T[], int n) {
	
	int i, j;
	struct element* p,*q;

	j = 0;
	for (i = 1; i <= n; i++) {
		p = T[i]->next;
		q = a[i]->next;
		if (p != NULL) {           /*����T[i]�ɗv�f�������P[n]��a[n]�̂��ׂĂ̗v�f������B�Ȃ����i��1�����B*/
			while (q != NULL) {
				P[++j].u = i;
				P[j].v = q->vertex;
				P[j].weight = q->weight;
				q = q->next;
			}
		}
	}
	return j;
}

void prim(struct edge E[], struct element *a[], struct element *T[], int m, int n)
{
	int sizeofT, reachable[ASIZE];
	
	sortedgearray(E, m);
	createadjlist(T, n);
	sizeofT = 1;/*prim�@�ł͍ŏ���1�ӂ�ǉ�����̂�sizeofT��1����X�^�[�g*/
	add(T, E[1]);/*�ł��d�݂��������ӂ�T�ɒǉ�*/
	while (sizeofT < n - 1) {
		int c, j = 0;
		struct edge e, P[ESIZE];/*P�͊��ɒǉ�����Ă���ӂ̒��_�ɂȂ���ӂ��i�[*/

	    c = collect(P, a, T,n);
		sortedgearray(P, c);/*P��weight�̏��������Ƀ\�[�g*/
		while (1) {
			e = P[++j];/*�I���ł���ӂ͊��ɒǉ�����Ă��钸�_�ɂȂ���ӂ̂�*/
			clearreachable(reachable, n);
			reachability(T, reachable, n, e.u);
			if (!reachable[e.v]) {
				add(T, e);
				++sizeofT;
				break;
			}
		}
	}
}

int main()
{
	int n, m;
	struct element* a[ASIZE], * T[ASIZE];
	struct edge E[ESIZE];

	n = makegraph(a);
	printf("adjlist of G\n");
	printadjlist(a, n);
	m = makeedgearray(a, E, n);
	prim(E, a, T, m, n);
	printf("adjlist of T\n");
	printadjlist(T, n);
}
