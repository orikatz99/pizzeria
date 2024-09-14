#include <stdio.h>
#include "Pizzeria.h"


//Writing to a binary file

int		savePizzeriaToFile(const Pizzeria* pizzeria, const char* fileName);
int		writeNameToBFile(FILE* fp, const char* string);
int		writeAddressToBFile(FILE* fp, const Address* address);
int		writePizzaToBFile(FILE* fp, const Pizza* pizza);
int		writePizzaListToBFile(FILE* fp, const LIST* pizzaList);
int		writeCustomerToBFile(FILE* fp, const Customer* customer);
int		writeMembersArrToBFile(FILE* fp, const Customer* membersArr, const int count);
int		writeCouponToBFile(FILE* fp, const Coupon* coupon);
int		writeCouponsArrToBFile(FILE* fp, Coupon** arrCoupons, int count);
int 	writeOrderToBFile(FILE* fp, const Order* order);
int		writeOrdersArrToBFile(FILE* fp, Order* orderArr, int count);

//Reading from a binary file

int		  initPizzeriaFromFile(Pizzeria* pizzeria, const char* fileName);
int		  readNameFromBFile(FILE* fp, char** string);
int		  readAddressFromBFile(FILE* fp, Address* address);
int		  readPizzaFromBFile(FILE* fp, Pizza* pizza);
int		  readPizzaListFromBFile(FILE* fp, LIST* pizzaList);
int		  readCustomerFromBFile(FILE* fp, Customer* customer);
Customer* readMembersArrFromBFile(FILE* fp, int* pCount);
int		  readCouponFromBFile(FILE* fp, Coupon* coupon);
Coupon** readCouponsArrFromBFile(FILE* fp, int* pCount);
int 	  readOrderFromBFile(FILE* fp, Order* order);
Order* readOrdersArrFromBFile(FILE* fp, int* pCount);