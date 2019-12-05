#pragma once
#include "Header.h"

//prototypes for Get functions
void getNavigation(char * command, Apartment * apartments, int size);
void printMaximumNumRooms(int maxRooms, Apartment * apartments, int size);
void printMinimumNumRooms(int minRooms, Apartment * apartments, int size);
void printMaximumPrice(int maxPrice, Apartment * apartments, int size);
void printPerDate(Date date, Apartment * apartments, int size);
void printEnter(Date date, Apartment * apartments, int size);
void printChosen(Apartment * arr, int size);
void bubbleSort(Apartment * arr, int size, int ascend);

