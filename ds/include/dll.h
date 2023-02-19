/**************************************
*	Developer :	Yossi Matzliah        *
*	Reviewer  :	Oran Freidin		  *
*	Date      : 18/02/2023			  *
**************************************/

#ifndef __ILRD_OL139_40_DLL_H__
#define __ILRD_OL139_40_DLL_H__

#include <stddef.h> /* size_t */

typedef struct node *iterator_t;
typedef struct doubly_linked_list dll_t;

typedef int (*action_func_t)(void *, void *); 
typedef int (*is_match_t)(void *, const void *);

/*******************************************************/

/*
* DLLCreate description:
* 	Creates a doubly linked list
*
* @param:
* 	none
* 
* @return:
* 	Returns a pointer to the created doubly likned list.
*
* complexity
* 	Time: O(1)
*/
dll_t *DLLCreate();

/*
* DLLDestroy description:
* 	Destroys doubly linked list
*
* @param:
* 	dll - Pointer to doubly linked list
* 
* @return:
* 	void
*
* complexity
* 	Time: O(1)
*/
void DLLDestroy(dll_t *dll);

/*
* DLLIsEmpty Description:
*	Checks if the linked list is empty.
*
* @Params:
*	dll - pointer to the linked list to be checked whether it's empty.
*
* @Returns:
*	1 or 0 if the linked list is empty or not, respectively.
*
* @Complexity
*	Time: O(1)
*/
int DLLIsEmpty(const dll_t *dll);

/*
* DLLCount Description:
*	Counts the number of nodes in the linked list.
*
* @Params:
*	dll - pointer to the linkedlist.
*		NOTE: if "dll" is invalid then - the behavior of the function is undefined.
*	
* @Returns:
*	Returns the number of nodes in the linked list.	
*
* @Complexity
*	Time: O(n)
*/
size_t DLLCount(const dll_t *dll);

/*
* DLLInsert Description:
*	Inserts a new node with a given data value at a specified position in the DLL.
*
* @Params:
*	iterator - pointer to the linked list.
*	data - pointer to the value for the inserted node.
*
* @Returns:
*	returns the iterator variable to the inserted node.
*	In case of fail returns iterator to the tail node.
*	if "iterator" is invalid, the behavior of the function is undefined.
*
* @Complexity
*	Time: O(1)
*/
iterator_t DLLInsert(iterator_t iterator, void *data);

/*
*  DLLRemove Description:
*	Removes a node pointed by the given iterator.
*
* @Params:
*	iterator - iterator to the node to be removed.
*
* @Returns:
*	returns an iterator to the next node in the linked list.
*   if "iterator" is invalid, the behavior of the function is undefined
*   Iterator invalidation can occur if the same iterator is used after the function has returned
* 	if the list is empty the behavior is undefined.
*	
* @Complexity
*	Time: O(1)
*/
iterator_t DLLRemove(iterator_t iterator);

/*
*  DLLPushBack Description:
*  	Inserts a node at the end of list.  
*
* @Params:
*	dll - Pointer to doubly linked list
*	data - Pointer to data to be inserted
*
* @Returns:
*	returns an iterator to the node that was inserted.
*
* @Complexity
*	Time: O(1)
*/
iterator_t DLLPushBack(dll_t *dll, void *data); /* Add to the end of the list */

/*
*  DLLPushFront Description:
*  	Inserts a node at beginning of list
*
* @Params:
*	dll - Pointer to doubly linked list
*	data - pointer to data to be inserted
*
* @Returns:
*	returns an iterator to the node that was inserted
*	
* @Complexity
*	Time: O(1)
*/
iterator_t DLLPushFront(dll_t *dll, void *data);  

/*
*  DLLPopBack Description:
*  	Removes the last node in the list and returns a pointer to the data saved in removed node
*
* @Params:
*	dll - Pointer to doubly linked list
*
* @Returns:
*	returns pointer to data in removed node
*	if the list is empty the behavior is undefined.
*	
* @Complexity
*	Time: O(1)
*/
void *DLLPopBack(dll_t *dll);

/*
*  DLLPopFront Description:
* 	 Removes the last node in the list and returns a pointer to the data saved in removed node
*
* @Params:
*	dll - Pointer to doubly linked list
*
* @Returns:
*	returns pointer to data in removed node
*	if the list is empty the behavior is undefined.
*	
* @Complexity
*	Time: O(1)
*/
void *DLLPopFront(dll_t *dll);

/*
* DLLFind Description:
*	Execute the given function on a given part of the linked list (inclusive 'from' to exclusive 'to')
*   with a given parameter.
*
* @Params:
*	from - pointer to the start of the range in the linked list.
*	to - pointer to the end of the range in the linked list.
*	match_func - pointer to a given compare function.
*	param - paramter to compare to.
*
* @Returns:
*	returns an iterator to the matching node.
*       In case of fail returns iterator to "to".
*       if "iterator" is invalid then - the behavior of the function is undefined
*
* @Complexity
*	Time: O(n)
*/
iterator_t DLLFind(iterator_t from, iterator_t to, is_match_t user_func, void *param);

