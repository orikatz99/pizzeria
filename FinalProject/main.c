#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "main.h"
#include "Pizzeria.h"
#include "General.h"
#include "PizzeriaBinFile.h"



int main()
{
	Pizzeria		pizzeria;

	int choiceFile = getChoiceFile();

	if (choiceFile)
	{
		if (!initPizzeriaFromTextFile(&pizzeria, PIZZERIA_TXTFILE_NAME_SRC))
		{
			PRINT(Error init from text file);
			return 0;
		}
	}
	else
	{
		if (!initPizzeriaFromFile(&pizzeria, PIZZERIA_BINFILE_NAME_SRC))
		{
			PRINT(Error init from binary file);
			return 0;
		}

	}

	printPizzeria(&pizzeria);


	int option;
	int stop = 0;


	do
	{
		option = menu();
		switch (option)
		{
		case eAddCoupon:
			if (!addCoupon(&pizzeria.allCoupons))
				PRINT(Error adding coupon);
			break;

		case eAddMember:
			if (!addMember(&pizzeria.membersArr))
				PRINT(Error adding member);
			break;

		case eAddPizza:
			if (!addPizza(&pizzeria.menu.pizzaList))
				PRINT(Error adding pizza);
			break;

		case eAddOrder:
			if (!addOrder(&pizzeria))
				PRINT(Error adding order);
			break;

		case ePrintPizzeria:
			printPizzeria(&pizzeria);
			break;

		case ePrintAllCoupons:
			printAllCoupons(pizzeria.allCoupons.arrCoupons, pizzeria.allCoupons.numOfCoupons);
			break;

		case ePrintAllMembers:
			printMembersArr(pizzeria.membersArr.membersArr, pizzeria.membersArr.membersCount);
			break;

		case ePrintMenu:
			printMenu(&pizzeria.menu.pizzaList);
			break;

		case ePrintAllOrders:
			printOrdersArr(pizzeria.orders, pizzeria.numOfOrders);
			break;

		case eSortOrder:
			sortOrders(&pizzeria);
			break;

		case eFindOrder:
			findOrder(&pizzeria);
			break;

		case EXIT:
			PRINT(Bye bye);
			stop = 1;
			break;

		default:
			PRINT(Wrong option);
			break;
		}
	} while (!stop);

	if (!savePizzeriaToFile(&pizzeria, PIZZERIA_BINFILE_NAME_DST))
	{
		PRINT(Error saving pizzeria data to binary file);
		return 0;
	}

	if (!savePizzeriaToTextFile(&pizzeria, PIZZERIA_TXTFILE_NAME_DST))
	{
		PRINT(Error saving pizzeria data to text file);
		return 0;
	}

	freePizzeria(&pizzeria);

	return 1;
}


int getChoiceFile()
{
	int choice;

	do {
		printf("Hello!\n");
		printf("Press 0 to load the system from a binary file, 1 to load the system from a text file\n");
		scanf("%d", &choice);
	} while (choice != 0 && choice != 1);

	return choice;
}

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options:\n");
	for (int i = 0; i < eNofOptions; i++)
		printf("%d - %s\n", i, str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}

