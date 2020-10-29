#ifdef _MSC_VER
#endif
//#include "pch.h" 

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char ime[20];
	char prez[20];
	int bod;
}student;


int main()
{
	FILE *fp = NULL;
	char str[20], ch;
	student *st;
	int i, n = 0, max = 0;

	printf("upisi ime datoteke: ");
	scanf(" %s", str);

	fp = fopen(str, "r");
	if (fp == NULL)
	{
		printf("Greska pri otvaranju datoteke!");
	}

	while (!feof(fp))
	{
		ch = fgetc(fp);
		if (ch == '\n') ++n;
	}

	st = (student*)malloc(n * sizeof(student));

	rewind(fp);

	for (i = 0; i < n; i++)
	{
		fscanf(fp, " %s %s %d", st[i].ime, st[i].prez, &st[i].bod);
		if (st[i].bod > max)
			max = st[i].bod;

	}

	printf("IME\tPREZIME\tAPSOLUTNO\tRELATIVNO\n");
	for (i = 0; i < n; i++)
	{
		printf("%s    %s    %d    %.2f\n", st[i].ime, st[i].prez, st[i].bod, (float)st[i].bod / max * 100);
	}
	return 0;
}