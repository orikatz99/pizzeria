#ifndef __MYMAIN__
#define __MYMAIN__

#include "Pizzeria.h"
#include "General.h"

typedef enum
{
	eAddCoupon, eAddMember, eAddPizza, eAddOrder, ePrintPizzeria,
	ePrintAllCoupons, ePrintAllMembers, ePrintMenu, ePrintAllOrders, eSortOrder, eFindOrder, eNofOptions
} eMenuOptions;

const char* str[eNofOptions] = { "Add Coupon","Add Member","Add Pizza","Add Order",
								"Print Pizzeria", "Print all Coupons",
								"Print all Members","Print Menu","Print all Orders",
								"Sort Order", "Find Order" };

#define PIZZERIA_BINFILE_NAME_SRC "pizzeria.bin"
#define PIZZERIA_TXTFILE_NAME_SRC "pizzeria.txt"

#define PIZZERIA_BINFILE_NAME_DST "pizzeria_out.bin"
#define PIZZERIA_TXTFILE_NAME_DST "pizzeria_out.txt"

#define EXIT -1

int menu();
int getChoiceFile();
int menu();


#endif 
