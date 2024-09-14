#ifndef __COUPON__
#define __COUPON__

#include "General.h"

#define MAX_LEN 5  
typedef struct
{
	char coupon[MAX_LEN + 1];
}Coupon;

void	getCoupon(char* code);
int		checkNum(char* code);
int		isCoupon(Coupon* coupon1, char* coupon2); //check if code is coupon's code
void	printCoupon(const Coupon* coupon);
void	printCouponGeneral(void* element);
void	freeCoupon(Coupon* coupon);
void	freeCouponGeneral(void* element);
void	calcCouponDiscount(Coupon* coupon, double* price);
int		writeCouponToTextFile(FILE* fp, const Coupon* coupon);
int		readCouponFromTextFile(FILE* fp, Coupon* coupon);


#endif   