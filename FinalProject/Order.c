#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Order.h"


void initOrder(Order* order, AllCoupons* allCoupons, MemberManager* memberManager, const Menu* pList)
{
	printf("\nEnter the order details:\n");
	getCustomerDetails(order, memberManager);

	getCorrectDate(&order->date);// We will update a date
	getCorrectTime(&order->time);//We will update an hour

	printf("What type of order would you like?\n");//We will update the order type
	order->typeOfOrder = getTypeFromUser(eNofOrderTypes, OrderTypeStr);

	if (order->typeOfOrder == eDelivery)//If it is a delivery, we will update the order address
	{
		printf("Please enter the address to which you would like to send the order\n");
		if (!initAdress(&order->address))
		{
			printf("allocation error\n");
			return;
		}
	}

	printMenu(pList);
	if (!L_init(&order->pizzaOrderList))
	{
		printf("memory error\n");
		return;
	}

	int answer;
	do {
		choosePizzas(order, pList);
		printf("Would you like order another pizza? (1-yes or 0-no)\n");//You can choose a pizza that has already been ordered
		scanf("%d", &answer);
		while (answer != 1 && answer != 0)
		{
			printf("1-yes or 0-no\n");
			scanf("%d", &answer);
		}
	} while (answer == 1);

	checkIsCoupon(order, allCoupons);
	double totalPrice = getPrice(order);
	printf("The amount you have to pay is: %lf\n", totalPrice);
	if (order->member == TRUE)
	{
		accumulatingPoints(order, &totalPrice);
		updatePoints(memberManager, &order->customer);
	}
	order->priceToPay = totalPrice;
}

void getCustomerDetails(Order* order, MemberManager* memberManager)
{
	initCustomer(&order->customer);
	int uniqe = isIdUniqe(memberManager->membersArr, memberManager->membersCount, order->customer.id);
	if (uniqe != -1)
	{
		printf("You are a club member!\n\n");
		order->member = TRUE;
	}
	else
	{
		printf("You are not a club member!\n\n");
		order->member = FALSE;
	}
}

void choosePizzas(Order* order, const Menu* pList)
{
	int flag = 0;
	int answer;
	Pizza* temp = (Pizza*)calloc(1, sizeof(Pizza));
	if (temp == NULL) {
		// Handle the case where memory allocation fails
		printf("Memory allocation failed\n");
		return;
	}
	while (flag == 0)
	{
		printf("Which pizza from the menu would you like? (write the number of the pizza)\n");
		flag = 1;
		scanf("%d", &answer);
		Pizza* selectedPizza = selectionPizza(&pList->pizzaList, answer);
		if (selectedPizza != NULL) {
			// Copy the selected pizza into the temp variable
			memcpy(temp, selectedPizza, sizeof(Pizza));
		}
		if (answer<1 || answer> getPizzasCount(&pList->pizzaList))
		{
			printf("There is no such pizza\n");
			flag = 0;
		}
	}
	NODE* placeBeforeAdd = getLastPlace(&order->pizzaOrderList);
	L_insert(placeBeforeAdd, temp);
}

Pizza* selectionPizza(const LIST* pizzaList, int choice) {
	int i = 1;
	NODE* current = pizzaList->head.next; // Start from the first node

	while (current != NULL && i < choice) {
		i++;
		current = current->next; // Move to the next node
	}

	if (current != NULL) {
		return (Pizza*)(current->key); // Return a pointer to the selected pizza
	}
	else {
		return NULL; // Return NULL if choice is out of range
	}
}

void checkIsCoupon(Order* order, AllCoupons* allCoupons)
{
	char temp[MAX_STR_LEN];
	int answer;
	int flag = 0;
	printf("Do you have a coupon code? (1-yes or 0-no)\n");
	scanf("%d", &answer);
	while (answer != 0 && answer != 1)
	{
		printf("Invalid\n");
		scanf("%d", &answer);
	}
	if (answer == 1)
	{
		while (flag == 0)
		{
			getCoupon(temp);
			if (findCouponByCode(temp, allCoupons) != NULL)
			{
				strcpy(order->coupon.coupon, temp);
				flag = 1;
			}
			else
			{
				printf("We don't have such a coupon, do you want to try another one? (1-yes or 0-no)\n");
				scanf("%d", &answer);
				while (answer != 0 && answer != 1)
				{
					printf("Invalid\n");
					scanf("%d", &answer);
				}
				if (answer == 0)
				{
					flag = 1;
					strcpy(order->coupon.coupon, "NULL");
				}
			}
		}
	}
	else
		strcpy(order->coupon.coupon, "NULL");
}

double getPrice(Order* order)
{
	double totalPrice = calcPriceAllPizza(order);
	if (strcmp(order->coupon.coupon, "NULL") != 0)
		calcCouponDiscount(&order->coupon, &totalPrice);
	if (order->member == TRUE)
		calcMemberDiscount(order, &totalPrice);
	return totalPrice;
}

