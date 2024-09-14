#ifndef __MYDATE__
#define __MYDATE__

#include "General.h"

#define MIN_YEAR 2024

typedef struct
{
	int			day;
	int			month;
	int			year;
}Date;

void getCorrectDate(Date* pDate);
int	 checkDate(char* date, Date* pDate);
void printDate(const Date* pDate);
int  writeDateToTextFile(FILE* fp, const Date* pDate);
int  readDateFromTextFile(FILE* fp, Date* pDate);


#endif  