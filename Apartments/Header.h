#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 100
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <assert.h>

#define SWAP(type,a,b) { type temp = a; a = b; b = temp; } // swap between types
#define FREE(ptr) do{free((ptr));(ptr) = NULL;}while(0) // free memory and set it pointer to NULL
#define ENTER '\n'
#define BFileName "apartments.bin"
#define TFileName "commands.txt"
#define TextFile 't'
#define BinaryFile 'b'
#define N 7

//structs declarations
typedef struct date
{
	short int day;
	short int month;
	short int year;
} Date;

typedef struct appartment
{
	short int code;
	char * andress;
	int price;
	short int rooms;
	struct date entrance;
	struct date entryDate;
} Apartment;

typedef struct listNode {
	Apartment appData;
	struct listNode* next;
} ListNode;

typedef struct list {
	ListNode* head;
	ListNode* tail;
} List;

//apartments identification code and list [static] 
extern short int codeApartment;

//commands identification code [static]
extern short int numCommand ;
extern short int codeCommand;

/* prototype for commandSender*/
void commandSender(char* input, List *apartments);
Apartment * copyToArray(List apartments, int * size);

/* prototype for main Function*/
char * input();

/*prototypes for date functions*/
Date getCurrentTime();
Date stod(char * str);
char * dtos(Date date);
Date getSpecificTime(int daysBefore);
int dateCompare(Date date1, Date date2);
bool isBetweenDates(Date prev, Date check, Date curr);

//prototypes for Lists functions
void insertDataToEndList(List* lst, Apartment data);
void insertNodeToEndList(List* lst, ListNode * newTail);
ListNode* createNewListNode(Apartment data, ListNode * next);
void makeEmptyList(List* lst);
bool isEmptyList(List lst);
void deleteNode(ListNode *deleteApp);
void deleteHead(List* lst);
int count(List apartments);
void freeList(List * lst);
void freeListRec(ListNode * node);
bool isExist(char * fileName, char type);