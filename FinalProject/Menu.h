#ifndef __MENU__
#define __MENU__

#include "List.h"
#include "Pizza.h"

typedef struct
{
	LIST pizzaList;

}Menu;


int	initMenu(LIST* pizzaList);
int	addPizza(LIST* pizzaList);
NODE* getLastPlace(LIST* pizzaList);
void  initPizza(Pizza* pizza, LIST* pizzaList);
int checkUniqePizza(const Pizza* pizza, const LIST* pizzaList);
int findPizza(const Pizza* pizza1, const Pizza* pizza2);
int compareByToppings(const Pizza* pizza1, const Pizza* pizza2);
int	getPizzasCount(const LIST* pizzaList);
void printMenu(const Menu* pList);
void freePizzaList(LIST* pizzaList);
int	writePizzaListToTextFile(FILE* fp, const LIST* pizzaList);
int	readPizzaListFromTextFile(FILE* fp, LIST* pizzaList);


#endif