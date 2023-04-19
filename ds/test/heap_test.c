/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	????				*
*	Date      : ?/04/2023			*
************************************/

#include <stdio.h>	

#include "dynamic_vector.h"
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

struct heap 
{
	vector_t *vec;
    int (*cmp_func)(const void *, const void *);
};

typedef struct test_struct
{
    size_t data;
    size_t key;
} test_struct_t;

/*****************************************************************/

int main();

static void TestHeapCreateDestroy();
static void TestHeapPush();
static void TestHeapPeek();
static void TestHeapPop();
static void TestHeapRemove();
static void TestHeapRemoveByKey();

int CompareFunc(const void *data1, const void *data2);
int IsMatch(const void *data, const void *param);
int KeyCmpFunction(const void *lhd, const void *rhd);
static void PrintHeapTree(heap_t *heap);
static void PrintStructHeapTree(heap_t *heap);

/*****************************************************************/

int main()
{
	TestHeapCreateDestroy();
	TestHeapPush();
	TestHeapPeek();
	TestHeapPop();
	TestHeapRemove();
	TestHeapRemoveByKey();

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

	HeapPush(test_heap, (void *)&data_3);
	++heap_size;
	HeapPush(test_heap, (void *)&data_4);
	++heap_size;
	PRINT_TEST(heap_size == HeapSize(test_heap));

	PrintHeapTree(test_heap);

	HeapDestroy(test_heap);
}

static void TestHeapPeek()
{
	heap_t *test_heap = NULL;
	size_t data_1 = 5;
	size_t data_2 = 10;
	size_t data_3 = 3;

	printf(U_LINE"\nTest Heap Peek:\n\n"RESET);

	test_heap = HeapCreate(CompareFunc);

	HeapPush(test_heap, (void *)&data_1);
	PRINT_TEST (*(size_t *)HeapPeek(test_heap) == data_1);

	HeapPush(test_heap, (void *)&data_2);
	PRINT_TEST (*(size_t *)HeapPeek(test_heap) == data_2);

	HeapPush(test_heap, (void *)&data_3);
	PRINT_TEST (*(size_t *)HeapPeek(test_heap) == data_2);

	HeapDestroy(test_heap);
}

static void TestHeapPop()
{
	heap_t *test_heap = NULL;
	size_t data_1 = 5;
	size_t data_2 = 10;
	size_t data_3 = 15;
	size_t data_4 = 8;
	size_t heap_size = 0;

	printf(U_LINE"\nTest Heap Pop:\n\n"RESET);

	test_heap = HeapCreate(CompareFunc);

	HeapPush(test_heap, (void *)&data_1);
	++heap_size;
	HeapPush(test_heap, (void *)&data_2);
	++heap_size;
	HeapPush(test_heap, (void *)&data_3);
	++heap_size;
	HeapPush(test_heap, (void *)&data_4);
	++heap_size;

	HeapPop(test_heap);
	--heap_size;
	PRINT_TEST(heap_size == HeapSize(test_heap));
	PRINT_TEST(*(size_t *)HeapPeek(test_heap) == data_2);
	HeapPop(test_heap);
	--heap_size;
	PRINT_TEST(heap_size == HeapSize(test_heap));
	PRINT_TEST(*(size_t *)HeapPeek(test_heap) == data_4);
	HeapPop(test_heap);
	HeapPop(test_heap);

	PRINT_TEST(TRUE == HeapIsEmpty(test_heap));

	HeapPush(test_heap, (void *)&data_1);
	
	PRINT_TEST (*(size_t *)HeapPeek(test_heap) == data_1);

	HeapDestroy(test_heap);
}

static void TestHeapRemove()
{
	heap_t *test_heap = NULL;
	size_t data_1 = 5;
	size_t data_2 = 10;
	size_t data_3 = 15;
	size_t data_4 = 8;
	size_t not_in = 2;
	size_t heap_size = 0;
	void *return_data = NULL;

	printf(U_LINE"\nTest Heap Remove:\n\n"RESET);

	test_heap = HeapCreate(CompareFunc);

	HeapPush(test_heap, (void *)&data_1);
	++heap_size;
	HeapPush(test_heap, (void *)&data_2);
	++heap_size;
	HeapPush(test_heap, (void *)&data_3);
	++heap_size;
	HeapPush(test_heap, (void *)&data_4);
	++heap_size;

	return_data = HeapRemove(test_heap, IsMatch, (void *)&data_2);
	--heap_size;
	PRINT_TEST(*(size_t *)return_data == data_2);
	PRINT_TEST(heap_size == HeapSize(test_heap));
	
	return_data = HeapRemove(test_heap, IsMatch, (void *)&data_3);
	PRINT_TEST(*(size_t *)return_data == data_3);

	return_data = HeapRemove(test_heap, IsMatch, (void *)&not_in);
	PRINT_TEST(NULL == return_data);

	HeapRemove(test_heap, IsMatch, (void *)&data_1);
	HeapRemove(test_heap, IsMatch, (void *)&data_4);
	PRINT_TEST(TRUE == HeapIsEmpty(test_heap));

	HeapDestroy(test_heap);
}

