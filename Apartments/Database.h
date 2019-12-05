#pragma once
#include "Header.h"
short int codeApartment;

typedef struct listNodeCommand {
	int code;
	char * command;
	struct listNodeCommand* next;
} ListNodeCommand;

typedef struct listCommand {
	ListNodeCommand* head;
	ListNodeCommand* tail;
} ListCommand;

//databases [static]
char * short_term_history[N];
ListCommand long_term_history;

//assistants function
int foundStr(char * str1, char* str2);
char *  updateCommand(char * oldCommand, char * newCommand, char * input);

//prototypes for History functions
void addToShortHistory(char*short_term_history[], ListCommand *long_term_history, char* input);
void addToLongHistory(ListCommand *long_term_history, char* input);
void arrangeArray(char* history[]);
void reproduction(char* input, char*short_term_history[], ListCommand *long_term_history, List *aparments);
void freeShortHistory(char * shortHistory[]);

//prototypes for CommandLists functions
void insertDataToEndListCommand(ListCommand* lst, char* data);
void insertNodeToEndListCommand(ListCommand* lst, ListNodeCommand * newTail);
ListNodeCommand* createNewListNodeCommand(char* data, ListNodeCommand * next);
void makeEmptyListCommand(ListCommand* lst);
bool isEmptyListCommand(ListCommand lst);
void deleteNodeCommand(ListNodeCommand *deleteApp);
void deleteHeadCommand(ListCommand* lst);
int countCommandList(ListCommand apartments);
void freeCommandList(ListCommand * lst);
void freeCommandListRec(ListNodeCommand * node);
