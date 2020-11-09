#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#define BUFFER_LENGTH 1024
#define ERROR -1
#define SUCCESS 0


typedef struct student* Position;
typedef struct student {
	char name[BUFFER_LENGTH];
	char surname[BUFFER_LENGTH];
	int birht_year;
	Position Next;
}student;



int Print_Menu();
Position CreateListNode(Position);
Position Insert_Student_Data(Position);
int Insert_At_Beggining_Of_List(Position);
int Print_List(Position);
Position Find_Last(Position);
int Insert_At_End_Of_List(Position);
Position Find_By_LastName(Position);
int Delete_By_LastName(Position);
Position Find_Previous_List_Element(Position);
int Garbage_Collector(Position);


int Insert_After_LastName(Position);
int Insert_Before_LastName(Position);
int Sort_List_By_LastName(Position);
int Print_To_File(Position);
int Load_From_File(Position);



int main()
{
	student head;
	Position searched_Student = NULL;
	char *choice;
	head.Next = NULL;
	choice = (char*)malloc(sizeof(char)*BUFFER_LENGTH);
	if (choice == NULL)
	{
		printf("\nMemorija nije dobro alocirana.");
		return ERROR;
	}
	memset(choice, '\0', BUFFER_LENGTH);

	while (strcmp(choice, "EXIT") != SUCCESS)
	{
		memset(choice, 0, BUFFER_LENGTH);
		Print_Menu();

		scanf(" %s", choice);

		if (strcmp(choice, "1") == SUCCESS)
		{
			Insert_At_Beggining_Of_List(&head);
		}
		else if (strcmp(choice, "2") == SUCCESS)
		{
			Print_List(&head);
		}
		else if (strcmp(choice, "3") == SUCCESS)
		{
			Insert_At_End_Of_List(&head);
		}
		else if (strcmp(choice, "4") == SUCCESS)
		{
			searched_Student = Find_By_LastName(&head);
			if (searched_Student != NULL)
			{
				printf("\nTrazili ste studenta:\n %s %s %d\n", searched_Student->name, searched_Student->surname, searched_Student->birht_year);
			}
			else
			{
				printf("\nStudent kojeg ste unijeli trenutno nije u bazi podataka.\n");
			}
		}
		else if (strcmp(choice, "5") == SUCCESS)
		{
			Delete_By_LastName(&head);
			Print_List(&head);
		}

		else if (strcmp(choice, "6") == SUCCESS)
		{
			Insert_After_LastName(&head);
			Print_List(&head);
		}
		else if (strcmp(choice, "7") == SUCCESS)
		{
			Insert_Before_LastName(&head);
			Print_List(&head);
		}
		else if (strcmp(choice, "8") == SUCCESS)
		{
			Sort_List_By_LastName(&head);
			Print_List(&head);
		}
		else if (strcmp(choice, "9") == SUCCESS)
		{
			Read_From_File(&head);
			Print_List(&head);
		}
		else if (strcmp(choice, "A") == SUCCESS)
		{
			Print_To_File(&head);
			Print_List(&head);
		}


		else if (strcmp(choice, "Exit") == SUCCESS)
		{
			break;
		}
		else
		{
			printf("\nNepravilan unos <%s>.\tProbajte ponovo.\n", choice);
		}
	}
	free(choice);
	Garbage_Collector(&head);

	return SUCCESS;
}

int Print_Menu()
{
	printf("1. Unesi studenta na pocetak.\n");
	printf("2. Ispisi listu.\n");
	printf("3. Unesi studenta na kraj.\n");
	printf("4. Pronadji preko prezimena.\n");
	printf("5. Izbrisi preko prezimena.\n");

	printf("6. Unesi element nakon studenta.\n");
	printf("7. Unesi element prije studenta.\n");
	printf("8. Sortiraj bazu podataka.\n");
	printf("9. Ucitaj listu iz datoteke.\n");

	printf("A. Ispisi listu u FILE.\n");
	printf("Exit. Izadji iz programa.\n");

	printf("\nUnesite izbor : ");

	return SUCCESS;
}

int Insert_At_Beggining_Of_List(Position P)
{

	Position Q = NULL;
	Q = CreateListNode(Q);

	if (Q == NULL)
	{
		printf("\nMemorija nije dobro alocirana za varijablu u CreateListNode.");
		return ERROR;
	}
	Q = Insert_Student_Data(Q);
	if (Q == NULL)
	{
		printf("\nEror u funkciji Insert_Student_Data.");
		return ERROR;
	}

	Q->Next = P->Next;
	P->Next = Q;

	return SUCCESS;
}

Position CreateListNode(Position Q)
{
	Q = (Position)malloc(sizeof(student));
	if (Q == NULL)
	{
		printf("\nMemorija nije dobro alocirana za varijablu u CreateListNode.");
		return NULL;
	}

	Q->Next = NULL;
	return Q;
}
Position Insert_Student_Data(Position Q)
{
	if (Q == NULL) {
		printf("\nDoslo je do pogreske u Insert_Student_Data funkciji.");
		return NULL;
	}
	printf("Unesite ime, prezime i godinu rodjena studenta: \n");
	scanf(" %s %s %d", Q->name, Q->surname, &Q->birht_year);

	return Q;
}

int Print_List(Position P) {
	P = P->Next;
	if (P == NULL) {
		printf("\nBaza podataka je prazna!");
	}
	else {
		printf("\nOvi studenti su u bazi podataka: \r\n");
		while (P != NULL) {
			printf("%s %s %d\r\n", P->name, P->surname, P->birht_year);
			P = P->Next;
		}
	}
	printf("\n");
	return SUCCESS;
}

