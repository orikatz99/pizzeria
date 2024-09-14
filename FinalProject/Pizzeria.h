#ifndef __PIZZERIA__
#define __PIZZERIA__
#include "Order.h"
#include "Menu.h"
#include "AllCoupons.h"
#include "MemberManager.h"




typedef enum {
	eNoSort, eSortPrice, eSortDate, eSortName, eNofSortType
} eOrderSortType;

static const char* sortStr[eNofSortType]
= { "not sorted", "Price", "Date", "Name" };

typedef struct
{
	AllCoupons allCoupons;
	Menu menu;
	MemberManager membersArr;
	int numOfMembers;
	Order* orders;
	int numOfOrders;
	char* name;
	Address address;
	eOrderSortType	typeSort;

}Pizzeria;

void			initPizzeria(Pizzeria* pizzeria);
void			getNamePizzeria(Pizzeria* pizzeria);
eOrderSortType	getOrderType();
void			sortOrders(Pizzeria* pizzeria);
int				compareOrdersByPrice(const void* order1, const void* order2);
int				compareOrdersByDate(const void* order1, const void* order2);
int				compareOrdersByName(const void* order1, const void* order2);
void			searchByPrice(const Pizzeria* pizzeria);
void			searchByDate(const Pizzeria* pizzeria);
void			searchByName(const Pizzeria* pizzeria);
void			findOrder(const Pizzeria* pizzeria);
int				addOrder(Pizzeria* pizzeria);
void			printOrdersArr(const Order* ordersArr, int ordersCount);
void			printPizzeria(const Pizzeria* pizzeria);
void			freeOrders(Order* arr, int size);
void			freePizzeria(Pizzeria* pizzeria);
int				writeNameTextFile(FILE* fp, const Pizzeria* pizzeria);
int				readNameTextFile(FILE* fp, Pizzeria* pizzeria);
int				WriteOrdersArrToTextFile(FILE* fp, const Order* ordersArr, int count);
Order* readOrdersArrFromTextFile(FILE* fp, int* pCount);
int				savePizzeriaToTextFile(const Pizzeria* pizzeria, const char* fileName);
int				initPizzeriaFromTextFile(Pizzeria* pizzeria, const char* fileName);


#endif







