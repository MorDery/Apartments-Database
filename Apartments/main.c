#pragma once
#include "Header.h"
#include "Database.h"
#include "BinaryFile.h"
#include "TextFile.h"

void main()
{
	//initialize static variables
	List apartments;
	short int codeApartment = 0;
	short int codeCommand = 0;
	short int numCommand = 0;
	short_term_history[N] = NULL;
	//initialize database
	makeEmptyListCommand(&long_term_history);
	makeEmptyList(&apartments);
	//get data from files if exist
	if (isExist(BFileName , BinaryFile))
		getApartmentsFromFile(&apartments);
	if(isExist(TFileName,TextFile))
		getFromText();

	printf("Please enter one of the following commands:"
		"\nadd-an-apt, get-an-apt, buy-an-apt or delete-an-apt\n"
		"For reconstruction commands, please enter:"
		"\n!!, !num, history, short_history or !num^str1^str2\n"
		"To exit, enter exit.\n");
	printf(">> ");

 	char * command = input();
	while (strcmp(command, "exit") != 0)
	{
		commandSender(command, &apartments);
		if(command != NULL)
			FREE(command);
		printf(">> ");
		command = input();
	}
	//set data from database into files
	makeTextFile();
	makeBinaryFile(apartments);
	//release memory
	FREE(command);
	freeCommandList(&long_term_history);
	freeList(&apartments);
	freeShortHistory(short_term_history);
	printf("Good Bye!\n");
}

/*This Function Takes input from user*/
char * input()
{
	int size = 10, i = 0;
	char * input = (char *)calloc(size, sizeof(char));
	char ch = getchar();
	while (ch != ENTER)
	{
		input[i++] = ch;
		if (i == size - 1)
		{
			size *= 2;
			input = (char *)realloc(input, size * sizeof(char));
		}
		ch = getchar();
	}

	input[i] = '\0';
	input = (char *)realloc(input, (i+1) * sizeof(char));
	return input;
}
/*This Function checks if file is exist in program library*/
bool isExist(char * fileName,char type)
{
	FILE * file=NULL;
	if(type == BinaryFile)
		file = fopen(BFileName, "rb");
	if(type == TextFile)
		file = fopen(TFileName, "r");
	if (file == NULL)
		return false;
	fclose(file);
	return true;
}