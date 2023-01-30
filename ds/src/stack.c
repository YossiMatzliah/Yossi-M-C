/********************************
*	Developper: Yossi Matzliah	*
*	Date: 		29/01/2023		*
*	Reviewer:	Avri			*
********************************/

#include <stdlib.h> 	/* malloc, free */
#include <assert.h> 	/* assert */
#include <stdio.h> 		/*printf, size_t */
#include <string.h> 	/* memcpy */
#include "/home/yossi/git/ds/include/stack.h"

struct stack
{
	void *data;
	long top;
	long capacity;
	size_t i_size;
};

stack_t *StackCreate(size_t capacity, size_t item_size)
{
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
	stack->data = malloc(capacity * item_size);
	
	if (NULL == stack)
	{
		printf ("Memory allocation for the satck failed \n");
		return NULL;
	}

	if (NULL == stack->data)
	{
		printf ("Memory allocation for the data array failed \n");
		return NULL;
	}
	
	stack->top = 0;
	stack->capacity = capacity;
	stack->i_size = item_size;
	
	return stack;
}

void StackDestroy(stack_t *stack)
{
	free(stack->data);
	free(stack);
}

size_t StackSize(const stack_t *stack)
{
	return (stack->top);
}

int StackIsEmpty(const stack_t *stack)
{
	if (0 == stack->top)
	{
		return 1;
	}
	
	else
	{
		return 0;
	}
}

void StackPop(stack_t *stack)
{
	assert(NULL != stack);
	assert(!StackIsEmpty(stack));
	
	--stack->top;
}

void StackPush(stack_t *stack, const void *item)
{
 
	assert(NULL != stack);
	assert(NULL != item);
	assert(stack->top < stack->capacity);
 
	++stack->top;
	memcpy((char*)stack->data + (stack->top * stack->i_size), item, stack->i_size);   
}

void* StackPeek(const stack_t *stack)
{
	assert(NULL != stack);
	assert(!StackIsEmpty(stack));
	
	return (char*)stack->data + (stack->top * stack->i_size);
}

size_t StackCapacity(const stack_t *stack)
{
	return stack->capacity;
}

