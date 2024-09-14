#ifndef __MYTIME__
#define __MYTIME__
#include "General.h"

typedef unsigned char BYTE;

typedef struct
{
	int			hour;
	int			minute;
}Time;

void getCorrectTime(Time* pTime);
int	 checkTime(char* time, Time* pTime);
void printTime(const Time* pTime);
int  writeTimeToTextFile(FILE* fp, const Time* pTime);
int  readTimeFromTextFile(FILE* fp, Time* pTime);
int  saveTimeToBFile(FILE* fp, const Time* pTime);
int  readTimeFromFile(FILE* fp, Time* pTime);

#endif
