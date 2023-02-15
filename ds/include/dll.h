typedef struct node node_t;
typedef node_t *iterator_t;
typedef struct doubly_linked_list dll_t;

struct node
{
    node_t *prev;
    void *data;
    node_t *next;
};

struct doubly_linked_list
{
	node_t *front;
	node_t *back;
};
    

/*
* Count Description:
*	Counts the number of nodes in the linked list.
*
* @Params:
*	dll - pointer to the linkedlist.
*
* @Returns:
*	Returns the number of nodes in the linked list.
*	if "dll" is invalid then  - the behavior of the function is undefined.
*
* @Complexity
*	Time: O(N)
*/
size_t DLLCount(const dll_t *dll);

/*
* IsEmpty Description:
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
* Count Description:
*	Counts the number of nodes in the linked list.
*
* @Params:
*	dll - pointer to the linkedlist.
*
* @Returns:
*	Returns the number of nodes in the linked list.
*	if "dll" is invalid then  - the behavior of the function is undefined.
*
* @Complexity
*	Time: O(N)
*/
size_t DLLCount(const dll_t *dll);

/*
* Insert Description:
*	Inserts a new node with a given data value at a specified position in the DLL.
*
* @Params:
*
* @Returns:
*
* @Complexity
*	Time: O(1)
*/
iterator_t DLLInsert(iterator_t iterator, void *data);

/*
* Remove Description:
*	Removes a node from the DLL at a specified position.
*
* @Params:
*
* @Returns:
*
* @Complexity
*	Time: O(1)
*/
iterator_t DLLRemove(iterator_t iterator);

/*
* PushBack Description:
*	Adds a new node with a given data value to the end of the DLL.
*
* @Params:
*
* @Returns:
*
* @Complexity
*	Time: O(1)
*/
iterator_t DLLPushBack(dll_t *dll, void *data); /* Add to the end of the list */

/*
* PushFront Description:
*	Adds a new node with a given data value to the beginning of the DLL.
*
* @Params:
*
* @Returns:
*
* @Complexity
*	Time: O(1)
*/
iterator_t DLLPushFront(dll_t *dll, void *data);  

/*
* PopBack Description:
*	Removes the last node in the DLL.
*
* @Params:
*
* @Returns:
*
* @Complexity
*	Time: O(1)
*/
void PopBack(dll_t *dll);

/*
* PopFront Description:
*	Removes the first node in the DLL.
*
* @Params:
*
* @Returns:
*
* @Complexity
*	Time: O(1)
*/
void PopFront(dll_t *dll);

/*
* Find Description:
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
iterator_t DLLFind(iterator_t from, iterator_t to, is_match user_func, void *param);

/*
* MultiFind Description:
*	Execute the given function on a given part of the linked list (inclusive 'from' to exclusive 'to')
*   with a given parameter.
*	//Finds all nodes in the DLL containing a given data value and returns them as a list.
* @Params:
*	from - pointer to the start of the range in the linked list.
*	to - pointer to the end of the range in the linked list.
*	match_func - pointer to a given compare function.
*	param - paramter to compare to.
*
* @Returns:
*	returns a list of the matching nodes.
*       // In case of fail returns iterator to "to".
*       if "iterator" is invalid then - the behavior of the function is undefined
*
* @Complexity
*	Time: O(n)
*/
dll_t *MultiFind(dll_t *dll_dest, iterator_t from, iterator_t to, is_match user_func, void *param); 

/*
* ForEach Description:
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
*       0 if succeeded. 
*       if one of the operations of the action func fails returns value different from 0.
*       if "iterator" is invalid then - the behavior of the function is undefined.
*
* @Complexity
*	Time: O(n)
*/
int DLLForEach(iterator_t from, const iterator_t to, action_func user_func, void *param);

/*
* SetData Description:
*	sets the value of a node pointed by the given iterator.
*
* @Params:
*	iterator - iterator points to the node.
*	data 	 - the data to set to the node.
*
* @Returns:
*	void
*
* @Complexity
*	Time: O(1)
*/
void DLLSetData(const iterator_t iterator, void *data);

/*
* GetData Description:
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
* Splice Description:
*	Takes a range of nodes from another DLL and inserts them into
*	a specified position in the current DLL.

*Transfer all the elements of list x into another list at some position.
    Transfer only the element pointed by i from list x into the list at some position.
    Transfers the range [first, last) from list x into another list at some position.
* @Params:
*	
*
* @Returns:
*	
*       
*
* @Complexity
*	Time: O(1)
*/
iterator_t DLLSplice(iterator_t iter_dest, iterator_t src_from, iterator src_to);  

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


    MultiFind: 
    ForEach: Performs a given function on each node in the DLL.
    SetData: Sets the data value of a given node in the DLL.
    GetData: Gets the data value of a given node in the DLL.
    BeginIter: Returns an iterator pointing to the first node in the DLL.
    EndIter: Returns an iterator pointing to the last node in the DLL.
    NextIter: Moves an iterator to the next node in the DLL.
    PrevIter: Moves an iterator to the previous node in the DLL.
    IsSameIter: Checks if two iterators are pointing to the same node.
    Splice: Takes a range of nodes from another DLL and inserts them into a specified position in the current DLL.