int Insert_At_End_Of_List(Position P) {
	if (P == NULL) {
		printf("\nDoslo je do pogreske u funkciji Insert_At_End_Of_List.");
		return ERROR;
	}
	P = Find_Last(P);
	return Insert_At_Beggining_Of_List(P);
}
Position Find_Last(Position P) {
	if (P == NULL) {
		printf("\nDoslo je do pogreske u funkciji Find_Last.");
		return NULL;
	}
	while (P->Next != NULL)
		P = P->Next;

	return P;
}

Position Find_By_LastName(Position P) {
	P = P->Next;
	char *lastName = NULL;
	lastName = (char*)malloc(sizeof(char)*BUFFER_LENGTH);
	if (lastName == NULL) {
		printf("\nDoslo je do pogreske u funkciji Find_By_LastName.");
		return NULL;
	}
	memset(lastName, '\0', BUFFER_LENGTH);

	printf("\nUnesite prezime studenta kojeg trazite: \n");
	scanf(" %s", lastName);
	while (P != NULL && strcmp(P->surname, lastName) != 0) {
		P = P->Next;
	}
	free(lastName);
	return P;
}

int Delete_By_LastName(Position P) {
	Position temp = NULL;
	P = Find_Previous_List_Element(P);
	if (P == NULL) {
		printf("\nStudent kojeg ste trazili prezimenom ne postoji u bazi podataka.");
		return ERROR;
	}
	temp = P->Next;
	if (temp != NULL) {
		P->Next = temp->Next;
		printf("\nStudent sa sljedecim podacima bit ce uklonjen s liste: %s %s %d", temp->name, temp->surname, temp->birht_year);
		free(temp);
	}
	return SUCCESS;
}
Position Find_Previous_List_Element(Position P) {
	char *lastName = NULL;

	lastName = (char*)malloc(sizeof(char)*BUFFER_LENGTH);
	if (lastName == NULL) {
		printf("Doslo je do pogreske u Find_Previous_List_Element");
		return NULL;
	}
	memset(lastName, '\0', BUFFER_LENGTH);
	printf("Unesite prezime studenta kojeg trazite: ");
	scanf(" %s", lastName);
	while (P->Next != NULL && strcmp(P->Next->surname, lastName) != 0)
		P = P->Next;

	if (P->Next == NULL)
		return NULL;

	free(lastName);

	return P;
}
int Garbage_Collector(Position P) {
	if (P->Next != NULL) {
		Garbage_Collector(P->Next);
	}
	free(P);
	return SUCCESS;
}


int Insert_After_LastName(Position P)
{
	P = Find_By_LastName(P);
	if (P == NULL) {
		printf("\nDoslo je do pogreske u funkciji Insert_After_LastName\n");
		return ERROR;
	}
	return Insert_At_Beggining_Of_List(P);
}
int Insert_Before_LastName(Position P) {
	P = Find_Previous_List_Element(P);
	if (P == NULL) {
		printf("\nDoslo je do pogreske u funkciji Insert_Before_LastName");
		return ERROR;
	}
	return Insert_At_Beggining_Of_List(P);
}
int Read_From_File(Position P) {
	Position Q = NULL;
	char *fileName = NULL;
	FILE *fp = NULL;

	fileName = (char*)malloc(sizeof(char)*BUFFER_LENGTH);
	if (fileName == NULL) {
		printf("\nMemorija nije dobro alocirana u funkciji Print_To_File.");
		return ERROR;
	}
	memset(fileName, '\0', BUFFER_LENGTH);

	printf("\nUnesite ime datoteke.\n");
	scanf(" %s", fileName);

	if (strchr(fileName, '.') == NULL) {
		strcat(fileName, '.txt');
	}

	fp = fopen(fileName, "w+");
	if (fp == NULL) {
		printf("\nDoslo je do pogreske u otvaranju datoteke.\n");
		return ERROR;
	}
	while (!feof(fp)) {
		Q = CreateListNode(Q);
		if (Q == NULL)
		{
			printf("\nMemorija nije dobro alocirana u funkciji Read_From_File!");
			return ERROR;
		}
		fscanf(fp, " %s %s %d", Q->name, Q->surname, &Q->birht_year);

		Q->Next = P->Next;
		P->Next = Q;
	}
	fclose(fp);
	return SUCCESS;
}

int Print_To_File(Position P) {
	FILE *fp = NULL;
	char *fileName = NULL;

	fileName = (char*)malloc(sizeof(char)*BUFFER_LENGTH);
	if (fileName == NULL) {
		printf("\nMemorija nije dobro alocirana u funkciji Print_To_File.");
		return ERROR;
	}
	memset(fileName, '\0', BUFFER_LENGTH);

	printf("\nUnesite ime datoteke.\n");
	scanf(" %s", fileName);

	if (strchr(fileName, '.') == NULL) {
		strcat(fileName, '.txt');
	}

	fp = fopen(fileName, "w+");
	if (fp == NULL) {
		printf("\nDoslo je do pogreske u otvaranju datoteke u Print_To_File funkciji.\n");
		return ERROR;
	}
	while (P != NULL) {
		fprintf(fp, "%s %s %d", P->name, P->surname, P->birht_year);
		P = P->Next;
		if (P != NULL) {
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
	return SUCCESS;
}
int Sort_List_By_LastName(Position P) {
	Position i = P;
	Position j = NULL;
	Position prev_j = NULL;
	Position end = NULL;

	while (i->Next != end) {
		prev_j = i;
		j = prev_j->Next;
		while (j->Next != end) {
			if (strcmp(j->surname, j->Next->surname) > 0) {
				prev_j->Next = j->Next;
				j->Next = j->Next->Next;
				prev_j->Next->Next = j;
				j = prev_j->Next;
			}
			prev_j = j;
			j = j->Next;
		}
		end = j;
	}
	return SUCCESS;
}