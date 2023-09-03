#ifndef __STACK_H__
#define __STACK_H__

/*
#This is an implementation of Stack using an array
#TOP is inintialized to 0 and get updated with every operation
#The size of the stack is decided by the user and passed to StackCreate(capacity, item size)

**************Limitation**************
#poping an empty stack will result an error
#pushing to full stack will result an error

**************basic instructions**************
check the stack current capacity before executing a command

**************Test function provided with basic implementations**************
*/

typedef struct stack stack_t;

/* 
* Description: StackCreate - create new stack of type struct stack_t
* @params:
* 	The capacity of the stack (num_of_elements) and item_size(in bytes) 
* @return:
* 	stack_t pointer
*/
stack_t *StackCreate(size_t capacity, size_t item_size);

/* 
* Description: StackDestroy - desroy (free) the stack of type struct stack_t
* @params:
* 	pointer to the stack struct 
* @return:
* 	void
*/
void StackDestroy(stack_t *stack);

/* 
* Description: StackPush - push element to the top of the stack
* @params:
* 	pointer to the stack struct and pointer to the item you want to push 
*	pushing when full on capacity could cause undefiend behaviour.
* @return:
*	void
*/
void StackPush(stack_t *, const void *item);

/* 
* Description: StackPop - pops out an element from the stack
* @params:
* 	pointer to the stack struct 
*	popping when stack is empty could cause undefiend behaviour.
* @return:
*	void
*/
void StackPop(stack_t *);

/* 
* Description: StaclPeek - get a pointer to the top stack element
* @params:
* 	const pointer to the stack struct 
*	peeking when stack is empty could cause undefiend behaviour.
* @return:
* 	void
*/
void *StackPeek(const stack_t *);

/* 
* Description: StackIsEmpty - check if the stack is in Underflow state or not
* @params:
*	const pointer to the stack struct
* @return:
*	int (0 : false, 1 : true)
*/
int StackIsEmpty(const stack_t *);

/* 
* Description: StackSize - the current size of the stack in bytes
* @params:
*	const pointer to the stack struct
* @return:
*	size_t with number of items
*/
size_t StackSize(const stack_t *);

/* 
* Description: StackCapacity - return the stack current capacity elements
* @params:
* 	const pointer to the stack struct
* @return:
* size_t with the capacity
*/
size_t StackCapacity(const stack_t *);

#endif



