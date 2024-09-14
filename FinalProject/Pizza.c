#include <stdio.h>
#include "Pizza.h"

void getPizza(Pizza* pizza)
{
	printf("\nYou have 3 sizes for pizzas\n");
	printf("%s- %d NIS, %s- %d NIS, %s- %d NIS\n", "Small", P_SMALL, "Medium", P_MEDIUM, "Large", P_LARGE);
	getSize(pizza);

	printf("\nYou have 4 types of dough\n");
	printf("%s- %d NIS, %s- %d NIS, %s- %d NIS, %s- %d NIS\n", DoughTypeStr[0], 0, DoughTypeStr[1], P_GLUTEN_FREE, DoughTypeStr[2], P_VEGAN, DoughTypeStr[3], P_WHOLE_WHEAT);
	pizza->doughType = getTypeFromUser(eNofDoughTypes, DoughTypeStr);

	printf("\nYou have %d quarters for a pizza\nchoose which topping to put in each quarter\n", MAX_TOP);
	printf("%s- %d NIS, %s- %d NIS, %s- %d NIS, %s- %d NIS\n", ToppingTypeStr[1], P_OLIVE, ToppingTypeStr[2], P_MUSHROOM, ToppingTypeStr[3], P_CORN, ToppingTypeStr[4], P_TOMATO);
	printf("The price for the topping is for one quarter\n");
	for (int i = 0; i < MAX_TOP; i++)
		pizza->topType[i] = getTypeFromUser(eNofToppingTypes, ToppingTypeStr);
	UpdatePrice(pizza);
	printf("\n");
}

void getSize(Pizza* pizza)
{
	do
	{
		printf("\nEnter the pizza size:\n");
		printf("%d- for small\n%d- for medium\n%d- for large\n", SMALL, MEDIUM, LARGE);
		scanf("%d", &pizza->size);
	} while (pizza->size != SMALL && pizza->size != MEDIUM && pizza->size != LARGE);
}

void drawPizza(const Pizza pizza)
{
	printRow(pizza.size);

	char topLeft = toppingToChar(pizza.topType[0]);
	char topRight = toppingToChar(pizza.topType[1]);
	drawHalf(pizza, 0, pizza.size / 2, topLeft, topRight);

	topLeft = toppingToChar(pizza.topType[2]);
	topRight = toppingToChar(pizza.topType[3]);
	drawHalf(pizza, pizza.size / 2, pizza.size - 1, topLeft, topRight);

	printRow(pizza.size);
}

void printRow(const int size)
{
	for (int i = 0; i < size; i++)
		printf("* ");
	printf("\n");
}

char toppingToChar(const eToppingType topType)
{
	char ch = ' ';//no topping

	if (topType == 1)
		ch = 'O';
	else if (topType == 2)
		ch = 'M';
	else if (topType == 3)
		ch = 'C';
	else if (topType == 4)
		ch = 'T';

	return ch;
}

void drawHalf(const Pizza pizza, int start, int end, char leftTop, char rightTop)
{
	for (int i = start; i < end; i++)
	{
		printf("* ");
		for (int j = 1; j < pizza.size / 2; j++)
		{
			printf("%c ", leftTop);
		}
		for (int m = pizza.size / 2; m < pizza.size - 1; m++)
		{
			printf("%c ", rightTop);
		}
		printf("* ");
		printf("\n");
	}
}

void UpdatePrice(Pizza* pizza)
{
	pizza->price = getPriceBasic(*pizza) + getPriceDough(*pizza) + calcTotalTop(*pizza);
}

int getPriceBasic(Pizza pizza)
{
	if (pizza.size == SMALL)
		return P_SMALL;
	else if (pizza.size == MEDIUM)
		return P_MEDIUM;
	return  P_LARGE;
}

int getPriceDough(Pizza pizza)
{
	if (pizza.doughType == 1)
		return P_GLUTEN_FREE;
	else if (pizza.doughType == 2)
		return P_VEGAN;
	else if (pizza.doughType == 3)
		return P_WHOLE_WHEAT;
	return 0; //regular
}

int  getPriceTopping(const eToppingType topType)
{
	if (topType == 1)
		return P_OLIVE;
	else if (topType == 2)
		return P_MUSHROOM;
	else if (topType == 3)
		return P_CORN;
	else if (topType == 4)
		return P_TOMATO;
	return 0;//no topping
}

int calcTotalTop(const Pizza pizza)
{
	int totalPrice = 0;
	for (int i = 0; i < MAX_TOP; i++)
	{
		totalPrice += getPriceTopping(pizza.topType[i]);
	}
	return totalPrice;
}

char sizeToChar(const Pizza* pizza)
{
	if (pizza->size == SMALL)
		return 'S';
	else if (pizza->size == MEDIUM)
		return 'M';
	return 'L';
}

void printPizza(const Pizza* pizza)
{
	char ch = sizeToChar(pizza);
	printf("Pizza size:%-20c \n", ch);
	printf("Dough:%-20s\n", DoughTypeStr[pizza->doughType]);
	for (int i = 1; i <= MAX_TOP; i++)
		printf("The topping in the %d quarter: %s\n", i, ToppingTypeStr[pizza->topType[i - 1]]);
	drawPizza(*pizza);
	printf("\nPizza price: %lf NIS\n\n", pizza->price);
}

void printPizzaGeneral(const void* element)
{
	const Pizza* pizza = (const Pizza*)element;
	printPizza(pizza);
}

int writePizzaToTextFile(FILE* fp, const Pizza* pizza)
{
	if (fprintf(fp, "%d\n", pizza->size) < 0)
		return 0;
	if (fprintf(fp, "%d\n", pizza->doughType) < 0)
		return 0;

	for (int i = 0; i < MAX_TOP; i++)
	{
		if (fprintf(fp, "%d\n", pizza->topType[i]) < 0) //check!
			return 0;
	}

	if (fprintf(fp, "%lf\n", pizza->price) < 0)
		return 0;

	return 1;

}



int readPizzaFromTextFile(FILE* fp, Pizza* pizza)
{
	if (fscanf(fp, "%d\n", &pizza->size) != 1)
		return 0;
	if (fscanf(fp, "%d\n", &pizza->doughType) != 1)
		return 0;

	for (int i = 0; i < MAX_TOP; i++)
	{
		if (fscanf(fp, "%d\n", &pizza->topType[i]) != 1)
			return 0;
	}

	if (fscanf(fp, "%lf\n", &pizza->price) != 1)
		return 0;

	return 1;
}
