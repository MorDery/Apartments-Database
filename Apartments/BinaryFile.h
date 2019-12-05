#pragma once
#define BFileName "apartments.bin"

typedef unsigned char Byte;
void makeBinaryFile(List apartments);
//get&set Bytes1
void updateBytes1(Byte bytes[], short int numRooms, short int day, short int month, short int year);
void set_numRooms(Byte bytes[], short int numRooms);
void set_entranceDay(Byte bytes[], short int day);
void set_entranceMonth(Byte bytes[], short int month);
void set_entranceYear(Byte bytes[], short int year);
short int get_numRooms(Byte bytes[]);
short int get_entranceDay(Byte bytes[]);
short int get_entranceMonth(Byte bytes[]);
short int get_entranceYear(Byte bytes[]);
//get&set Bytes2
void updateBytes2(Byte bytes[], short int day, short int month, short int year);
void set_entryDay(Byte bytes[], short int day);
void set_entryMonth(Byte bytes[], short int month);
void set_entryYear(Byte bytes[], short int year);
short int get_entryDay(Byte bytes[]);
short int get_entryMonth(Byte bytes[]);
short int get_entryYear(Byte bytes[]);
long getFileByte(FILE * file);
void getApartmentsFromFile(List * apartments);
void addApartmentFromBinary(long checkPoint, FILE * file, List * apartments);