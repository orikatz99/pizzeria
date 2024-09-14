#ifndef __CUSTOMER__
#define __CUSTOMER__
#include "General.h"


typedef struct
{
	char* name;
	char* id;
	int points;
}Customer;

void		 initCustomer(Customer* customer);
void		 getName(Customer* customer);
void		 getId(Customer* customer);
int			 checkId(char* id);
int			 isIdUniqe(Customer* membersArr, int memberCount, char* id);
void		 printCustomer(const Customer* customer);
void	     printCustomerGeneral(const void* element);
void		 freeCustomer(Customer* customer);
void		 freeCustomerGeneral(void* element);
int			 writeCustomerToTextFile(FILE* fp, const Customer* customer);
int			 readCustomerFromTextFile(FILE* fp, Customer* customer);


#endif