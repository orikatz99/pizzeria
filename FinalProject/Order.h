#ifndef __ORDER__
#define __ORDER__
#include "Date.h"
#include "Time.h"
#include "Address.h"
#include "Menu.h"
#include "AllCoupons.h"
#include "MemberManager.h"
#include "General.h"


#define ACCUMULATION_PERCENTAGE 30

typedef enum {
	eSitting, eTakeAWay, eDelivery, eNofOrderTypes
} eOrderType;

static char* OrderTypeStr[eNofOrderTypes] = { "Sitting in a restaurant", "Take a way", "Home delivery" };

typedef struct
{
	Date		date;
	Time		time;
	eOrderType	typeOfOrder;
	Address		address;
	LIST		pizzaOrderList;
	Coupon		coupon;
	Customer	customer;
	int			member; //1 - if the customer is a club member 0 - if not
	double		priceToPay;
}Order;

void	initOrder(Order* order, AllCoupons* allCoupons, MemberManager* memberManager, const Menu* pList);
void	getCustomerDetails(Order* order, MemberManager* memberManager);
void	choosePizzas(Order* order, const Menu* pList);
Pizza* selectionPizza(const LIST* pizzaList, int choice);
void	checkIsCoupon(Order* order, AllCoupons* allCoupons);
double	getPrice(Order* order);
double	calcPriceAllPizza(Order* order);
void	calcMemberDiscount(Order* order, double* price);
void	usePoints(Order* order, double* price);
void	accumulatingPoints(Order* order, double* price);
void	printOrder(const Order* order);
void	printOrderGeneral(const void* element);
void	printTitle();
void	freeOrder(Order* order);
void	freeOrderGeneral(void* element);
int		writeOrderToTextFile(FILE* fp, const Order* order);
int		readOrderFromTextFile(FILE* fp, Order* order);


#endif   