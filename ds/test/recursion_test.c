/**************************************
*	Developer :	Yossi Matzliah        *
*	Reviewer  :	"MedalCollector" Oran *
*	Date      : 18/03/2023			  *
**************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc, free */
#include <string.h>	/* str funcs */

#include "recursion.h"

#define U_LINE 	"\033[1m\033[4m"
#define RED   	"\033[1m\033[41m\x1B[30m"
#define GRN   	"\033[1m\033[42m\x1B[30m"
#define RESET 	"\033[0m"

#define TRUE 	(1)
#define FALSE 	(0)
#define FAILURE (1)
#define SUCCESS (0)

#define PRINT_TEST(x) ((TRUE == (x)) ? printf(GRN"SUCCESS!"RESET"\n\n") : printf(RED"FAILURE!, line %d"RESET"\n\n", __LINE__))

#define NEW_LINE printf("\n")

/*****************************************************************/

static void TestFibonacci();
static void TestFlipList();
static void TestSortUnsortedStack();
static void TestStrLenRec();
static void TestStrCmpRec();
static void TestStrCpyRec();
static void TestStrCatRec();
static void TestStrStrRec();

/*****************************************************************/

int main()
{
	TestFibonacci();
	TestFlipList();
	TestSortUnsortedStack();
	TestStrLenRec();
	TestStrCmpRec();
	TestStrCpyRec();
	TestStrCatRec();
	TestStrStrRec();
	
	return 0;
}

static void TestFibonacci()
{
	int fib = 4;
	int fib_exp = 2;
	int fib_recursive = 0;
	int fib_iterative = 0;
	
	printf(U_LINE"Fibonacci Test:\n"RESET);
	
	fib_iterative = FiboIter(fib);
	fib_recursive = FiboRec(fib);
	
	PRINT_TEST(fib_recursive == fib_iterative);		
	PRINT_TEST(fib_recursive == fib_exp);
	
	fib = 10;
	fib_exp = 34;
	
	fib_iterative = FiboIter(fib);
	fib_recursive = FiboRec(fib);
	
	PRINT_TEST(fib_recursive == fib_iterative);		
	PRINT_TEST(fib_recursive == fib_exp);
}

static void TestFlipList()
{
	
	int a = 1;
	int b = 2;
	int c = 3;
	int status = SUCCESS;
	
	node_t *iterator = {NULL};
	node_t head = {0};
	node_t node_1 = {0};
	node_t node_2 = {0};
	
	head.data = (void *)&a;
	node_1.data = (void *)&b;
	node_2.data = (void *)&c;
	
	head.next = &node_1;
	node_1.next = &node_2;
	node_2.next = NULL;

	printf(U_LINE"\nFlip List Test:\n"RESET);
	
	iterator = &head;
	
	while (NULL != iterator)
	{
		printf("%d-->", *(int *)(iterator->data));
		iterator = iterator->next;
	}
	printf("NULL\n");
	
	iterator = FlipList(&head);
	if (iterator->data != node_2.data)
	{
		status = FAILURE;
	}
	
	if (iterator->next->data != node_1.data)
	{
		status = FAILURE;
	}
	
	if (iterator->next->next->data != head.data)
	{
		status = FAILURE;
	}
	
	if (NULL != iterator->next->next->next)
	{
		status = FAILURE;
	}
	
	while (NULL != iterator)
	{
		printf("%d-->", *(int *)(iterator->data));
		iterator = iterator->next;
	}
	printf("NULL\n");
	
	PRINT_TEST(SUCCESS == status);
}

static void TestSortUnsortedStack()
{
	stack_t *stack = StackCreate(6, sizeof(int));
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;
	int status = 0;
	int i = 0;
	
	printf(U_LINE"\nSort Stack Test:\n"RESET);

	StackPush(stack, (void *)&num3);
	StackPush(stack, (void *)&num4);
	StackPush(stack, (void *)&num5);
	StackPush(stack, (void *)&num1);
	StackPush(stack, (void *)&num2);
	
	SortUnsortedStack(stack);
	
	for (i = 5; 0 < i; --i)
	{
		if (i != *(int *)StackPeek(stack))
		{
			status = FAILURE;
		}
		
		StackPop(stack);
	}
	
	StackDestroy(stack);
	
	PRINT_TEST(SUCCESS == status);
}

static void TestStrLenRec()
{
	char *str = "abcdef";
	size_t my_len = 0;
	size_t lib_len = 0;
	
	printf(U_LINE"\nRecursive StrLen Test:\n"RESET);
	
	my_len = StrLenRec(str);
	lib_len = strlen(str);
	
	PRINT_TEST(my_len == lib_len);
}

static void TestStrCmpRec()
{
	char *str = "abcdef";
	char *str_2 = "bcdefb";
	int my_cmp = 0;
	int lib_cmp = 0;
	
	printf(U_LINE"\nRecursive StrCmp Test:\n"RESET);
	
	my_cmp = StrCmpRec(str, str_2);
	lib_cmp = strcmp(str, str_2);
	
	PRINT_TEST(my_cmp == lib_cmp);
}

static void TestStrCpyRec()
{
	char *src = "abcde";
	char my_dest[6] = {"0"};
	char lib_dest[6] = {"0"};
	
	printf(U_LINE"\nRecursive StrCpy Test:\n"RESET);
	
	StrCpyRec(my_dest, src);
	PRINT_TEST(0 == StrCmpRec(my_dest, src));
	strcpy(lib_dest, src);
	PRINT_TEST(0 == StrCmpRec(lib_dest, my_dest));
}

static void TestStrCatRec()
{
	char *src = "WORLD";
	char my_dest[12] = "HELLO ";
	char lib_dest[12] = "HELLO ";
	
	printf(U_LINE"\nRecursive StrCat Test:\n"RESET);
	
	printf("Src is: %s\n", src);
	printf("My dest is: %s\n", my_dest);
	StrCatRec(my_dest, src);
	printf("After concatenate:\nMy dest is: %s\n", my_dest);
	strcat(lib_dest, src);
	PRINT_TEST(0 == StrCmpRec(lib_dest, my_dest));
}

static void TestStrStrRec()
{
	char *haystack = "HELLO WORLD";
	char *my_needle = "WORLD";
	char *lib_needle = "WORLD";
	char *my_needle_ptr = NULL;
	char *lib_needle_ptr = NULL;
	
	printf(U_LINE"\nRecursive StrStr Test:\n"RESET);
	
	my_needle_ptr = StrStrRec(haystack, my_needle);
	lib_needle_ptr  = strstr(haystack, lib_needle);
	
	PRINT_TEST(0 == StrCmpRec(lib_needle_ptr, my_needle_ptr));
}

