#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Address.h"

int	initAdress(Address* address)
{
	address->city = getStrExactName("Enter the city name\n");
	if (!address->city)
		return 0;
	fixString(address->city);

	address->street = getStrExactName("Enter the street name\n");
	if (!address->street)
		return 0;
	fixString(address->street);

	printf("Enter the house number (between 1 and 100)\n");
	scanf("%d", &address->houseNum);
	while (address->houseNum < 1 || address->houseNum>100)
	{
		printf("invalid address\n");
		scanf("%d", &address->houseNum);
	}
	return 1;
}

void printAddress(const Address* address)
{
	printf("Address: %s %d, %s\n", address->street, address->houseNum, address->city);
}

void freeAddress(Address* address)
{
	free(address->city);
	free(address->street);
}

int writeAddressToTextFile(FILE* fp, const Address* address)
{
	return (fprintf(fp, "%s\n%d\n%s\n", address->street, address->houseNum, address->city) >= 0);
}

int	readAddressFromTextFile(FILE* fp, Address* address)
{
	char street[MAX_STR_LEN] = { 0 };
	char city[MAX_STR_LEN] = { 0 };

	myGets(street, MAX_STR_LEN, fp);
	if (fscanf(fp, "%d", &address->houseNum) != 1)
		return 0;
	myGets(city, MAX_STR_LEN, fp);

	address->street = strdup(street);
	address->city = strdup(city);

	if (!address->street || !address->city)
		return 0;

	return 1;
}