/*
* DLLMultiFind Description:
* 	Finds all nodes (inclusive 'from' to exclusive 'to') in the DLL containing a given data value and
*	returns them as a list to the user's given dll. 
*
* @Params:
*	dll_dest - pointer to an empty list given by the user
*	from - pointer to the start of the range in the linked list.
*	to - pointer to the end of the range in the linked list.
*	match_func - pointer to a given compare function.
*	param - paramter to compare to.
*
* @Returns:
*	returns a linked list of all iterators that were found by function
*   In case of were no matches were found- returns dest as it been recieved.
*	In case of failure returns NULL.
*   if "iterator" is invalid then - the behavior of the function is undefined
*
* @Complexity
*	Time: O(n)
*/
dll_t *DLLMultiFind(dll_t *dll_dest, iterator_t from, iterator_t to, is_match_t user_func, void *param); 

/*
* DLLForEach Description:
*	Execute the given function on a given part of the linked list (inclusive 'from' to exclusive 'to') 
	with a given parameter.
*
* @Params:
*	from - pointer to the start of the range in the linked list.
*	to - pointer to the end of the range in the linked list.
*	action_func - pointer to a given action function sent by user.
*	param - paramter for the action function.
*
* @Returns:
*	returns action_function status. 
*	0 if succeeded. 
*	if one of the operations of the action func fails returns value different from 0.
*	if "iterator" is invalid then - the behavior of the function is undefined.
*
* @Complexity
*	Time: O(n)
*/
int DLLForEach(iterator_t from, const iterator_t to, action_func_t user_func, void *param);

/*
* DLLSetData Description:
*	sets the value of a node pointed by the given iterator.
*
* @Params:
*	iterator - iterator points to the node.
*	data 	 - the data to set to the node.
*
* @Returns:
*	none
*
* @Complexity
*	Time: O(1)
*/
void DLLSetData(const iterator_t iterator, void *data);

/*
* DLLGetData Description:
*	gets the value of a node pointed by the given iterator.
*
* @Params:
*	iterator - iterator  points to a node.
*
* @Returns:
*	returns void * to the data
*       if "iterator" is invalid then - the behavior of the function is undefined.
*
* @Complexity
*	Time: O(1)
*/
void *DLLGetData(iterator_t iterator);

/*
* DLLSplice Description:
*	Takes a range of nodes from another DLL and inserts them before a specified position in the current DLL(before dest)
*
* @Params:
*	dest - iterator points to a node in destination linked list.
*	src_from - iterator points to first node in required range of source linked list. (included)
*	src_to - iterator points to last node in required range of source linked list. (excluded)
*
* @Returns:
*	returns iterator to beginning of destination linked lists
*
* @Complexity
*	Time: O(1)
*/
iterator_t DLLSplice(iterator_t iter_dest, iterator_t src_from, iterator_t src_to);  

/*
* BeginIter Description:
*	returns an iterator to the start of the linked list
*
* @Params:
*	dll - pointer to the linked list.
*
* @Returns:
*	returns an iterator to the first node
*		if "dll" is invalid then the behavior of the function is undefined
*
* @Complexity
*	Time: O(1)
*/
iterator_t DLLBeginIter(const dll_t *dll);

/*
* NextIter Description:
*	returns the iterator that points to the next node.
*
* @Params:
*	iterator - pointer to the current node.
*       if "iterator" is invalid then  the behavior of the function is undefined
*
* @Returns:
*	returns the iterator that points to the next node.
*
* @Complexity
*	Time: O(1)
*/
iterator_t DLLNextIter(const iterator_t iterator);

/*
* PrevIter Description:
*	returns the iterator that points to the previous node.
*
* @Params:
*	iterator - pointer to the current node.
*       if "iterator" is invalid then  the behavior of the function is undefined
*
* @Returns:
*	returns the iterator that points to the previous node.
*
* @Complexity
*	Time: O(1)
*/
iterator_t DLLPrevIter(const iterator_t iterator);

/*
* EndIter Description:
*	returns the iterator that points to the end of the linked list.
*
* @Params:
*	dll - pointer to the linked list.
*
* @Returns:
*	returns the iterator that points to the end of the linked list.
*       if "dll" is invalid then the behavior of the function is undefined
*
* @Complexity
*	Time: O(1)
*/
iterator_t DLLEndIter(const dll_t *dll);

/*
* IsSameIter Description:
*	Compares two iterators
*
* @Params:
*	iter1 - iterator points to a node in a linked list.
*	iter2 - iterator points to a node in a linked list.
*
* @Returns:
*	returns 1 if they are equal.
	returns 0 otherwise.
*
* @Complexity
*	Time: O(1)
*/
int DLLIsSameIter(const iterator_t iter1, const iterator_t iter2);

#endif

