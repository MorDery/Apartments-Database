#include "Set.h"
#include "Get.h"
#include "Database.h"

/*This Function interprets commands and sends eachone to the right function*/
void commandSender(char* input, List *aparments)
{
	//we want to save the original input to be free after running commandSender
	char *cpyInput1 = (char *)calloc((strlen(input) + 1) , sizeof(char));
	char *cpyInput2 = (char *)calloc((strlen(input) + 1) , sizeof(char));
	strcpy(cpyInput1, input); //sends to manage functions
	strcpy(cpyInput2, input); //sends to addToShortHistory
	cpyInput1 = strtok(cpyInput1, " ");
	if (cpyInput1[0] == 'g')
	{
		int size=0;
		Apartment * apartments = copyToArray(*aparments, &size);
		getNavigation(strtok(NULL, "\n"), apartments, size);
		addToShortHistory(short_term_history, &long_term_history, cpyInput2);
		FREE(cpyInput2);
	}
	else if (cpyInput1[0] == 'a')
	{
		addNavigation(aparments, strtok(NULL, "\n"));
		addToShortHistory(short_term_history, &long_term_history, cpyInput2);
		FREE(cpyInput2);
	}
	else if (cpyInput1[0] == 'b')
	{
		buyApartment(aparments, atoi(strtok(NULL, "\n")));
		addToShortHistory(short_term_history, &long_term_history, cpyInput2);
		FREE(cpyInput2);
	}
	else if (cpyInput1[0] == 'd')
	{
		strtok(NULL, " ");
		deleteApartment(aparments, atoi(strtok(NULL, "\n")));
		addToShortHistory(short_term_history, &long_term_history, cpyInput2);
		FREE(cpyInput2);
	}
	else
	{
		reproduction(cpyInput2, short_term_history, &long_term_history, aparments);
		FREE(cpyInput2);
	}
		FREE(cpyInput1);
}

/*This Function copy Database of apartments to array - to change and print it in get functions* without touch the original Database*/
Apartment * copyToArray(List apartments, int * size)
{
	int i = 0, howMany = 0;
	ListNode * curr;
	howMany = count(apartments);
	Apartment * apArr = (Apartment *)malloc(howMany * sizeof(Apartment));
	for (curr = apartments.head; curr != NULL; curr = curr->next, i++)
	{
		apArr[i] = curr->appData;
	}
	*size = howMany;
	return apArr;
}

