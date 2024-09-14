#include <stdlib.h>
#include <string.h>
#include "PizzeriaBinFile.h"

//Writing to a binary file

int		savePizzeriaToFile(const Pizzeria* pizzeria, const char* fileName)
{//Writing to a binary file of pizzeria data
	FILE* fp;
	fp = fopen(fileName, "wb");

	CHECK_RETURN_FALSE(fp);

	if (!writeNameToBFile(fp, pizzeria->name))//Writing the name of the pizzeria
	{
		CLOSE_RETURN_FALSE(fp);
	}
	if (!writeAddressToBFile(fp, &pizzeria->address))//Writing the Address of the pizzeria
	{
		CLOSE_RETURN_FALSE(fp);

	}
	if (!writePizzaListToBFile(fp, &pizzeria->menu.pizzaList))//Writing the menu
	{
		CLOSE_RETURN_FALSE(fp);

	}
	if (!writeMembersArrToBFile(fp, pizzeria->membersArr.membersArr, pizzeria->membersArr.membersCount))//Writing the members arr
	{
		CLOSE_RETURN_FALSE(fp);

	}
	if (!writeCouponsArrToBFile(fp, pizzeria->allCoupons.arrCoupons, pizzeria->allCoupons.numOfCoupons))//Writing the coupons arr
	{
		CLOSE_RETURN_FALSE(fp);

	}
	if (!writeOrdersArrToBFile(fp, pizzeria->orders, pizzeria->numOfOrders))//Writing the orders arr
	{
		CLOSE_RETURN_FALSE(fp);

	}
	fclose(fp);
	return 1;
}

