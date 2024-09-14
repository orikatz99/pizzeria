/********************************************/
/*   list.h                                 */
/*   a dynamic  linked list with a header   */
/********************************************/


#ifndef _LIST_
#define _LIST_

#include "General.h"


/*** Definitions ***/

// List
typedef struct
{
	NODE head;
}LIST;


/*** Function prototypes ***/

BOOL L_init(LIST* pList);					// create new list

NODE* L_insert(NODE* pNode, DATA Value);	// add new node after *pNode

BOOL L_delete(NODE* pNode);				// erase node after *pNode

const NODE* L_find(const NODE* pNode, DATA Value);

BOOL L_free(LIST* pList);					// free list memory

int L_print(const LIST* pList, void(*print)(const void*));					// print the list content

#endif
