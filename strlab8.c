//Duje Radman Livaja i ja zajedno radili
/*
Napisati program koji generira slučajne brojeve u opsegu od 50-80. Ukoliko je generirani broj paran
sprema se u vezanu listu parnih brojeva i to u padajućem redoslijedu (od najvećeg prema najmanjem).
Ukoliko je broj neparan sprema se u vezanu listu neparnih brojeva, također u padajućem redoslijedu.

Niti jedna vezana lista ne smije sadržavati dva ista elementa. Unos traje sve dok obje liste ne sadrže 10
elemenata. Treba ispisivati koji se broj generira i na kraju ispisati obje liste.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

struct list;
typedef struct list* pos;

typedef struct list
{
	int el;

	pos next;
}list;

pos CreateNode();
int PrintList(pos);
int InsertList(int, pos);
pos FindPlace(int, pos);
pos Find(int, pos);

int main()
{
	pos p1 = NULL, p2 = NULL;
	pos q = NULL;
	int n = 0;
	int br1 = 0, br2 = 0;
	int brojac = 1;
	srand((unsigned)time(NULL));

	p1 = CreateNode();

	if (p1 == NULL)
		return -1;

	p1->next = NULL;

	p2 = CreateNode();

	if (p2 == NULL)
		return -1;

	p2->next = NULL;

	while (br1 != 10 || br2 != 10)
	{
		n = rand() % (80 - 50) + 50;
		printf("Izgeneriran je %d. broj: %d \n", brojac, n);
		brojac++;

		if (n % 2 == 0 && br1 != 10)
		{
			q = Find(n, p1);

			if (q == NULL)
			{
				br1++;
				q = FindPlace(n, p1);
				InsertList(n, q);
			}
		}

		if (n % 2 != 0 && br2 != 10)
		{
			q = Find(n, p2);

			if (q == NULL)
			{
				br2++;
				q = FindPlace(n, p2);
				InsertList(n, q);
			}
		}
	}


	printf("\n Prva lista\n\n ");
	PrintList(p1->next);

	printf("\n\n Druga lista \n\n ");
	PrintList(p2->next);

	printf("\n\n");

	return 0;
}

pos CreateNode()
{
	pos q = NULL;

	q = (pos)malloc(sizeof(list));

	if (q == NULL)
	{
		printf("Neuspjesno alocirana memorija\n");
		return NULL;
	}

	return q;
}

int PrintList(pos p)
{
	if (p == NULL)
	{
		printf("Lista je prazna\n");
		return -1;
	}

	while (p != NULL)
	{
		printf("%d ", p->el);
		p = p->next;
	}

	return 0;
}

int InsertList(int el, pos p)
{
	pos q = NULL;

	q = CreateNode();

	if (q == NULL)
		return -1;

	q->el = el;

	q->next = p->next;
	p->next = q;

	return 0;
}

pos FindPlace(int n, pos p)
{
	while (p->next != NULL && n > p->next->el)
		p = p->next;

	return p;
}

pos Find(int n, pos p)
{
	while (p != NULL && n != p->el)
		p = p->next;

	return p;
}
