#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"

int	initMenu(LIST* pizzaList)
{
	if (!L_init(pizzaList))
		return 0;
	return 1;
}

int	addPizza(LIST* pizzaList)
{
	Pizza* pizza = (Pizza*)calloc(1, sizeof(Pizza));
	if (!pizza)
		return 0;
	initPizza(pizza, pizzaList);
	NODE* placeBeforeAdd = getLastPlace(pizzaList);
	L_insert(placeBeforeAdd, pizza);
	return 1;
}

NODE* getLastPlace(LIST* pizzaList)
{
	NODE* qCurrentPlace = &pizzaList->head;
	while (qCurrentPlace->next)
	{
		qCurrentPlace = qCurrentPlace->next;
	}
	return qCurrentPlace;
}

void  initPizza(Pizza* pizza, LIST* pizzaList)
{
	while (1)
	{
		getPizza(pizza);
		if (checkUniqePizza(pizza, pizzaList))
			break;
		printf("This pizza is already on the menu, please enter another one\n");
	}
}

int checkUniqePizza(const Pizza* pizza, const LIST* pizzaList)
{
	NODE* current = pizzaList->head.next; // Start from the first node
	if (current == NULL)
		return TRUE;
	while (current != NULL)
	{
		if (findPizza(pizza, current->key))
			return FALSE;
		current = current->next; // Move to the next node
	}
	return TRUE;
}

int findPizza(const Pizza* pizza1, const Pizza* pizza2)
{
	if (pizza1->size != pizza2->size)
		return FALSE;
	if (pizza1->doughType != pizza2->doughType)
		return FALSE;
	if (!compareByToppings(pizza1, pizza2))
		return FALSE;
	return TRUE;
}

int compareByToppings(const Pizza* pizza1, const Pizza* pizza2)
{
	for (int i = 0; i < MAX_TOP; i++)
	{
		if (pizza1->topType[i] != pizza2->topType[i])
			return FALSE;
	}
	return TRUE;
}

int	getPizzasCount(const LIST* pizzaList)
{
	NODE* p = pizzaList->head.next;
	int counter = 0;
	while (p)
	{
		counter++;
		p = p->next;
	}
	return counter;
}

void printMenu(const Menu* pList)
{
	for (int i = 0; i < 24; i++)
		printf("~ ");
	printf("\n                    MENU                   \n");
	printf("                    ____                   \n");
	L_print(&pList->pizzaList, printPizzaGeneral);
	printf("                Bon appetit!              \n");
	for (int i = 0; i < 24; i++)
		printf("~ ");
	printf("\n\n");
}

void freePizzaList(LIST* pizzaList)
{
	L_free(pizzaList);
}

int	writePizzaListToTextFile(FILE* fp, const LIST* pizzaList)
{
	int pizzaCount = getPizzasCount(pizzaList);
	if (fprintf(fp, "%d\n", pizzaCount) <= 0)
		return 0;
	NODE* p = pizzaList->head.next;
	for (int i = 0; i < pizzaCount; i++)
	{
		if (!writePizzaToTextFile(fp, (Pizza*)p->key))
			return 0;
		p = p->next;
	}
	return 1;
}


int	readPizzaListFromTextFile(FILE* fp, LIST* pizzaList)
{
	int pizzaCount = 0;
	if (fscanf(fp, "%d", &pizzaCount) != 1)
		return 0;

	for (int i = 0; i < pizzaCount; i++)
	{
		Pizza* pizza = (Pizza*)calloc(1, sizeof(Pizza));
		if (!pizza)
			return 0;

		if (!readPizzaFromTextFile(fp, pizza))
		{
			freePizzaList(pizzaList);
			return 0;
		}
		NODE* placeBeforeAdd = getLastPlace(pizzaList);
		L_insert(placeBeforeAdd, pizza);

	}

	return 1;


}