#pragma once
#include "Header.h"

//prototypes for Set functions
void addApartment(List *apartments, char* andress, int price, short int rooms, Date entrance);
void buyApartment(List *apartments, short int codeApparment);
void deleteApartment(List *apartments, int numDates);
void addNavigation(List *apartments, char * details);
char * copyDate(char * str);