double calcPriceAllPizza(Order* order)
{
	double sum = 0;
	NODE* current = order->pizzaOrderList.head.next; // Start from the first node
	while (current != NULL)
	{
		Pizza* currentPizza = current->key;
		sum += currentPizza->price;
		current = current->next; // Move to the next node
	}
	return sum;
}

void calcMemberDiscount(Order* order, double* price)
{
	int answer;
	printf("Total order right now: %lf\n", *price);
	printf("You have %d points\n", order->customer.points);
	printf("Would you like to redeem points? (1-yes or 0-no)\n");
	scanf("%d", &answer);
	while (answer != 0 && answer != 1)
	{
		printf("Invalid\n");
		scanf("%d", &answer);
	}
	if (answer == TRUE)
		usePoints(order, price);
}

void usePoints(Order* order, double* price)
{
	int answer;
	int flag = 0;
	while (flag == 0)
	{
		flag = 1;
		printf("How many points would you like to use?\n");
		scanf("%d", &answer);
		if (answer <= 0)
		{
			printf("Invalid\n");
			flag = 0;
		}
		else if (answer > *price)
		{
			printf("Incorrect, the number of points is greater than the amount of the order\n");
			flag = 0;
		}
		else if (answer > order->customer.points)
		{
			printf("Incorrect, the number of points is greater than the number of points you have\n");
			flag = 0;
		}
	}
	*price -= answer;
	order->customer.points -= answer;
}

void accumulatingPoints(Order* order, double* price)
{
	int sum = (int)(*price) * ACCUMULATION_PERCENTAGE / 100;
	printf("At the end of the payment you will accumulate %d points\n", sum);
	order->customer.points += sum;
}

void printOrder(const Order* order)
{
	printTitle();
	printCustomer(&order->customer);
	printf("Your order type is: %s\n", OrderTypeStr[order->typeOfOrder]);
	if (order->typeOfOrder == eDelivery)
		printAddress(&order->address);
	printDate(&order->date);
	printTime(&order->time);
	printf("\n");
	L_print(&order->pizzaOrderList, printPizzaGeneral);
	printf("The amount you have to pay is: %lf\n", order->priceToPay);
	printf("\nThanks!\n");
}

void	printOrderGeneral(const void* element)
{
	Order* order = (Order*)element;
	printOrder(order);
}

void printTitle()
{
	printf("\n");
	for (int i = 0; i < 13; i++)
		printf("* ");
	printf("\n");
	printf("* Summary of the order  *\n");
	for (int i = 0; i < 13; i++)
		printf("* ");
	printf("\n\n");
}

void freeOrder(Order* order)
{
	if (order->typeOfOrder == eDelivery)
		freeAddress(&order->address);
	freePizzaList(&order->pizzaOrderList);
	freeCustomer(&order->customer);
}

void freeOrderGeneral(void* element)
{
	Order* order = (Order*)element;
	freeOrder(order);
}

int writeOrderToTextFile(FILE* fp, const Order* order)
{
	if (!writeCustomerToTextFile(fp, &order->customer))
		return 0;
	if (!writeDateToTextFile(fp, &order->date))
		return 0;
	if (!writeTimeToTextFile(fp, &order->time))
		return 0;
	if (fprintf(fp, "%d\n", order->typeOfOrder) < 0)
		return 0;

	if (order->typeOfOrder == eDelivery)
	{
		if (!writeAddressToTextFile(fp, &order->address))
			return 0;
	}

	if (!writePizzaListToTextFile(fp, &order->pizzaOrderList))
		return 0;

	if (!writeCouponToTextFile(fp, &order->coupon))
		return 0;


	if (fprintf(fp, "%lf\n", order->priceToPay) < 0)
		return 0;

	return 1;

}


int readOrderFromTextFile(FILE* fp, Order* order)
{
	if (!readCustomerFromTextFile(fp, &order->customer))
		return 0;
	if (!readDateFromTextFile(fp, &order->date))
		return 0;
	if (!readTimeFromTextFile(fp, &order->time))
		return 0;
	if (fscanf(fp, "%d", &order->typeOfOrder) != 1)
		return 0;

	if (order->typeOfOrder == eDelivery)
	{
		if (!readAddressFromTextFile(fp, &order->address))
			return 0;
	}

	if (!L_init(&order->pizzaOrderList))
	{
		printf("memory error\n");
		return 0;
	}

	if (!readPizzaListFromTextFile(fp, &order->pizzaOrderList))
		return 0;

	if (!readCouponFromTextFile(fp, &order->coupon))
		return 0;

	if (fscanf(fp, "%lf", &order->priceToPay) != 1)
		return 0;

	return 1;
}