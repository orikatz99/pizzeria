#include <stdio.h>
#include "Pizzeria.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h> 
#include <stdlib.h>
#include "Pizzeria.h"


void initPizzeria(Pizzeria* pizzeria)
{
	getNamePizzeria(pizzeria);
	initAdress(&pizzeria->address);
	initMenu(&pizzeria->menu.pizzaList);
	initMemberManager(&pizzeria->membersArr);
	initCouponsArr(&pizzeria->allCoupons);
	pizzeria->orders = NULL;
	pizzeria->numOfOrders = 0;

}

void getNamePizzeria(Pizzeria* pizzeria)
{
	pizzeria->name = getStrExactName("Enter name of pizzeria\n");
	fixString(pizzeria->name);
}

eOrderSortType getOrderType()
{
	int option;
	do {
		for (int i = 1; i < eNofSortType; i++)
			printf("Enter %d for %s\n", i, sortStr[i]);
		printf("\n");
		scanf("%d", &option);
	} while (option < 0 || option >= eNofSortType);
	getchar();
	return (eOrderSortType)option;
}

void sortOrders(Pizzeria* pizzeria)
{
	printf("\nBase on what field do you want to sort?\n");
	pizzeria->typeSort = getOrderType();
	if (pizzeria->typeSort == eSortPrice)
		qsort(pizzeria->orders, pizzeria->numOfOrders, sizeof(Order), compareOrdersByPrice);
	else if (pizzeria->typeSort == eSortDate)
		qsort(pizzeria->orders, pizzeria->numOfOrders, sizeof(Order), compareOrdersByDate);
	else if (pizzeria->typeSort == eSortName)
		qsort(pizzeria->orders, pizzeria->numOfOrders, sizeof(Order), compareOrdersByName);
}

int	compareOrdersByPrice(const void* order1, const void* order2)
{
	const Order* p1 = (const Order*)order1;
	const Order* p2 = (const Order*)order2;
	return p1->priceToPay - p2->priceToPay;

}

int	compareOrdersByDate(const void* order1, const void* order2)
{
	const Order* p1 = (const Order*)order1;
	const Order* p2 = (const Order*)order2;

	// Compare years
	if (p1->date.year != p2->date.year) {
		return p1->date.year - p2->date.year;
	}

	// If years are equal, compare months
	if (p1->date.month != p2->date.month) {
		return p1->date.month - p2->date.month;
	}

	// If months are equal, compare days
	return p1->date.day - p2->date.day;
}

int	compareOrdersByName(const void* order1, const void* order2)
{
	const Order* p1 = (const Order*)order1;
	const Order* p2 = (const Order*)order2;
	return strcmp(p1->customer.name, p2->customer.name);
}

void searchByPrice(const Pizzeria* pizzeria)
{
	Order temp;
	printf("Price: ");
	scanf("%lf", &temp.priceToPay);
	Order* pFound = (Order*)bsearch(&temp, pizzeria->orders, pizzeria->numOfOrders, sizeof(Order), compareOrdersByPrice);
	if (pFound)
	{
		printf("Order found, ");
		printOrder(pFound);
	}
	else
		printf("Order was not found\n");
}

void searchByDate(const Pizzeria* pizzeria)
{
	Order temp;
	getCorrectDate(&temp.date);
	Order* pFound = (Order*)bsearch(&temp, pizzeria->orders, pizzeria->numOfOrders, sizeof(Order), compareOrdersByDate);
	if (pFound)
	{
		printf("Order found, ");
		printOrder(pFound);
	}
	else
		printf("Order was not found\n");
}


void searchByName(const Pizzeria* pizzeria)
{
	Order temp;
	getName(&temp.customer);
	Order* pFound = (Order*)bsearch(&temp, pizzeria->orders, pizzeria->numOfOrders, sizeof(Order), compareOrdersByName);
	if (pFound)
	{
		printf("Order found, ");
		printOrder(pFound);
	}
	else
		printf("Order was not found\n");


}

void findOrder(const Pizzeria* pizzeria)
{
	if (pizzeria->typeSort == eSortPrice)
	{
		searchByPrice(pizzeria);
	}
	else if (pizzeria->typeSort == eSortDate)
	{
		searchByDate(pizzeria);
	}
	else if (pizzeria->typeSort == eSortName)
	{
		searchByName(pizzeria);
	}
	else //Un sorted
		printf("The search cannot be performed, array not sorted\n");
}

int	addOrder(Pizzeria* pizzeria)
{
	pizzeria->orders = (Order*)realloc(pizzeria->orders, (pizzeria->numOfOrders + 1) * sizeof(Order));
	if (!pizzeria->orders)
		return 0;
	initOrder(&pizzeria->orders[pizzeria->numOfOrders], &pizzeria->allCoupons, &pizzeria->membersArr, &pizzeria->menu);
	pizzeria->numOfOrders++;
	return 1;
}

void printOrdersArr(const Order* ordersArr, int size)
{
	generalArrayFunction(ordersArr, size, sizeof(*ordersArr), printOrderGeneral);
}

void freeOrders(Order* arr, int size)
{
	generalArrayFunction(arr, size, sizeof(*arr), freeOrderGeneral);
}

