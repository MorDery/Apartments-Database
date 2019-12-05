#include "Database.h"
short int numCommand;
short int codeCommand;

/*This Function takes arguments of command and insert it to short history Database*/
void addToShortHistory(char*short_term_history[], ListCommand *long_term_history, char* input)
{
	char* command;
	command = (char *)calloc(strlen(input)+1, sizeof(char));
	strcpy(command, input);
	if (numCommand >= N)
	{
		if (codeCommand == 0)
			makeEmptyListCommand(long_term_history);
		addToLongHistory(long_term_history, short_term_history[0]);
		arrangeArray(short_term_history);
		short_term_history[N - 1] = command;
		numCommand++;
	}
	else
	{
		short_term_history[numCommand] = command;
		numCommand++;
	}
}
/*This Function takes arguments of command and insert it to long term history Database*/
void addToLongHistory(ListCommand * long_term_history, char* input)
{
	insertDataToEndListCommand(long_term_history, input);
}
/*This Function make arrangement in the short history Database after delivery to long term history*/
void arrangeArray(char* history[])
{
	int i = 0;
	for(i=0;i<N-1;i++)
	{
		SWAP(char *,history[i],history[i+1]);
	}
	history[i] = NULL;
}
/*This Function takes arguments of command and does one of this:
1. go to long_term_history/short history Databases and get the requested command from it.
2. after get the requested command, it change part of it and use the new command.
3. prints all Database or only the short term Database.*/
void reproduction(char* input, char * short_term_history[], ListCommand  * long_term_history, List  * apartments)
{
	int num;
	ListNodeCommand *history;
	char *oldCommand=NULL, *newCommand=NULL, *command = NULL;
	char * saveInput = input;

	if (strcmp(input, "!!") == 0)
	{
		if (numCommand <= N)
		{
			commandSender(short_term_history[numCommand - 1], apartments);
		}
		else
		{
			commandSender(short_term_history[N - 1], apartments);
		}
	}
	else if (input[0] == '!')
	{
		if (strstr(input, "^") != NULL)
		{
			input++;
			input = strtok(input, "^");
			num = atoi(input);
			input = strtok(NULL, "^");
			oldCommand = (char *)calloc(strlen(input) + 1, sizeof(char));
			strcpy(oldCommand, input);
			input = strtok(NULL, "\0");
			newCommand = (char *)calloc(strlen(input) + 1, sizeof(char));
			strcpy(newCommand, input);

			if (num > codeCommand)
			{
				command = (char*)calloc((strlen(short_term_history[num - codeCommand - 1])+1), sizeof(char));
				strcpy(command, short_term_history[num - codeCommand - 1]);
			}
			else
			{
				history = long_term_history->head;
				while (history != NULL)
				{
					if (history->code == num)
					{
						command = (char*)calloc(strlen(history->command)+1, sizeof(char));
						strcpy(command, history->command);
					}
					history = history->next;
				}
			}
			char  *updatedCommand = updateCommand(oldCommand, newCommand, command);
			commandSender(updatedCommand, apartments);
			input = saveInput;
			FREE(oldCommand);
			FREE(newCommand);
			FREE(updatedCommand);
			FREE(command);
		}

		else
		{
			input++; // to avoid '!'
			num = atoi(input);
			if (num >= numCommand - N - 1)
				commandSender(short_term_history[num - codeCommand - 1], apartments);
			else
			{
				history = long_term_history->head;
				while (history != NULL)
				{
					if (history->code == num)
					{
						commandSender(history->command, apartments);
						return;
					}
					history = history->next;
				}
			}
			input = saveInput;
		}
	}
	else if (strcmp(input, "short_history") == 0)
	{
		for(int i=0 ;i < N ; i++)
		{
			printf("%d: %s\n", (codeCommand + 1 + i), short_term_history[i]);
		}
	}
	else if (strcmp(input, "history") == 0)
	{
		history = long_term_history->head;
		while (history != NULL)
		{
			printf("%d: %s\n", history->code, history->command);
			history = history->next;
		}

		for(int i=0;i < numCommand - codeCommand;i++)
		{
			printf("%d: %s\n", (i+1+ numCommand - N), short_term_history[i]);
		}
	}
	else
	{
		printf("Wrong input");
		exit(1);
	}
}

