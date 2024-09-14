#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "General.h"


char* myGets(char* buffer, int size, FILE* source)
{
	char* ok;
	if (buffer != NULL && size > 0)
	{
		do {
			ok = fgets(buffer, size, source);
		} while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
		if (ok)
		{
			char* back = buffer + strlen(buffer);
			//trim end spaces
			while ((buffer < back) && (isspace(*--back)));
			*(back + 1) = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}

char* getStrExactName(const char* msg)
{
	char* str;
	char temp[MAX_STR_LEN];
	printf("%s\n", msg);
	myGets(temp, MAX_STR_LEN, stdin);

	str = getDynStr(temp);
	return str;
}

char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr)
		return NULL;

	strcpy(theStr, str);
	return theStr;
}

void clearSpaces(char* str) //clear spaces in the begining of a string
{
	int noSpace = 1;
	char* pLook = str;
	char* pWrite = str;


	while (*pLook && isspace(*pLook)) //remove leading spaces
	{
		pLook++;
	}

	while (*pLook)  //copy non-space characters to the start of the string
	{
		if (!isspace(*pLook))
		{
			*pWrite++ = *pLook++;
			noSpace = 1;
		}
		else if (isspace(*pLook) && noSpace)
		{
			*pWrite++ = *pLook++;
			noSpace = 0;
		}
		else
		{
			pLook++;
		}
	}
	pWrite--;
	*(pWrite + 1) = '\0';
}

void changeToBigLetter(char* str) //changes every word's first letter to a big letter
{
	while (*str)
	{
		while (*str && isspace(*str)) //space-not a word
		{
			str++;
		}
		if (*str) //first letter in word - change to big letter
		{
			*str = toupper(*str);
		}
		while (*str && !isspace(*str)) //still the same word, dont make changes
		{
			str++;
		}

	}
}

void fixString(char* str) //calls all the "fixing" functions to fix a string by the rules given in the assignment
{
	clearSpaces(str);
	changeToBigLetter(str);
}

int isSameStr(char* str1, char* str2) //checks if two strings are the same by using strcmp
{
	if ((strcmp(str1, str2)) == 0)
		return TRUE;
	else
		return FALSE;
}

int getTypeFromUser(int size, char* arr[])
{
	int i, t;
	do {
		printf("\nPlease enter one of the following types\n");
		for (i = 0; i < size; i++)
			printf("%d for %s\n", i, arr[i]);
		scanf("%d", &t);
	} while (t < 0 || t >= size);//Checks that the selected type is one of the existing types
	return t;
}

void generalArrayFunction(const void* arr, int size, int typeSize, void f(void* element))
{
	void* element;
	for (int i = 0; i < size; i++)
	{
		element = (char*)arr + i * typeSize;
		f(element);
	}
}