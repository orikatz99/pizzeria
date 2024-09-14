#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
#include "Customer.h"

void initCustomer(Customer* customer)
{
	getName(customer);
	getId(customer);
	customer->points = 10;//The customer initially has 10 points, of course he can only use them if he is a club member
}

void getName(Customer* customer)
{
	customer->name = getStrExactName("Enter name");
	fixString(customer->name);
}

void getId(Customer* customer)
{
	int ok = 0;

	do
	{
		customer->id = getStrExactName("Enter your Id number (9 numbers only)\n");
		ok = checkId(customer->id);
	} while (!ok);

}

int checkId(char* id)
{
	if (strlen(id) != 9)
		return FALSE;
	else
	{
		for (int i = 0; i < MAX_ID; i++)
		{
			if (!(isdigit(id[i])))
				return FALSE;
		}
	}

	return TRUE;
}

int isIdUniqe(Customer* membersArr, int memberCount, char* id)
{
	for (int i = 0; i < memberCount; i++)
	{
		if (isSameStr(membersArr[i].id, id))
			return i;
	}
	return -1;
}

void printCustomer(const Customer* customer)
{
	printf("Customer: name:%s, id: %s\n", customer->name, customer->id);

}

void	printCustomerGeneral(const void* element)
{
	Customer* customer = (Customer*)element;
	printCustomer(customer);
}

void freeCustomer(Customer* customer)
{
	free(customer->name);
	free(customer->id);
}

void freeCustomerGeneral(void* element)
{
	Customer* customer = (Customer*)element;
	freeCustomer(customer);
}

int  writeCustomerToTextFile(FILE* fp, const Customer* customer)
{
	return (fprintf(fp, "%s\n%s\n%d\n", customer->name, customer->id, customer->points) >= 0);

}

int	readCustomerFromTextFile(FILE* fp, Customer* customer)
{
	char customerName[MAX_STR_LEN] = { 0 };
	char id[MAX_STR_LEN] = { 0 };

	myGets(customerName, MAX_STR_LEN, fp);
	myGets(id, MAX_STR_LEN, fp);

	customer->name = strdup(customerName);
	customer->id = strdup(id);

	if (!customer->name || !customer->id)
		return 0;

	if (fscanf(fp, "%d", &customer->points) != 1)
		return 0;

	return 1;
}