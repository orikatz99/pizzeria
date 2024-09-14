#ifndef __GENERAL__
#define __GENERAL__

#define MAX_TOP 4

#define SMALL 10
#define MEDIUM 16
#define LARGE 22

#define P_SMALL 30
#define P_MEDIUM 40
#define P_LARGE 50

#define P_OLIVE 2
#define P_MUSHROOM 6
#define P_CORN 3
#define P_TOMATO 5

#define P_GLUTEN_FREE 12
#define P_VEGAN 5
#define P_WHOLE_WHEAT 10

#define MAX_STR_LEN 255

#define FALSE 0
#define TRUE 1

#define MAX_ID 9

#define		EMPTY	0x7FFFFFFF

//macros//
#define PRINT(s)	printf(#s"\n");
#define CHECK_RETURN_FALSE(ptr) {if(!ptr) return 0;} 
#define CLOSE_RETURN_FALSE(fp) do {\
                                fclose(fp);\
                                return 0;\
                              } while(0)
#define PRINT(s)	printf(#s"\n");
//macros//

typedef void* DATA;// a type for data (easy to change)
typedef enum { False, True } BOOL;	// a boolean type

// Node
typedef struct node
{
    DATA			key;
    struct node* next;
}NODE;

//char* myGets(char* buffer, int size);
//char* fMyGets(FILE* file, char* buffer, int size);

char* myGets(char* buffer, int size, FILE* source);

char* getStrExactName(const char* msg);
char* getDynStr(char* str);
void clearSpaces(char* str);
void changeToBigLetter(char* str);
void fixString(char* str);
int isSameStr(char* str1, char* str2);
int getTypeFromUser(int size, char* arr[]);
void generalArrayFunction(const void* arr, int size, int typeSize, void f(void* element));

#endif 

