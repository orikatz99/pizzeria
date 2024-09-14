#ifndef __PIZZA__
#define __PIIZA__

#include "General.h"

typedef enum {
	eNoToppings, eOlives, eMushrooms, eCorn, eTomato, eNofToppingTypes
} eToppingType;

static char* ToppingTypeStr[eNofToppingTypes] = { "No Toppings", "Olives", "Mushrooms", "Corns", "Tomatoes" };

typedef enum {
	eRegular, eGlutenFree, eVegan, eWholeWheat, eNofDoughTypes
} eDoughType;

static char* DoughTypeStr[eNofDoughTypes] = { "Regular", "Gluten free", "Vegan", "Whole wheat" };


typedef struct
{
	eToppingType	topType[MAX_TOP];
	eDoughType		doughType;
	int				size;
	double			price;
}Pizza;


void	getSize(Pizza* pizza);
void	getPizza(Pizza* pizza);
void	drawPizza(const Pizza pizza);
void	printRow(const int size);
char	toppingToChar(const eToppingType topType);
void	drawHalf(const Pizza pizza, int start, int end, char leftTop, char rightTop);
void	UpdatePrice(Pizza* pizza);
int		getPriceBasic(Pizza pizza);
int		getPriceDough(const Pizza pizza);
int		getPriceTopping(eToppingType topType);
int		calcTotalTop(const Pizza pizza);
char	sizeToChar(const Pizza* pizza);
void	printPizza(const Pizza* pizza);
void	printPizzaGeneral(const void* element);
int		writePizzaToTextFile(FILE* fp, const Pizza* pizza);
int		readPizzaFromTextFile(FILE* fp, Pizza* pizza);

#endif