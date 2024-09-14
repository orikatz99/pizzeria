#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
#include "MemberManager.h"

void initMemberManager(MemberManager* memberManager)
{
	memberManager->membersArr = NULL;
	memberManager->membersCount = 0;
}

int addMember(MemberManager* memberManager)
{
	printf("Enter your details to enter the database of club members\n");
	memberManager->membersArr = (Customer*)realloc(memberManager->membersArr, (memberManager->membersCount + 1) * sizeof(Customer));//memory allocation
	if (!memberManager->membersArr)//Checking if the memory allocation was successful
		return FALSE;
	initCustomer(&memberManager->membersArr[memberManager->membersCount]);
	int uniqe = isIdUniqe(memberManager->membersArr, memberManager->membersCount, memberManager->membersArr[memberManager->membersCount].id);
	while (uniqe != -1)
	{
		printf("Id already exists in system!\n");
		getId(&memberManager->membersArr[memberManager->membersCount]);
		uniqe = isIdUniqe(memberManager->membersArr, memberManager->membersCount, memberManager->membersArr[memberManager->membersCount].id);
	}

	memberManager->membersCount++;
	return TRUE;
}

void printMember(const Customer* customer)
{
	printCustomer(customer);
	printf("You have %d points\n", customer->points);
}

void printMembersArr(const Customer* arr, int size)
{
	printf("There are %d members\n", size);
	generalArrayFunction(arr, size, sizeof(*arr), printMember);
}

void updatePoints(MemberManager* memberManager, const Customer* customer)
{
	int i = isIdUniqe(memberManager->membersArr, memberManager->membersCount, customer->id);
	if (i != -1)
	{
		memberManager->membersArr[i].points = customer->points;
	}
}

void	freeMemberManager(Customer* arr, int size)
{
	generalArrayFunction(arr, size, sizeof(*arr), freeCustomerGeneral);
}

int		writeMembersArrToTextFile(FILE* fp, const Customer* memberArr, const int count)
{

	if (fprintf(fp, "%d\n", count) < 0)
		return 0;

	for (int i = 0; i < count; i++)
	{
		if (!writeCustomerToTextFile(fp, &memberArr[i]))
			return 0;
	}
	return 1;
}


Customer* readMembersArrFromTextFile(FILE* fp, int* pCount)
{
	Customer* memArr;

	if (fscanf(fp, "%d", pCount) != 1)
		return NULL;

	memArr = (Customer*)malloc(*pCount * sizeof(Customer));
	if (!memArr)
		return NULL;

	for (int i = 0; i < *pCount; i++)
		if (!readCustomerFromTextFile(fp, &memArr[i]))
		{
			freeMemberManager(memArr, *pCount);
			return NULL;
		}
	return memArr;

}


