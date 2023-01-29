/********************************
*	Developper: Yossi Matzliah	*
*	Date: 		29/01/2023		*
*	Reviewer:	Avri			*
********************************/

#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <stdio.h> /*printf*/
#include <string.h> /*memcpy*/
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
	stack->top = -1;
	stack->capacity = capacity;
	stack->i_size = item_size;
    
	if (NULL == stack)
	{
		printf ("Memory allocation for the satck faild \n");
		return NULL;
	}

	if (NULL == stack->data)
	{
		printf ("Memory allocation for the data array faild \n");
		return NULL;
	}
	return stack;
}

void StackDestroy(stack_t *stack)
{
	free(stack->data);
	free(stack);
}

size_t StackSize(const stack_t *stack)
{
	return (stack->top + 1);
}

int StackIsEmpty(const stack_t *stack)
{
	if (-1 == stack->top)
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
	assert(stack->top != stack->capacity);
 
	++stack->top;
	memcpy((char*)stack->data + (stack->top * stack->i_size), item, stack->i_size);   
}

void* StackPeek(const stack_t *stack)
{
	assert(NULL != stack);
	assert(!StackIsEmpty(stack));
	
	return (char*)stack->data + (stack->top * stack->i_size);
}