void printPizzeria(const Pizzeria* pizzeria)
{
	printf("\n\nWelcome to %s!!!\n\n", pizzeria->name);
	printAddress(&pizzeria->address);
	printf("\n");
	printMenu(&pizzeria->menu);
	printf("\n");
	printMembersArr(pizzeria->membersArr.membersArr, pizzeria->membersArr.membersCount);
	printf("\n");
	printAllCoupons(pizzeria->allCoupons.arrCoupons, pizzeria->allCoupons.numOfCoupons);
	printf("\n\n%s currently have %d orders: \n\n", pizzeria->name, pizzeria->numOfOrders);
	printOrdersArr(pizzeria->orders, pizzeria->numOfOrders);

}

void freePizzeria(Pizzeria* pizzeria)
{
	freeAllCouponsArr(pizzeria->allCoupons.arrCoupons, pizzeria->allCoupons.numOfCoupons);
	freePizzaList(&pizzeria->menu.pizzaList);
	freeMemberManager(pizzeria->membersArr.membersArr, pizzeria->membersArr.membersCount);
	freeOrders(pizzeria->orders, pizzeria->numOfOrders);
	freeAddress(&pizzeria->address);
	free(pizzeria->name);
}

int writeNameTextFile(FILE* fp, const Pizzeria* pizzeria)
{
	return (fprintf(fp, "%s\n", pizzeria->name) >= 0);

}

int	readNameTextFile(FILE* fp, Pizzeria* pizzeria)
{
	char name[MAX_STR_LEN] = { 0 };
	myGets(name, MAX_STR_LEN, fp);
	pizzeria->name = strdup((name));

	if (!pizzeria->name)
		return 0;

	return 1;
}

int WriteOrdersArrToTextFile(FILE* fp, const Order* ordersArr, int count)
{
	if (fprintf(fp, "%d\n", count) < 0)
		return 0;

	for (int i = 0; i < count; i++)
	{
		if (!writeOrderToTextFile(fp, &ordersArr[i]))
			return 0;

	}

	return 1;
}

Order* readOrdersArrFromTextFile(FILE* fp, int* pCount)
{
	Order* ordersArr;

	if (fscanf(fp, "%d", pCount) != 1)
		return NULL;

	ordersArr = (Order*)malloc(*pCount * sizeof(Order));

	if (!ordersArr)
		return NULL;

	for (int i = 0; i < *pCount; i++)
		if (!readOrderFromTextFile(fp, &ordersArr[i]))
		{
			freeOrders(ordersArr, *pCount);
			return NULL;
		}
	return ordersArr;
}

int		savePizzeriaToTextFile(const Pizzeria* pizzeria, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "w");

	CHECK_RETURN_FALSE(fp);


	if (!writeNameTextFile(fp, pizzeria))
	{
		CLOSE_RETURN_FALSE(fp);

	}

	if (!writeAddressToTextFile(fp, &pizzeria->address))
	{
		CLOSE_RETURN_FALSE(fp);

	}

	if (!writePizzaListToTextFile(fp, &pizzeria->menu.pizzaList))
	{
		CLOSE_RETURN_FALSE(fp);

	}

	if (!writeMembersArrToTextFile(fp, pizzeria->membersArr.membersArr, pizzeria->membersArr.membersCount))
	{
		CLOSE_RETURN_FALSE(fp);

	}

	if (!writeCouponsArrToTextFile(fp, pizzeria->allCoupons.arrCoupons, pizzeria->allCoupons.numOfCoupons))
	{
		CLOSE_RETURN_FALSE(fp);

	}

	if (!WriteOrdersArrToTextFile(fp, pizzeria->orders, pizzeria->numOfOrders))
	{
		CLOSE_RETURN_FALSE(fp);

	}

	fclose(fp);
	return 1;

}

int		initPizzeriaFromTextFile(Pizzeria* pizzeria, const char* fileName)
{
	FILE* fp = fopen(fileName, "r");

	CHECK_RETURN_FALSE(fp);

	if (!readNameTextFile(fp, pizzeria))
	{
		freePizzeria(pizzeria);
		CLOSE_RETURN_FALSE(fp);

	}
	if (!readAddressFromTextFile(fp, &pizzeria->address))
	{
		freePizzeria(pizzeria);
		CLOSE_RETURN_FALSE(fp);

	}

	if (!L_init(&pizzeria->menu.pizzaList))
	{
		printf("memory error\n");
		return 0;
	}

	if (!readPizzaListFromTextFile(fp, &pizzeria->menu.pizzaList))
	{
		freePizzeria(pizzeria);
		CLOSE_RETURN_FALSE(fp);

	}

	pizzeria->membersArr.membersArr = readMembersArrFromTextFile(fp, &pizzeria->membersArr.membersCount);

	if (!pizzeria->membersArr.membersArr)
	{
		freePizzeria(pizzeria);
		CLOSE_RETURN_FALSE(fp);

	}

	pizzeria->allCoupons.arrCoupons = readCouponsArrFromTextFile(fp, &pizzeria->allCoupons.numOfCoupons);

	if (!pizzeria->allCoupons.arrCoupons)
	{
		freePizzeria(pizzeria);
		CLOSE_RETURN_FALSE(fp);

	}
	pizzeria->orders = readOrdersArrFromTextFile(fp, &pizzeria->numOfOrders);

	if (!pizzeria->orders)
	{
		freePizzeria(pizzeria);
		CLOSE_RETURN_FALSE(fp);

	}

	pizzeria->typeSort = 0;
	return 1;
}
