#include "Set.h"

/*This Function recognize input values and deliver them to create new appartment func*/
void addNavigation(List *apartments, char * details)
{
	char *andress, *date;
	Date entrance;
	int price, rooms;
	details++; // to avoid from ""
	details = strtok(details, "\"");
	andress = details;
	details = strtok(NULL, " ");
	price = atoi(details);
	details = strtok(NULL, " ");
	rooms = atoi(details);
	details = details + 2;
	date = copyDate(details);
	entrance = stod(date);
	FREE(date); // FREE memory after use
	addApartment(apartments, andress, price, rooms, entrance);
}

/*This Function creates new apartment and insert it to list*/
void addApartment(List *apartments, char* andress, int price, short int rooms, Date entrance)
{
	Apartment data;
	data.code = ++codeApartment;
	data.andress = (char *)calloc((strlen(andress)+1),sizeof(char));
	strcpy(data.andress, andress);
	data.price = price;
	data.rooms = rooms;
	data.entrance = entrance;
	data.entryDate = getCurrentTime(); 
	insertDataToEndList(apartments, data);
}
/*This Function purchase appartment and delete it from list*/
void buyApartment(List *apartments, short int code)
{
	ListNode *deleteApp = apartments->head;
	ListNode *temp = NULL;
	/*check the first cell on the list */
	if (deleteApp->appData.code == code)
	{
		deleteHead(apartments);
		return;
	}
	while (deleteApp->next != NULL)
	{
		if (deleteApp->next->appData.code == code)
		{
			deleteNode(deleteApp);
			break;
		}
		deleteApp = deleteApp->next;
	}
}
/*This Function delete appartments from list by date input*/
void deleteApartment(List *apartments, int numDates)
{
	ListNode *deleteApp = apartments->head;
	ListNode *temp = NULL;
	Date firstDate, lastDate;
	firstDate = getSpecificTime(numDates);
	lastDate = getCurrentTime();
	while (deleteApp->next != NULL)
	{
		if (isBetweenDates(firstDate, (deleteApp->appData.entryDate), lastDate))
		{
			deleteNode(deleteApp);
		}
		else
			deleteApp = deleteApp->next;
	}

	/*check the first cell on the list */
	deleteApp = apartments->head;
	if (isBetweenDates(firstDate, (deleteApp->appData.entryDate), lastDate))
	{
		deleteHead(apartments);
	}
}
/*This Function copy str of date from input into another str that represents date */
char * copyDate(char * str)
{
	int i = 0,j=0;
	char * date = (char *)calloc(9, sizeof(char));
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			date[j++] = str[i];
		if (j == 4)
		{
			date[j++] = '2';
			date[j++] = '0';
		}
		i++;
	}
	date[j] = '\0';
	return date;
}