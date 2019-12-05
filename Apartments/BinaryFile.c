#include "Header.h"
#include "Database.h"
#include "BinaryFile.h"
#include "Set.h"
#define TWOTHOUSAND 2000

//masks for Bytes1
Byte numRooms_mask = 0xF << 4;
Byte entranceDay1_mask = 0xF;
Byte entranceDay2_mask = 0x1 << 7;
Byte entranceMonth_mask = 0xF << 3;
Byte entranceYear1_mask = 0x7;
Byte entranceYear2_mask = 0xF << 4;
//masks for Bytes2
Byte entryDay_mask = 0xF8;
Byte entryMonth1_mask = 0x7;
Byte entryMonth2_mask = 0x1 << 7;
Byte entryYear_mask = 0x7F;

/*This shell Function gets apartments data from files*/
void getApartmentsFromFile(List * apartments)
{
	long checkPoint;
	FILE * File = fopen(BFileName, "rb");
	assert(File != NULL);
	rewind(File);
	long fileSize = getFileByte(File);
	fread(&codeApartment, sizeof(short int), 1, File);
	while (ftell(File) < fileSize)
	{
		checkPoint = ftell(File); //checkpoint of code apartment,andress length,andress and price.
		addApartmentFromBinary(checkPoint, File, apartments);
	}
	fclose(File);
}
/*This Function creates binary file that stores apartments data from last run*/
void makeBinaryFile(List apartments)
{
	FILE * newFile = fopen(BFileName, "wb");
	assert(newFile != NULL);
	ListNode * curr = apartments.head;
	rewind(newFile);
	fwrite(&codeApartment, sizeof(short int), 1, newFile); //save static code for next add
	while (curr != NULL)
	{
		Byte Bytes1[3] = { 0 };
		Byte Bytes2[2] = { 0 };
		fwrite(&(curr->appData.code), sizeof(short int), 1, newFile);
		short int andressLen = (short int)strlen(curr->appData.andress);
		fwrite(&andressLen, sizeof(short int), 1, newFile);
		fwrite(curr->appData.andress, sizeof(char), andressLen, newFile);
		fwrite(&curr->appData.price, sizeof(int), 1, newFile);

		updateBytes1(Bytes1, curr->appData.rooms, curr->appData.entrance.day,
			curr->appData.entrance.month, (curr->appData.entrance.year - TWOTHOUSAND));
		updateBytes2(Bytes2,curr->appData.entryDate.day, curr->appData.entryDate.month
			, (curr->appData.entryDate.year- TWOTHOUSAND));
		fwrite(Bytes1, sizeof(Byte), 3, newFile);
		fwrite(Bytes2, sizeof(Byte), 2, newFile);
		curr = curr->next;
	}
	fclose(newFile);
}

