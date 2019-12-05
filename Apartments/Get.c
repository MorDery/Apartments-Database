#include "Get.h"
void mergeSort(Apartment * arr, int size, int ascend);
void sortedMerge(Apartment * arr1, int size1, Apartment * arr2, int size2, Apartment* res, int ascend);

//instance for command:
//get-an-apt –MinimumNumRooms 3 –MaximumNumRooms 5 –MaximumPrice 1750000 -sr
//get-an-apt |–Date 01052017
//get-an-apt |–MaximumNumRooms 5 -sr
//get-an-apt |–Enter <x>
/*This Function gets command input and sorting the right appartment to print*/
void getNavigation(char * command, Apartment * apartments, int size)
{
	char delimeter[3] = " \n";
	if (command == NULL)
		return;
	if (size == 0)
	{
		printf("No apartments");
		return;
	}
	command = strtok(command, delimeter);
	while (command != NULL)
	{
		if (strcmp(command, "-sr") == 0)
			mergeSort(apartments, size, -1);
		else if (strcmp(command, "-s") == 0)
			mergeSort(apartments, size, 1);
		else if (strcmp(command, "-MaximumNumRooms") == 0)
			printMaximumNumRooms(atoi(strtok(NULL, delimeter)), apartments, size);
		else if (strcmp(command, "-MinimumNumRooms") == 0)
			printMinimumNumRooms(atoi(strtok(NULL, delimeter)), apartments, size);
		else if (strcmp(command, "-MaximumPrice") == 0)
			printMaximumPrice(atoi(strtok(NULL, delimeter)), apartments, size);
		else if (strcmp(command, "-Date") == 0)
			printPerDate(stod(strtok(NULL, delimeter)), apartments, size);
		else if (strcmp(command, "-Enter") == 0)
			printEnter(getSpecificTime(atoi(strtok(NULL, delimeter))), apartments, size);
		else
		{
			printf("something wrong with input");
			exit(1);
		}
		command = strtok(NULL, delimeter);
	}
	printChosen(apartments, size);
	FREE(apartments);
	return;
}
/*This Function marks unwanted apartments to print*/
void printMaximumNumRooms(int maxRooms, Apartment * apartments, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (apartments[i].rooms > maxRooms)
			apartments[i].code = 0; //This tells us to ignore this appartment from print
	}
}
/*This Function marks unwanted apartments to print*/
void printMinimumNumRooms(int minRooms, Apartment * apartments, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (apartments[i].rooms < minRooms)
			apartments[i].code = 0; //This tells us to ignore this appartment from print
	}
}
/*This Function marks unwanted apartments to print*/
void printMaximumPrice(int maxPrice, Apartment * apartments, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (apartments[i].price > maxPrice)
			apartments[i].code = 0; //This tells us to ignore this appartment from print
	}
}
/*This Function marks unwanted apartments to print*/
void printPerDate(Date date, Apartment * apartments, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (dateCompare(apartments[i].entrance, date) == 1)
			apartments[i].code = 0; //This tells us to ignore this appartment from print
	}
}
/*This Function marks unwanted apartments to print*/
void printEnter(Date date, Apartment * apartments, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (dateCompare(apartments[i].entryDate, date) == 1)
			apartments[i].code = 0; //This tells us to ignore this appartment from print
	}
}
/*This Function prints the right apartments by the requirments*/
void printChosen(Apartment * arr, int size)
{
	/* Output signeture
	Apt details:
	Code: 4
	Address: Gordon 85 Holon
	Number of rooms: 3
	Price: 1500000
	Entry date: 15.6.2017
	Database entry date: 29.4.2018
	*/
	for (int i = 0; i < size; i++)
	{
		if (arr[i].code != 0)
			printf("Apt details:\nCode: %d\nAddress: %s\nNumber of rooms: %d\nPrice: %d\nEntry date: %s\nDatabase entry date: %s\n",
				arr[i].code, arr[i].andress, arr[i].rooms, arr[i].price, dtos(arr[i].entrance), dtos(arr[i].entryDate));
	}

}

/* This Function does mergeSort by inputs :ascentSort = 1 , descendSort = -1 */
void mergeSort(Apartment * arr, int size, int ascend)
{
	int  i;
	Apartment * temp;
	if (size <= 1)
		return;
	else
	{
		mergeSort(arr, size / 2, ascend);
		mergeSort(arr + size / 2, size - size / 2, ascend);
		temp = (Apartment *)calloc(size, sizeof(Apartment));
		sortedMerge(arr, size / 2, arr + size / 2, size - size / 2, temp, ascend);
		for (i = 0; i < size; i++)
		{
			arr[i] = temp[i];
		}
		FREE(temp);
	}
}
/*This Function gets two arrays and sort them by ascend value*/
void sortedMerge(Apartment * arr1, int size1, Apartment * arr2, int size2, Apartment* res,int ascend)
{
	int read1 = 0, read2 = 0, write = 0;
	while ((read1 < size1) && (read2 < size2))
	{
		if (ascend == 1) //ascentSort
		{
			if (arr1[read1].price <= arr2[read2].price)
			{
				res[write] = arr1[read1];
				read1++;
			}
			else 
			{
				res[write] = arr2[read2];
				read2++;
			}
		}
		else //descendSort
		{
			if (arr1[read1].price >= arr2[read2].price)
			{
				res[write] = arr1[read1];
				read1++;
			}
			else
			{
				res[write] = arr2[read2];
				read2++;
			}
		}
		write++;
	}
	while (read1 < size1)  
	{
		res[write] = arr1[read1];
		read1++;
		write++;
	}
	while (read2 < size2)
	{
		res[write] = arr2[read2];
		read2++;
		write++;
	}
}
