/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	????				*
*	Date      : ?/04/2023			*
************************************/

#include <stdio.h>	

#include "heap.h"

#define U_LINE 	"\033[1m\033[4m"
#define RED   	"\033[1m\033[41m\x1B[30m"
#define GRN   	"\033[1m\033[42m\x1B[30m"
#define RESET 	"\033[0m"

#define TRUE 	(1)
#define FALSE 	(0)
#define SUCCESS (0)
#define FAILURE (1)

#define PRINT_TEST(x) ((TRUE == (x)) ? printf(GRN"SUCCESS!"RESET"\n\n") : printf(RED"FAILURE!, line %d"RESET"\n\n", __LINE__))

#define NEW_LINE printf("\n")





/*****************************************************************/

int main();

static void TestHeapCreateDestroy();
static void TestHeapPush();

int CompareFunc(const void *data1, const void *data2);

/*****************************************************************/

int main()
{
	TestHeapCreateDestroy();
	TestHeapPush();
	
	return 0;
}

static void TestHeapCreateDestroy()
{
	heap_t *test_heap = NULL;

	printf(U_LINE"Test Heap Create:\n\n"RESET);

	test_heap = HeapCreate(CompareFunc);

	PRINT_TEST(NULL != test_heap);
	PRINT_TEST(TRUE == HeapIsEmpty(test_heap));

	HeapDestroy(test_heap);
}

static void TestHeapPush()
{
	heap_t *test_heap = NULL;
	size_t data_1 = 5;
	size_t data_2 = 10;
	size_t data_3 = 3;
	size_t data_4 = 8;
	size_t heap_size = 0;

	printf(U_LINE"\nTest Heap Push:\n\n"RESET);

	test_heap = HeapCreate(CompareFunc);

	HeapPush(test_heap, (void *)&data_1);
	++heap_size;

	PRINT_TEST(FALSE == HeapIsEmpty(test_heap));
	PRINT_TEST(heap_size == HeapSize(test_heap));
	PRINT_TEST (*(size_t *)HeapPeek(test_heap) == data_1);

	HeapPush(test_heap, (void *)&data_2);
	++heap_size;
	PRINT_TEST(heap_size == HeapSize(test_heap));
	PRINT_TEST (*(size_t *)HeapPeek(test_heap) == data_2);

	HeapDestroy(test_heap);
}

/**************************************************************/

int CompareFunc(const void *data1, const void *data2)
{
	return (int)(*(size_t *)data1 - *(size_t *)data2);  
}