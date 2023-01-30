/********************************
*	Developper: Yossi Matzliah	*
*	Date: 		29/01/2023		*
*	Reviewer:	Avri			*
********************************/

#include <stdio.h> /*printf*/
#include "/home/yossi/git/ds/include/stack.h"

static void TestStack();

int main()
{
	TestStack();
	return 0;
}
static void TestStack()
{
	int item1 = 1;
	int item2 = 2;
	int item3 = 3;
	int item4 = 4;
	size_t capacity1 = 4;
	size_t item_size1 = sizeof(item1);
	stack_t *stack1 = StackCreate(capacity1, item_size1);
    
	char item5 = 'a';
	char item6 = 'b';
	char item7 = 'c';
	size_t capacity2 = 3;
	size_t item_size2 = sizeof(item5);
	stack_t *stack2 = StackCreate(capacity2, item_size2);
    
	float item8 = 1.5;
	float item9 = 2.5;
	float item10 = 3.5;
	size_t capacity3 = 3;
	size_t item_size3 = sizeof(item8);
	stack_t *stack3 = StackCreate(capacity3, item_size3);
    
    
    printf("capacity of stack1 is: %lu\n", StackCapacity(stack1)); 
	StackPush(stack1, &item1);
	printf("%d is at the top of the stack1\n", *((int *)StackPeek(stack1)));
	StackPush(stack1, &item2);
	printf("%d is at the top of the stack1\n", *((int *)StackPeek(stack1)));
	StackPush(stack1, &item3);
	printf("%d is at the top of the stack1\n", *((int *)StackPeek(stack1)));
	StackPush(stack1, &item4);
	printf("%d is at the top of the stack1\n", *((int *)StackPeek(stack1)));
    printf("There are: %ld elements in the stack now(before pop). \n\n", StackSize(stack1));
    
	if (!StackIsEmpty(stack1))
	{
		StackPop(stack1);
	}
		
	printf("After one pop: %ld elements in the stack now. \n", StackSize(stack1));
	printf("%d is at the top of the stack(after one pop)\n\n", *((int *)StackPeek(stack1)));
		
	StackDestroy(stack1); 
	
	printf("capacity of stack2 is: %lu\n", StackCapacity(stack2)); 	
	StackPush(stack2, &item5);
	printf("%c is at the top of the stack2\n", *((char *)StackPeek(stack2)));
	StackPush(stack2, &item6);
	printf("%c is at the top of the stack2\n", *((char *)StackPeek(stack2)));
	StackPush(stack2, &item7);
	printf("%c is at the top of the stack2\n", *((char *)StackPeek(stack2)));
		
	if (!StackIsEmpty(stack2))
	{
		StackPop(stack2);
	}    
	
	if (!StackIsEmpty(stack2))
	{
		StackPop(stack2);
	}    
	
	printf("After two pops: %ld elements in the stack2 now. \n", StackSize(stack2));
	printf("%c is at the top of the stack2\n\n", *((char *)StackPeek(stack2)));
			
	StackDestroy(stack2); 
	
	printf("capacity of stack3 is: %lu\n", StackCapacity(stack3)); 	
	StackPush(stack3, &item8);
	printf("%.1f is at the top of the stack3\n", *((float *)StackPeek(stack3)));
	StackPush(stack3, &item9);
	printf("%.1f is at the top of the stack3\n", *((float *)StackPeek(stack3)));
	StackPush(stack3, &item10);
	printf("%.1f is at the top of the stack3\n", *((float *)StackPeek(stack3)));
    
	if (!StackIsEmpty(stack3))
	{
		StackPop(stack3);
	}
	
	printf("After one pop and a peek: %ld elements in the stack3 now. \n", StackSize(stack3));
	printf("%.1f is at the top of the stack3\n\n", *((float *)StackPeek(stack3)));
	
	StackDestroy(stack3); 
}