/*This shell Function gets apartment data from Bytes*/
void updateBytes2(Byte bytes[], short int day, short int month, short int year)
{
	set_entryDay(bytes, day);
	set_entryMonth(bytes, month);
	set_entryYear(bytes, year);
}
/*This shell Function gets apartment data from Bytes*/
void updateBytes1(Byte bytes[], short int numRooms, short int day, short int month, short int year)
{
	set_numRooms(bytes, numRooms);
	set_entranceDay(bytes, day);
	set_entranceMonth(bytes, month);
	set_entranceYear(bytes, year);
}
/*put data of apartment into Bytes*/
void set_numRooms(Byte bytes[], short int numRooms)
{
	Byte temp = 0;
	temp = ((Byte)numRooms << 4) & (numRooms_mask);
	bytes[0] = bytes[0] | temp;
}
/*put data of apartment into Bytes*/
void set_entranceDay(Byte bytes[], short int day)
{
	Byte day1 = 0;
	day1= ((Byte)day >> 1) & entranceDay1_mask;
	Byte day2 = 0;
	day2 =((Byte)day << 7) & entranceDay2_mask;
	bytes[0] = bytes[0] | day1;
	bytes[1] = bytes[1] | day2;
}
/*put data of apartment into Bytes*/
void set_entranceMonth(Byte bytes[], short int month)
{
	Byte bmonth = 0;
	bmonth = ((Byte)month << 3) & entranceMonth_mask;
	bytes[1] = bytes[1] | bmonth;
}
/*put data of apartment into Bytes*/
void set_entranceYear(Byte bytes[], short int year)
{
	Byte year1 = 0;
	year1 = ((Byte)year >> 4) & entranceYear1_mask;
	Byte year2 = 0;
	year2 = ((Byte)year << 4) & entranceYear2_mask;
	bytes[1] = bytes[1] | year1;
	bytes[2] = bytes[2] | year2;
}
/*put data of apartment into Bytes*/
void set_entryDay(Byte bytes[], short int day)
{
	Byte bday = 0;
	bday = ((Byte)day << 3) & entryDay_mask;
	bytes[0] = bytes[0] | bday;
}
/*put data of apartment into Bytes*/
void set_entryMonth(Byte bytes[], short int month)
{
	Byte month1 = 0;
	month1 = ((Byte)month >> 1) & entryMonth1_mask;
	Byte month2 = 0;
	month2 = ((Byte)month << 7) &  entryMonth2_mask;
	bytes[0] = bytes[0] | month1;
	bytes[1] = bytes[1] | month2;
}
/*put data of apartment into Bytes*/
void set_entryYear(Byte bytes[], short int year)
{
	Byte byear = 0;
	byear = ((Byte)year) & entryYear_mask;
	bytes[1] = bytes[1] | byear;
}
/*This Function returns size of file*/
long getFileByte(FILE * file)
{
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);
	return size;
}
/*get data of apartment from Bytes*/
short int get_numRooms(Byte bytes[])
{
	return ((bytes[0] & numRooms_mask) >> 4);
}
/*get data of apartment from Bytes*/
short int get_entranceDay(Byte bytes[])
{
	Byte day1 = (bytes[0] & entranceDay1_mask);
	Byte day2 = (bytes[1] & entranceDay2_mask) >> 7;
	Byte day = (day1 << 1) | day2;
	return day;
}
/*get data of apartment from Bytes*/
short int get_entranceMonth(Byte bytes[])
{
	return ((bytes[1] & entranceMonth_mask) >> 3);
}
/*get data of apartment from Bytes*/
short int get_entranceYear(Byte bytes[])
{
	Byte year1 = (bytes[1] & entranceYear1_mask);
	Byte year2 = (bytes[2] & entranceYear2_mask) >> 4;
	Byte year = (year1 << 4) | year2;
	return year;
}
/*get data of apartment from Bytes*/
short int get_entryDay(Byte bytes[])
{
	return ((bytes[0] & entryDay_mask) >> 3);
}
/*get data of apartment from Bytes*/
short int get_entryMonth(Byte bytes[])
{
	Byte month1 = (bytes[0] & entryMonth1_mask);
	Byte month2 = (bytes[1] & entryMonth2_mask) >> 7;
	Byte month = (month1 << 1) | month2;
	return month;
}
/*get data of apartment from Bytes*/
short int get_entryYear(Byte bytes[])
{
	return (bytes[1] & entryYear_mask);
}

/*This Function creates new apartment and insert it to list*/
void addApartmentFromBinary(long checkPoint , FILE * file , List * apartments)
{
	Apartment data;
	int andressLen=0;
	fread(&data.code, sizeof(short int), 1, file);
	fread(&andressLen, sizeof(short int), 1, file);
	data.andress = (char *)calloc((andressLen + 1), sizeof(char));
	fread(data.andress, sizeof(char), andressLen, file);
	fread(&data.price, sizeof(int), 1, file);
	Byte bytes1[3] = { 0 };
	fread(bytes1, sizeof(Byte), 3, file);
	data.rooms = get_numRooms(bytes1);
	data.entrance.day = get_entranceDay(bytes1);
	data.entrance.month = get_entranceMonth(bytes1);
	data.entrance.year = get_entranceYear(bytes1)+TWOTHOUSAND;
	Byte bytes2[2] = { 0 };
	fread(bytes2, sizeof(Byte), 2, file);
	data.entryDate.day = get_entryDay(bytes2);
	data.entryDate.month = get_entryMonth(bytes2);
	data.entryDate.year = get_entryYear(bytes2)+TWOTHOUSAND;
	insertDataToEndList(apartments, data);
}
