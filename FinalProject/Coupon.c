#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Coupon.h"

void getCoupon(char* code)
{
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Enter coupon - %d UPPER CASE letters and then 2 digits that represent the discount he gives\n", MAX_LEN - 2);
		myGets(temp, MAX_STR_LEN, stdin);
		if (strlen(temp) != MAX_LEN)
		{
			printf("Coupon should be %d letters\n", MAX_LEN);
			ok = 0;
		}
		else {
			for (int i = 0; i < MAX_LEN - 2; i++)
			{
				if (isupper(temp[i]) == 0)
				{
					printf("The first 3 characters must be capital letters\n");
					ok = 0;
					break;
				}
			}
			if (ok != 0)
				ok = checkNum(temp);
		}
	} while (!ok);

	strcpy(code, temp);
}

int checkNum(char* code)
//A function that receives the coupon that the user entered 
// and checks if the last 2 characters are digits 
// and if they are in a normal range (5-50)
{
	int ok = 1;
	int discountPercentage = 0;
	for (int i = MAX_LEN - 2; i < MAX_LEN; i++)
	{
		if (!isdigit(code[i]))
		{
			printf("The last 2 characters must be digits\n");
			ok = 0;
			break;
		}
	}
	if (ok != 0)
	{
		discountPercentage = (code[MAX_LEN - 2] - '0') * 10 + (code[MAX_LEN - 1] - '0');
		if (discountPercentage < 1 || discountPercentage>50)
		{
			printf("The discount percentage is invalid\n");
			ok = 0;
		}
	}
	return ok;
}

int isCoupon(Coupon* coupon1, char* coupon2) //check if code is coupon's code
{
	if (!isSameStr(coupon1->coupon, coupon2))
		return 0;
	return 1;
}

void printCoupon(const Coupon* coupon) //print coupon details
{
	printf("Coupon: %s\n", coupon->coupon);
}

void	printCouponGeneral(void* element)
{
	const Coupon* coupon = *(const Coupon**)element;
	printCoupon(coupon);
}

void	freeCoupon(Coupon* coupon)
{
	//nothing to free
}

void freeCouponGeneral(void* element)
{
	Coupon* coupon = *(Coupon**)element;
	freeCoupon(coupon);
}

void calcCouponDiscount(Coupon* coupon, double* price)
{
	printf("Total order before discount: %lf\n", *price);
	int discountPercentage = ((coupon->coupon[MAX_LEN - 2] - '0') * 10) + (coupon->coupon[MAX_LEN - 1] - '0');
	printf("You have %d percent off the coupon\n", discountPercentage);
	*price = (*price) * (100 - discountPercentage) / 100;
}

int writeCouponToTextFile(FILE* fp, const Coupon* coupon)
{

	return (fprintf(fp, "%s\n", coupon->coupon) >= 0);

}

int	 readCouponFromTextFile(FILE* fp, Coupon* coupon)
{
	return (fscanf(fp, "%s", coupon->coupon) == 1);
}
