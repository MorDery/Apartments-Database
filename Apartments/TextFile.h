#pragma once
#include "Header.h"
#include"Database.h"
#define TFileName "commands.txt"
#define LINE 100

void makeTextFile();
void addToText(ListNodeCommand *lst, FILE *newFile);
void getFromText();
void addToList(FILE *newFile);
void insertDataToEndListCommandFromText(ListCommand* lst, short int code, char * command);
ListNodeCommand* createNewListNodeCommandFromText(short int code, char* command, ListNodeCommand * next);