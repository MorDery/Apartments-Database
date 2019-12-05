#include "Header.h"

/*This Function returns the current date*/
Date getCurrentTime()
{
	Date myCurrentTime;
	time_t currentfulltime= time(&currentfulltime);
	struct tm * currentspecifictime = localtime(&currentfulltime);
	myCurrentTime.day = (short int)(currentspecifictime->tm_mday);
	myCurrentTime.month = (short int)(currentspecifictime->tm_mon + 1);
	myCurrentTime.year = (short int)(currentspecifictime->tm_year + 1900);
	return myCurrentTime;
}

/*This Function gets date that represented in string and returns it in Date type*/
Date stod(char * str)
{
	Date newDate;
	char day[3] = { str[0],str[1] ,'\0'};
	char month[3] = { str[2] , str[3] ,'\0'};
	char year[5] = { str[4],str[5],str[6],str[7], '\0'};
	newDate.day = (short int)atoi(day);
	newDate.month = (short int)atoi(month);
	newDate.year = (short int)atoi(year);
	return newDate;
}
/*This Function gets date that represented by Date type and returns it in string*/
char * dtos(Date date)
{
	char * newDate = (char *)malloc(10 * sizeof(char));
	newDate[0] = (char)(date.day / 10 + '0');
	newDate[1] = (char)(date.day % 10 + '0');
	newDate[2] = '.';
	newDate[3] = (char)(date.month / 10 + '0');
	newDate[4] = (char)(date.month % 10 + '0');
	newDate[5] = '.';
	int year = date.year;
	for (int i = 9; i >= 6; i--)
	{
		newDate[i] = (char)(year % 10 + '0');
		year /= 10;
	}
	newDate[10] = '\0';
	return newDate;
}
/*This Function gets amount of days and returns what was the date before this days*/
Date getSpecificTime(int daysBefore)
{
	Date timeBefore;
	time_t currentFullTime = time(&currentFullTime);
	currentFullTime -= (1440 * daysBefore);
	struct tm * currentSpecificTime = localtime(&currentFullTime);
	timeBefore.day = (short int)currentSpecificTime->tm_mday-daysBefore;
	timeBefore.month = (short int)currentSpecificTime->tm_mon + 1;
	timeBefore.year = (short int)currentSpecificTime->tm_year + 1900;
	return timeBefore;
}
/*This Function gets two dates and returns which bigger by 1,-1,0 values*/
int dateCompare(Date date1, Date date2)
{
	if (date1.year - date2.year > 0)
		return 1;
	if (date1.year - date2.year < 0)
		return -1;
	if (date1.year - date2.year == 0)
	{
		if (date1.month - date2.month > 0)
			return 1;
		if (date1.month - date2.month < 0)
			return -1;
		if (date1.month - date2.month == 0)
		{
			if (date1.day - date2.day > 0)
				return 1;
			if (date1.day - date2.day < 0)
				return -1;
			if (date1.day - date2.day == 0)
				return 0;
		}
	}
	return 1;
}
/*This Function gets three dates and returns if the middle one is between them*/
bool isBetweenDates(Date prev, Date check, Date curr)
{
	return (dateCompare(check, prev) > -1 && dateCompare(curr, check) > -1);
}