int		writeNameToBFile(FILE* fp, const char* string)
{//Writing to a binary file of the pizzeria string
	int len = (int)strlen(string) + 1;
	if (fwrite(&len, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(string, sizeof(char), len, fp) != len)
		return 0;
	return 1;
}

int		writeAddressToBFile(FILE* fp, const Address* address)
{//Writing to a binary file of the pizzeria address
	if (!writeNameToBFile(fp, address->city))
		return 0;
	if (!writeNameToBFile(fp, address->street))
		return 0;
	if (fwrite(&address->houseNum, sizeof(int), 1, fp) != 1)
		return 0;
	return 1;
}

int		writePizzaToBFile(FILE* fp, const Pizza* pizza)
{//Writing to a binary file of pizza data
	if (fwrite(&pizza->size, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(&pizza->doughType, sizeof(int), 1, fp) != 1)
		return 0;
	for (int i = 0; i < MAX_TOP; i++)
	{
		if (fwrite(&pizza->topType, sizeof(int), 1, fp) != 1)
			return 0;
	}
	if (fwrite(&pizza->price, sizeof(double), 1, fp) != 1)
		return 0;
	return 1;
}

int		writePizzaListToBFile(FILE* fp, const LIST* pizzaList)
{//Writing to a binary file of a list of pizzas
	NODE* current = pizzaList->head.next;
	int count = getPizzasCount(pizzaList);
	if (fwrite(&count, sizeof(int), 1, fp) != 1)
		return 0;
	while (current != NULL)
	{
		if (!writePizzaToBFile(fp, (Pizza*)current->key))
			return 0;
		current = current->next; // Move to the next node
	}
	return 1;
}

int		writeCustomerToBFile(FILE* fp, const Customer* customer)
{//Writing to a binary file of the pizzeria customer
	if (!writeNameToBFile(fp, customer->name))
		return 0;
	if (!writeNameToBFile(fp, customer->id))
		return 0;
	if (fwrite(&customer->points, sizeof(int), 1, fp) != 1)
		return 0;
	return 1;
}

int		writeMembersArrToBFile(FILE* fp, const Customer* membersArr, const int count)
{//Writing to a binary file of an array of members
	if (fwrite(&count, sizeof(int), 1, fp) != 1)
		return 0;
	for (int i = 0; i < count; i++)
		if (!writeCustomerToBFile(fp, &membersArr[i]))
			return 0;
	return 1;
}

int		writeCouponToBFile(FILE* fp, const Coupon* coupon)
{//Writing to a binary file of coupon data
	if (fwrite(&coupon->coupon, sizeof(char), MAX_LEN, fp) != MAX_LEN)
		return 0;
	return 1;
}

int		writeCouponsArrToBFile(FILE* fp, Coupon** arrCoupons, int count)
{//Writing to a binary file of an array of coupons
	if (fwrite(&count, sizeof(int), 1, fp) != 1)
		return 0;
	for (int i = 0; i < count; i++)
		if (!writeCouponToBFile(fp, arrCoupons[i]))
			return 0;
	return 1;
}

int 	writeOrderToBFile(FILE* fp, const Order* order)
{//Writing to a binary file of order data
	if (!writeCustomerToBFile(fp, &order->customer))
		return 0;
	if (fwrite(&order->date, sizeof(Date), 1, fp) != 1)
		return 0;
	if (!saveTimeToBFile(fp, &order->time))
		return 0;
	if (fwrite(&order->typeOfOrder, sizeof(int), 1, fp) != 1)
		return 0;
	if (order->typeOfOrder == eDelivery)//If it is a delivery, we will update the order address
	{
		if (!writeAddressToBFile(fp, &order->address))
			return 0;
	}
	if (!writePizzaListToBFile(fp, &order->pizzaOrderList))
		return 0;
	if (!writeCouponToBFile(fp, &order->coupon))
		return 0;
	if (fwrite(&order->priceToPay, sizeof(double), 1, fp) != 1)
		return 0;
	return 1;
}

int		writeOrdersArrToBFile(FILE* fp, Order* orderArr, int count)
{//Writing to a binary file of an array of orders
	if (fwrite(&count, sizeof(int), 1, fp) != 1)
		return 0;
	for (int i = 0; i < count; i++)
		if (!writeOrderToBFile(fp, &orderArr[i]))
			return 0;
	return 1;
}

//Reading from a binary file

int		initPizzeriaFromFile(Pizzeria* pizzeria, const char* fileName)
{//Reading from a binary file of pizzeria data
	FILE* fp = fopen(fileName, "rb");

	CHECK_RETURN_FALSE(fp);


	if (!readNameFromBFile(fp, &pizzeria->name))//Reading the name of the pizzeria
	{
		freePizzeria(pizzeria);
		CLOSE_RETURN_FALSE(fp);

	}
	if (!readAddressFromBFile(fp, &pizzeria->address))//Reading the address of the pizzeria
	{
		freePizzeria(pizzeria);
		CLOSE_RETURN_FALSE(fp);

	}
	if (!L_init(&pizzeria->menu.pizzaList))
	{
		printf("memory error\n");
		return 0;
	}
	if (!readPizzaListFromBFile(fp, &pizzeria->menu.pizzaList))//Reading the address of the pizzeria
	{
		freePizzeria(pizzeria);
		CLOSE_RETURN_FALSE(fp);

	}
	pizzeria->membersArr.membersArr = readMembersArrFromBFile(fp, &pizzeria->membersArr.membersCount);//Reading the planes array
	if (!pizzeria->membersArr.membersArr)
	{
		freePizzeria(pizzeria);
		CLOSE_RETURN_FALSE(fp);

	}
	pizzeria->allCoupons.arrCoupons = readCouponsArrFromBFile(fp, &pizzeria->allCoupons.numOfCoupons);//Reading the coupons array
	if (!pizzeria->allCoupons.arrCoupons)
	{
		freePizzeria(pizzeria);
		CLOSE_RETURN_FALSE(fp);

	}
	pizzeria->orders = readOrdersArrFromBFile(fp, &pizzeria->numOfOrders);//Reading the flights array
	if (!pizzeria->orders)
	{
		freePizzeria(pizzeria);
		CLOSE_RETURN_FALSE(fp);

	}
	pizzeria->typeSort = 0;
	return 1;
}

int		readNameFromBFile(FILE* fp, char** string)
{//Reading from a binary file of the pizzzeria string
	int len;
	if (fread(&len, sizeof(int), 1, fp) != 1)
		return 0;
	*string = (char*)malloc(len * sizeof(char));
	if (!*string)
		return 0;
	if (fread(*string, sizeof(char), len, fp) != len)
	{
		free(*string);
		return 0;
	}
	return 1;
}

int		readAddressFromBFile(FILE* fp, Address* address)
{//Reading from a binary file of the pizzzeria address
	if (!readNameFromBFile(fp, &address->city))
		return 0;
	if (!readNameFromBFile(fp, &address->street))
		return 0;
	if (fread(&address->houseNum, sizeof(int), 1, fp) != 1)
		return 0;
	return 1;
}

int		readPizzaFromBFile(FILE* fp, Pizza* pizza)
{//Reading from a binary file of pizza data
	if (fread(&pizza->size, sizeof(int), 1, fp) != 1)
		return 0;
	if (fread(&pizza->doughType, sizeof(int), 1, fp) != 1)
		return 0;
	for (int i = 0; i < MAX_TOP; i++)
	{
		if (fread(&pizza->topType, sizeof(int), 1, fp) != 1)
			return 0;
	}
	if (fread(&pizza->price, sizeof(double), 1, fp) != 1)
		return 0;
	return 1;
}

int		readPizzaListFromBFile(FILE* fp, LIST* pizzaList)
{//Reading from a binary file of an list of pizzas
	int count;
	if (fread(&count, sizeof(int), 1, fp) != 1)
		return 0;

	for (int i = 0; i < count; i++)
	{
		Pizza* pizza = (Pizza*)calloc(1, sizeof(Pizza));
		if (!pizza)
			return 0;
		if (!readPizzaFromBFile(fp, pizza))
		{
			freePizzaList(pizzaList);
			return 0;
		}
		NODE* placeBeforeAdd = getLastPlace(pizzaList);
		L_insert(placeBeforeAdd, pizza);
	}
	return 1;
}

int		readCustomerFromBFile(FILE* fp, Customer* customer)
{//Reading from a binary file of the pizzzeria customer
	if (!readNameFromBFile(fp, &customer->name))
		return 0;
	if (!readNameFromBFile(fp, &customer->id))
		return 0;
	if (fread(&customer->points, sizeof(int), 1, fp) != 1)
		return 0;
	return 1;
}

Customer* readMembersArrFromBFile(FILE* fp, int* pCount)
{//Reading from a binary file of an array of members
	Customer* memArr;
	if (fread(pCount, sizeof(int), 1, fp) != 1)
		return NULL;

	memArr = (Customer*)malloc(*pCount * sizeof(Customer));
	if (!memArr)
		return NULL;

	for (int i = 0; i < *pCount; i++)
		if (!readCustomerFromBFile(fp, &memArr[i]))
		{
			freeMemberManager(memArr, *pCount);
			return NULL;
		}
	return memArr;
}

int		readCouponFromBFile(FILE* fp, Coupon* coupon)
{//Reading from a binary file of coupon data
	if (fread(&coupon->coupon, sizeof(char), MAX_LEN, fp) != MAX_LEN)
		return 0;
	return 1;
}

Coupon** readCouponsArrFromBFile(FILE* fp, int* pCount)
{
	Coupon** allCoupons;
	if (fread(pCount, sizeof(int), 1, fp) != 1)
		return NULL;

	allCoupons = (Coupon**)malloc(*pCount * sizeof(Coupon*));
	if (!allCoupons)
		return NULL;

	for (int i = 0; i < *pCount; i++)
	{
		allCoupons[i] = (Coupon*)calloc(1, sizeof(Coupon));
		if (!allCoupons[i])
			return NULL;
		if (!readCouponFromBFile(fp, allCoupons[i]))
		{
			freeAllCouponsArr(allCoupons, *pCount);
			return NULL;
		}
	}
	return allCoupons;
}

int 	readOrderFromBFile(FILE* fp, Order* order)
{//Reading from a binary file of order data
	if (!readCustomerFromBFile(fp, &order->customer))
		return 0;
	if (fread(&order->date, sizeof(Date), 1, fp) != 1)
		return 0;
	if (!readTimeFromFile(fp, &order->time))
		return 0;
	if (fread(&order->typeOfOrder, sizeof(int), 1, fp) != 1)
		return 0;
	if (order->typeOfOrder == eDelivery)//If it is a delivery, we will update the order address
	{
		if (!readAddressFromBFile(fp, &order->address))
			return 0;
	}
	if (!L_init(&order->pizzaOrderList))
	{
		printf("memory error\n");
		return 0;
	}
	if (!readPizzaListFromBFile(fp, &order->pizzaOrderList))
		return 0;
	if (!readCouponFromBFile(fp, &order->coupon))
		return 0;
	if (fread(&order->priceToPay, sizeof(double), 1, fp) != 1)
		return 0;
	return 1;
}

Order* readOrdersArrFromBFile(FILE* fp, int* pCount)
{//Reading from a binary file of an array of planes
	Order* ordersArr;
	if (fread(pCount, sizeof(int), 1, fp) != 1)
		return NULL;

	ordersArr = (Order*)malloc(*pCount * sizeof(Order));
	if (!ordersArr)
		return NULL;

	for (int i = 0; i < *pCount; i++)
		if (!readOrderFromBFile(fp, &ordersArr[i]))
		{
			freeOrders(ordersArr, *pCount);
			return NULL;
		}
	return ordersArr;
}