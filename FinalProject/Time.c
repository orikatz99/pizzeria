#include <stdio.h>
#include <string.h>
#include "Time.h"

#define SPECIAL_TAV ':'

void getCorrectTime(Time* pTime)
{
	char time[MAX_STR_LEN];
	int ok = 1;
	printf("\nThe pizzeria is open between the hours: 12:00-22:00\n");
	do {
		printf("Please enter the order time hh%cmm \t", SPECIAL_TAV);
		myGets(time, MAX_STR_LEN, stdin);
		ok = checkTime(time, pTime);
		if (!ok)
			printf("Error try again\n");
	} while (!ok);

}

int	 checkTime(char* time, Time* pTime)
{
	int hour, minute;

	if (strlen(time) != 5)
		return 0;
	if ((time[2] != SPECIAL_TAV))
		return 0;
	sscanf(time, "%d%*c%02d", &hour, &minute);
	if (hour < 12 || hour > 22)
		return 0;
	if (minute < 0 || minute > 59)
		return 0;
	if (hour == 22 && minute > 0)
		return 0;

	pTime->hour = hour;
	pTime->minute = minute;

	return 1;
}

void printTime(const Time* pTime)
{
	printf("Time of order: %d:%02d", pTime->hour, pTime->minute);
}

int writeTimeToTextFile(FILE* fp, const Time* pTime)
{
	return (fprintf(fp, "%d:%02d\n", pTime->hour, pTime->minute) >= 0);

}

int readTimeFromTextFile(FILE* fp, Time* pTime)
{
	return (fscanf(fp, "%d%*c%02d", &pTime->hour, &pTime->minute) == 2); //*c??

}

int saveTimeToBFile(FILE* fp, const Time* pTime)
{
	BYTE data[2];
	data[0] = ((pTime->hour - 12) << 4) | (pTime->minute >> 2);
	data[1] = (pTime->minute << 6);

	if (fwrite(data, sizeof(BYTE), 2, fp) != 2)
		return 0;
	return 1;
}

int readTimeFromFile(FILE* fp, Time* pTime)
{
	BYTE data[2];
	if (fread(data, sizeof(BYTE), 2, fp) != 2)
		return 0;

	pTime->hour = ((data[0] >> 4) & 0x0F) + 12;
	pTime->minute = ((data[0] & 0x0F) << 2) | (data[1] >> 6);

	return 1;
}