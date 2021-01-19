//Radila sa kolegom Dujom Radman Livajom

/* 10. Napisati program koji iz datoteke cita postfiks izraz i zatim stvara stablo proracuna. 
Iz gotovog stabla proracuna upisati u datoteku infiks izraz.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Stablo;
typedef struct Stablo*st;
struct Stablo
{
	char* el;
	st L;
	st D;
};

struct Stog;
typedef struct Stog*poz;
struct Stog
{
	st stablo;
	poz next;
};

st Novo();
poz Novi();
int Inorder(st);
int Push(poz, st);
st Pop(poz);
st Citaj();

int main()
{
	st root = NULL;
	struct Stog head;
	head.next = NULL;

	root = Citaj(root, &head);

	Inorder(root);
	return 0;
}

st Citaj(st S, poz P)
{
	FILE*dat = NULL;
	char*ime = NULL;
	char*buff = NULL;

	ime = (char*)malloc(30 * sizeof(char));
	if (ime == NULL)
		printf("greska");

	printf("unesite ime datoteke:\n");
	scanf("%s", ime);

	if (strchr(ime, '.') == NULL)
		strcat(ime, ".txt");

	dat = fopen(ime, "r");
	if (dat == NULL)
		printf("greska");

	buff = (char*)malloc(30 * sizeof(char));

	while (!feof(dat))
	{
		fscanf(dat, "%s", buff);

		if (isdigit(buff[0]))
		{
			S = Novo();
			strcpy(S->el, buff);
			Push(P, S);
		}
		else if (buff[0] == '+' || buff[0] == '-' || buff[0] == '*' || buff[0] == '/')
		{

			S = Novo();
			strcpy(S->el, buff);

			S->D = Pop(P);
			S->L = Pop(P);

			Push(P, S);
		}
	}
	free(ime);
	free(buff);
	S = Pop(P);
	fclose(dat);

	return S;
}

st Novo()
{
	st q = NULL;
	q = (st)malloc(sizeof(struct Stablo));
	if (q == NULL)
		printf("greska");

	q->el = (char*)malloc(30 * sizeof(char));
	q->L = NULL;
	q->D = NULL;

	return q;
}
int Inorder(st S)
{
	if (S != NULL)
	{
		Inorder(S->L);

		printf("%s", S->el);

		Inorder(S->D);
	}
	return 0;
}

int Push(poz P, st S)
{
	poz q = NULL;
	q = (poz)malloc(sizeof(struct Stog));
	if (q == NULL)
		printf("greska");

	q->stablo = S;
	q->next = P->next;
	P->next = q;

	return 0;
}
st Pop(poz P)
{
	poz temp = NULL;
	st stablo = NULL;

	temp = P->next;
	stablo = temp->stablo;
	P->next = temp->next;

	free(temp);
	return stablo;
}