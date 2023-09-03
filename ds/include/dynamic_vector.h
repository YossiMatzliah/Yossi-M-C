#ifndef __DYNAMIC_VECTOR_H__
#define __DYNAMIC_VECTOR_H__

#include <stdio.h> /* size_t, printf */

typedef struct vector vector_t;

#define GROWTH_FACTOR (2)
#define SHRINK_THRESHOLD (4)

/*
* VectorCreate Description:
*	creates new Dynamic Vector data structure.
*	the vector will be able to contain capacity number of elements of size element_size.
*
* @Params:
*	capacity 	 - number of possible elements in the vector.
*	element_size - size of one element in bytes.
*
* @Returns:
*	pointer to a vector that can be used to access vector functions. NULL if failed.
*
* @Complexity
*	Time: Amortized O(1)
*/
vector_t *VectorCreate(size_t capacity, size_t element_size);

/*
* VectorDestroy Description:
*	realeases allocated memory for vector and all it's data.
*
* @Params:
*	vector - pointer to a vector to destroy.
*
* @Returns:
*	None.
*
* @Complexity
*	Time: O(1)
*/
void VectorDestroy(vector_t *vector);

/* 
* VectorPushItem Description:
* 	push an element to the end of the vector
*	if pushing to last avaiable space, the capacity will grow according to an internal growth factor.
*	Incase the realocatin failed the element will still be pushed to the vector. 
*
* @param:
*	vector 	- pointer to the vector to add an item to.	 
*	element - A pointer to the item to add.
*			
* @Return
*	Returns 0 / 1 if reallocation of additional memory succeeded / failed accordingly
*	if failed, additional calls to this function will result in undefined behavior.
*
* @Complexity
*	Time: Amortized O(n) if reallocation is required / Amortized O(1) if not
*/
int VectorPushBack(vector_t *vector, const void *element);

/* 
* PopBack Description
*	pops an element from the end of the vector
*	the capacity might be reduced by an internal growth factor.
*	popping an element from an empty vector causes undefiend behaviour.
*
* @param:
*	vector - pointer to the vector.	 
*			
* @Return
*	None.
*
* @Complexity
*	Time: Amortized O(n) if reallocation is required / Amortized O(1) if not
*/
void VectorPopBack(vector_t *vector);

/* 
* VectorGetAccessToElement Description:
* 	Returns a pointer to the element by a given index.
*	The pointer returned by the function might be invalidated by any Pop or Push actions.
*
* @param:
*	vector - pointer to the vector to read the element from. 
*   index  - Index to the element in vector to read.
*			
* @Return
*	A pointer to the element stored in a given index. 
*
* @Complexity
*	Time: O(1)
*/
void *VectorGetAccessToElement(const vector_t *vector, size_t index);

/* 
* VectorReserve Description:
* 	Increasing the capacity of the vector to the given 'reserve'.
*	if the given reserve size is less than the current capacity nothing will happen.
*
* @param:
*	vector 		 -  The vector to write the item. 
*	reserve_size -  the new capacity to set the vector to.
*
* @Return
*	returns 0 if the allocation was successful. 
*	returns 1 if failed to increase size.
*
* @Complexity
*	Time: O(n)
*/
int VectorReserve(vector_t *vector, size_t reserve_size);

/* 
* VectorShrinkToSize Description:
* Shrinks the capacity of a vector to the current number of elements + 1.
*
* @param:
*	vector - pointer to a vector to shrink to size.
*
* @Return
*	returns 0 if the allocation was successful, 
*	returns 1 if failed to shrink to size.
*
* @Complexity
*	Time: O(n)
*/
int VectorShrinkToSize(vector_t *vector);

/* 
* VectorIsEmpty Description:
* 	Checks if the Vector is empty and returns a feedback to the user.
*
* @param:
*	vector - The vector to check if is empty. 
*
* @Return
*	returns 1 if empty.
*	returns 0 if not.
*
* @Complexity
*	Time: O(n)
*/
int VectorIsEmpty(const vector_t *vector);

/*
* VectorCapacity Description:
* 	Checks the vector current maximum capacity.
*
* @param:
*	vector - The vector to check it's capacity 
*
* @Return
*	size_t variable represents the maximum number of elements the vector can currently store.
*
* @Complexity
*	Time: O(1)
*/
size_t VectorCapacity(const vector_t *vector);

/*
* VectorSize Description:
* 	Checks the vector current number of elements in the vector.
*
* @param:
*	vector - The vector to check it's size(number of elements). 
*
* @Return
*	size_t variable represents the current number of elements.
*
* @Complexity
*	Time: O(1)
*/
size_t VectorSize(const vector_t *vector);


/*
VectorInsertItem		// Item is inserted at a given index, other elements move 
CreateArray(size_t initial_capacity)
DestroyArray	// Frees element	

***Advanced***

ReverseArray	// Reverses elements in array 
ArrayToString	// Converts array to a string 
*/

#endif
