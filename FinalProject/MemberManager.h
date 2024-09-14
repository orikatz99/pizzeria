#ifndef __MEMBERMAN__
#define __MEMBERMAN__
#include "General.h"
#include "Customer.h"


typedef struct
{
	Customer* membersArr;
	int membersCount;

}MemberManager;

void		initMemberManager(MemberManager* memberManager);
int			addMember(MemberManager* memberManager);
void		printMember(const Customer* customer);
void		printMembersArr(const Customer* arr, int membersCount);
void		updatePoints(MemberManager* memberManager, const Customer* customer);
void		freeMemberManager(Customer* arr, int size);
int			writeMembersArrToTextFile(FILE* fp, const Customer* memberArr, const int count);
Customer* readMembersArrFromTextFile(FILE* fp, int* pCount);


#endif