static void TestHeapRemoveByKey()
{
	heap_t *test_heap = NULL;
	test_struct_t struct_1 = {1, 5};
	test_struct_t struct_2 = {2, 10};
	test_struct_t struct_3 = {3, 15};
	test_struct_t struct_4 = {4, 8};
	test_struct_t struct_not_in = {20, 2};

	test_struct_t *struct_1_ptr = &struct_1;
	test_struct_t *struct_2_ptr = &struct_2;
	test_struct_t *struct_3_ptr = &struct_3;
	test_struct_t *struct_4_ptr = &struct_4;
	test_struct_t *struct_not_in_ptr = &struct_not_in;

	size_t heap_size = 0;
	void *return_data = NULL;

	printf(U_LINE"\nTest Heap Remove By Key:\n\n"RESET);

	test_heap = HeapCreate(KeyCmpFunction);

	HeapPush(test_heap, (void *)struct_1_ptr);
	++heap_size;
	HeapPush(test_heap, (void *)struct_2_ptr);
	++heap_size;
	HeapPush(test_heap, (void *)struct_3_ptr);
	++heap_size;
	HeapPush(test_heap, (void *)struct_4_ptr);
	++heap_size;

	PrintStructHeapTree(test_heap);

	return_data = HeapRemoveByKey(test_heap, (void *)struct_2_ptr);
	--heap_size;
	
	PRINT_TEST((*(test_struct_t **)return_data)->key == struct_2.key);
	PRINT_TEST(heap_size == HeapSize(test_heap));
	PrintStructHeapTree(test_heap);
	return_data = HeapRemoveByKey(test_heap, (void *)struct_3_ptr);
	PRINT_TEST((*(test_struct_t **)return_data)->key == struct_3.key);
	PrintStructHeapTree(test_heap);
	return_data = HeapRemoveByKey(test_heap, (void *)struct_not_in_ptr);
	PRINT_TEST(NULL == return_data);

	HeapRemoveByKey(test_heap, (void *)struct_1_ptr);
	PrintStructHeapTree(test_heap);
	HeapRemoveByKey(test_heap, (void *)struct_4_ptr);
	PrintStructHeapTree(test_heap);
	PRINT_TEST(TRUE == HeapIsEmpty(test_heap));

	HeapDestroy(test_heap);
}


/**************************************************************/

int CompareFunc(const void *data1, const void *data2)
{
	return (int)(*(size_t *)data1 - *(size_t *)data2);  
}

int IsMatch(const void *data, const void *param)
{
	return (*(size_t *)data == *(size_t *)param);
}

int KeyCmpFunction(const void *lhd, const void *rhd)
{
	return (((test_struct_t *)lhd)->key - ((test_struct_t *)rhd)->key);
}

static void PrintHeapTree(heap_t *heap)
{
    int level = 0;
    size_t nodes_in_level = 1;
    size_t i = 0;

    for (i = 0; i < HeapSize(heap); ++i) 
    {
        printf("%ld  ", **(size_t **)VectorGetAccessToElement(heap->vec, i));
        if (i == nodes_in_level - 1) 
        {
            NEW_LINE;
            level++;
            nodes_in_level += (1 << level);
        }
    }
    NEW_LINE;
}

static void PrintStructHeapTree(heap_t *heap) 
{
    size_t level = 0;
    size_t nodes_in_level = 1;
    size_t i = 0;

    for (i = 0; i < HeapSize(heap); ++i) 
    {
        printf("%ld  ", (*(test_struct_t **)VectorGetAccessToElement(heap->vec, i))->data);
        if (i == nodes_in_level - 1) 
        {
            NEW_LINE;
            level++;
            nodes_in_level += (1 << level);
        }
    }
    NEW_LINE;
}