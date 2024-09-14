#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "AllCoupons.h"

void initCouponsArr(AllCoupons* coupons) //reset the array of coupons and number of coupons
{
	coupons->numOfCoupons = 0;
	coupons->arrCoupons = NULL;
}

int addCoupon(AllCoupons* coupons) //add coupon to system by adding one more place in array using realloc
{
	int flag;
	coupons->arrCoupons = (Coupon**)realloc(coupons->arrCoupons, (coupons->numOfCoupons + 1) * sizeof(Coupon*));
	if (!coupons->arrCoupons)
		return FALSE;

	//allocate memory for the new coupon object
	coupons->arrCoupons[coupons->numOfCoupons] = malloc(sizeof(Coupon));
	if (!coupons->arrCoupons[coupons->numOfCoupons])
	{
		free(coupons->arrCoupons); //free previously allocated memory
		return FALSE;
	}

	do
	{
		flag = 1;
		getCoupon(coupons->arrCoupons[coupons->numOfCoupons]->coupon);
		if (findCouponByCode(coupons->arrCoupons[coupons->numOfCoupons]->coupon, coupons) != NULL)
		{
			printf("This coupon already exists - enter another code\n");
			flag = 0;
		}
	} while (flag == 0);
	coupons->numOfCoupons++;
	return TRUE;
}

Coupon* findCouponByCode(char* coupon, AllCoupons* allCoupons)
{
	for (int i = 0; i < allCoupons->numOfCoupons; i++)
	{
		if (isCoupon(allCoupons->arrCoupons[i], coupon)) //locate coupon in array by its code
		{
			return allCoupons->arrCoupons[i];
		}
	}
	return NULL;
}

void printAllCoupons(const Coupon** arr, int size)
{
	printf("There are %d coupons\n", size);
	generalArrayFunction(arr, size, sizeof(*arr), printCouponGeneral);

}

void freeAllCouponsArr(Coupon** arr, int size)
{
	generalArrayFunction(arr, size, sizeof(*arr), freeCouponGeneral);
}

int	writeCouponsArrToTextFile(FILE* fp, Coupon** arrCoupons, int count)
{
	if (fprintf(fp, "%d\n", count) < 0)
		return 0;
	for (int i = 0; i < count; i++)
	{
		if (!writeCouponToTextFile(fp, arrCoupons[i]))
			return 0;
	}

	return 1;
}

Coupon** readCouponsArrFromTextFile(FILE* fp, int* pCount)
{
	Coupon** allCoupons;

	if (fscanf(fp, "%d", pCount) != 1)
		return NULL;

	allCoupons = (Coupon**)malloc(*pCount * sizeof(Coupon*));
	if (!allCoupons)
		return NULL;

	for (int i = 0; i < *pCount; i++)
	{
		allCoupons[i] = (Coupon*)calloc(1, sizeof(Coupon));
		if (!allCoupons[i])
			return NULL;

		if (!readCouponFromTextFile(fp, allCoupons[i]))
		{
			freeAllCouponsArr(allCoupons, *pCount);
			return NULL;
		}
	}
	return allCoupons;
}