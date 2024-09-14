#ifndef __ALL_COUPONS__
#define __ALL_COUPONS__

#include "Coupon.h"

typedef struct
{
	Coupon** arrCoupons; //All coupons in the system
	int numOfCoupons; //numbers of coupons in system

} AllCoupons;

void		initCouponsArr(AllCoupons* coupons); //reset the array of coupons and number of coupons
int			addCoupon(AllCoupons* coupons);
Coupon* findCouponByCode(char* coupon, AllCoupons* allCoupons);
void		printAllCoupons(const Coupon** arr, int size);
void		freeAllCouponsArr(Coupon** arr, int size);
int			writeCouponsArrToTextFile(FILE* fp, Coupon** arrCoupons, int count);
Coupon** readCouponsArrFromTextFile(FILE* fp, int* pCount);


#endif