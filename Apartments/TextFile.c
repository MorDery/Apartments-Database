#include "TextFile.h"
short int codeCommand;
short int numCommand;

/*This Function creates text file that stores commands history data from last run*/
void makeTextFile()
{
	FILE * newFile;
	ListNodeCommand *curr;
	curr = long_term_history.head;
	newFile = fopen(TFileName, "w");
	assert(newFile != NULL);
	fprintf(newFile, "%hd\n", numCommand);// save number of all the command
	fprintf(newFile, "%hd\n", codeCommand);//save number of code in list
	for (int i = N - 1; i >= 0; i--)
	{
		fputs(short_term_history[i], newFile);//save command
		fputs("\n", newFile);
	}
	addToText(curr, newFile);
	fclose(newFile);
}

/*This Function puts data into text file*/
void addToText(ListNodeCommand *lst, FILE *newFile)
{
	if (lst == NULL)
		return;
	addToText(lst->next, newFile);
	fprintf(newFile, "%hd", lst->code);//save code command
	fputs("\n", newFile);
	fputs(lst->command, newFile);//save command
	fputs("\n", newFile);
}

/*This Function gets commands history data from files*/
void getFromText()
{
	FILE * newFile;
	newFile = fopen(TFileName, "r");
	assert(newFile != NULL);
	if (newFile == NULL)
	{
		return;
	}
	fscanf(newFile, "%hd\n", &numCommand);// save number of all the command
	fscanf(newFile, "%hd\n", &codeCommand);//save number of code in list
	for (int i = N - 1; i >= 0; i--)
	{
		short_term_history[i] = (char*)calloc(LINE, sizeof(char));
		fgets(short_term_history[i], LINE, newFile);//save command
		short_term_history[i] = (char *)realloc(short_term_history[i], (strlen(short_term_history[i]) + 1) * sizeof(char));
		(short_term_history[i])[strlen(short_term_history[i]) - 1] = '\0';
	}
		addToList(newFile);
		fclose(newFile);
}

/*This Function inserts data of commands history into database*/
void addToList(FILE *newFile)
{
	short int code=0;
	char* command = NULL;
	
	fscanf(newFile, "%hd\n", &code);//save code command
	if (code==0)
	{
		return;
	}
	command = (char*)calloc(LINE, sizeof(char));
	fgets(command, LINE, newFile);//save command
	command = (char *)realloc(command, (strlen(command) +1) * sizeof(char));
	command[strlen(command)-1] = '\0';
	addToList(newFile);
	fclose(newFile);
	insertDataToEndListCommandFromText(&long_term_history, code, command);
}

/*This function inserts data to end of list*/
void insertDataToEndListCommandFromText(ListCommand* lst, short int code, char * command)
{
	ListNodeCommand* newTail;
	newTail = createNewListNodeCommandFromText(code, command, NULL);
	insertNodeToEndListCommand(lst, newTail);
}
/*This function creates ListNodeCommandFromText*/
ListNodeCommand* createNewListNodeCommandFromText(short int code, char* command, ListNodeCommand * next)
{
	ListNodeCommand* res;
	res = (ListNodeCommand*)calloc(1,sizeof(ListNodeCommand));
	res->code = code;
	res->command = command;
	res->next = next;
	return res;
}