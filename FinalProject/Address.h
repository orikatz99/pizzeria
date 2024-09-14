#ifndef __ADDRESS__
#define __ADDRESS__

#include "General.h"

typedef struct
{
	char* city;
	char* street;
	int	    houseNum;
}Address;

int	initAdress(Address* address);
void printAddress(const Address* address);
void freeAddress(Address* address);
int  writeAddressToTextFile(FILE* fp, const Address* address);
int	 readAddressFromTextFile(FILE* fp, Address* address);



#endif  