/*This Function insert new input to end of list*/
void insertDataToEndListCommand(ListCommand* lst, char * data)
{
	ListNodeCommand* newTail;
	newTail = createNewListNodeCommand(data, NULL);
	insertNodeToEndListCommand(lst, newTail);
}
/*This Function insert new node to end of list*/
void insertNodeToEndListCommand(ListCommand* lst, ListNodeCommand * newTail)
{
	if (isEmptyListCommand(*lst))
	{
		lst->head = lst->tail = newTail;
	}
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

/*This Function creates new node and insert input*/
ListNodeCommand* createNewListNodeCommand(char* data, ListNodeCommand * next)
{
	ListNodeCommand* res;
	res = (ListNodeCommand*)malloc(sizeof(ListNodeCommand));
	res->code = ++codeCommand;
	res->command = data;
	res->next = next;
	return res;
}

/*This Function makes empty list*/
void makeEmptyListCommand(ListCommand* lst)
{
	lst->head = lst->tail = NULL;
}
/*This Function checks if list is empty*/
bool isEmptyListCommand(ListCommand lst)
{
	return (lst.head == NULL);
}
/*This Function deletes node*/
void deleteNodeCommand(ListNodeCommand *deleteApp)
{
	ListNodeCommand *temp;
	temp = deleteApp;
	deleteApp->next = temp->next;
	FREE(temp);
}
/*This Function deletes head node*/
void deleteHeadCommand(ListCommand* command)
{
	ListNodeCommand *deleteApp = command->head;
	command->head = deleteApp->next;
	FREE(deleteApp);
	return;
}
/*This Function counts how many nodes does exist*/
int countCommandList(ListCommand apartments)
{
	ListNodeCommand * curr = apartments.head;
	if (curr == NULL)
		return 0;
	int count = 0;
	while (curr != NULL)
	{
		count++;
		curr = curr->next;
	}
	return count;
}
/*This Function gets list and FREE its memory*/
void freeCommandList(ListCommand * lst)
{
	freeCommandListRec(lst->head);
	lst->head = NULL;
	lst->tail = NULL;
}
void freeCommandListRec(ListNodeCommand * node)
{
	if (node == NULL)
		return;
	freeCommandListRec(node->next);
	char * freeCommand = node->command;
	FREE(freeCommand);
	FREE(node);
}
/*This Function gets arr and FREE its memory*/
void freeShortHistory(char * shortHistory[])
{
	for (int i = 0; i < N; i++)
	{
		FREE(shortHistory[i]);
	}
}
/*This Function takes 2 str arguments and returns the index of first appearence of str2 in str1*/
int foundStr(char * str1, char* str2)
{
	int count = 0;
	int i = 0, j = 0;
	while (str1[i] != '\0')
	{
		while (str1[i] == str2[j])
		{
			count++;
			i++;
			j++;
			if (str2[j] == '\0')
				return (i - (int)strlen(str2));
		}
		if (j != 0)
			i = i - count;
		j = 0;
		i++;
	}
	return -1;
}
/*This Function gets 2 arguments of str and command and switch every str1 in command to str2*/
char *  updateCommand(char * oldCommand, char * newCommand, char * input)
{
	int last_found;
	char * newInput = NULL;
	int inputLength = (int)strlen(input);
	last_found = foundStr(input, oldCommand);
	while (last_found != -1)
	{
		int i = 0, j = 0, k = 0, lst_found = 0;
		int startLength = 0, newCommandLength,oldCommandLength, endLength = 0;
		newCommandLength = (int)strlen(newCommand);
		oldCommandLength = (int)strlen(oldCommand);
		char * start = (char *)calloc((last_found + 1), sizeof(char));
		for (i = 0; i < last_found; i++)
			start[i] = input[i];
		start[i] = '\0';
		startLength = (int)strlen(start);
		char * end = (char *)calloc((inputLength - startLength - oldCommandLength + 1), sizeof(char));
		for (i = i+ oldCommandLength, j = 0; i < inputLength; i++, j++)
			end[j] = input[i];
		end[j] = '\0';
		endLength = (int)strlen(end);
		newInput = (char *)calloc((startLength + newCommandLength + endLength + 1), sizeof(char));
		for (i = 0; i < startLength; i++)
			newInput[k++] = start[i];
		for (i = 0; i < newCommandLength; i++)
			newInput[k++] = newCommand[i];
		for (i = 0; i < endLength; i++)
			newInput[k++] = end[i];
		newInput[k] = '\0';
		lst_found = foundStr(newInput + startLength + newCommandLength - 1, oldCommand);
		FREE(start);
		FREE(end);
		if (lst_found == -1)
			break;
		else
		{
			input = (char *)realloc(input, (strlen(newInput) + 1) * sizeof(char));
			strcpy(input, newInput);
			FREE(newInput);
			newInput = NULL;
			last_found += lst_found;
		}
	}
	if (newInput == NULL)
		return input;
	return newInput;
}