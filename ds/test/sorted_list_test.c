/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Omri	  			*
*	Date      : 20/02/2023			*
************************************/

#include <stdio.h> /* printf */

#include "../include/sorted_list.h"

#define U_LINE 	"\033[1m\033[4m"
#define RED   	"\033[1m\033[41m\x1B[30m"
#define GRN   	"\033[1m\033[42m\x1B[30m"
#define RESET 	"\033[0m"

#define TRUE (1)
#define FALSE (0)
#define FAILURE (1)
#define SUCCESS (0)

#define PRINT_TEST(x) ((TRUE == (x)) ? printf(GRN"SUCCESS!"RESET"\n\n") : printf(RED"FAILURE!, line %d"RESET"\n\n", __LINE__))

static void TestSortedListCreate();
static void TestSortedListIsEmpty();
static void TestSortedListSize();
static void TestSortedListInsertFind();
static void TestSortedListPopFrontBack();
static void TestSortedListRemove();
static void TestSortedListForEach();
static void TestSortedListIsSameIter();
static void TestSortedListFind();
static void TestSortedListMerge();
static void TestSortedListFindIf();
static void PrintSortedList(sol_t *sorted_list);

int CompareFunc(const void *data1, const void *data2);
int IsMatch(void *data, const void *parameter);
int AddParam(void *data, void *parameter);

/*****************************************************************/

int main()
{
	TestSortedListCreate();
	TestSortedListIsEmpty();
	TestSortedListSize();
	TestSortedListInsertFind();
	TestSortedListRemove();
	TestSortedListPopFrontBack();
	TestSortedListForEach();
	TestSortedListIsSameIter();
	TestSortedListFind();
	TestSortedListFindIf();
	TestSortedListMerge();
	
	return 0;
}

static void TestSortedListCreate()
{
	sol_t *create_sorted_l = NULL;
	 
	printf(U_LINE"Test SortedList Create:\n"RESET);
	create_sorted_l = SortedListCreate(CompareFunc);
	
	PRINT_TEST(SortedListIsEmpty(create_sorted_l));

	SortedListDestroy(create_sorted_l);
}

static void TestSortedListIsEmpty()
{
	int val1 = 1;
	int is_empty = FALSE;
	sol_t *test_sor_l = SortedListCreate(CompareFunc);
	
	printf(U_LINE"Test SortedList Is Empty:\n"RESET);
	
	printf("After insert:\n");
	SortedListInsert(test_sor_l, (void *)&val1);
	is_empty = SortedListIsEmpty(test_sor_l);
	PRINT_TEST(FALSE == is_empty);
	
	printf("After Pop:\n");
	SortedListPopBack(test_sor_l);
	is_empty = SortedListIsEmpty(test_sor_l);
	PRINT_TEST(TRUE == is_empty);
	
	SortedListDestroy(test_sor_l);
}

static void TestSortedListSize()
{
	int val1 = 1;
	int val2 = 2;
	int val3 = 3;
	size_t size = 3;
	sol_t *test_sor_l = SortedListCreate(CompareFunc);
	
	printf(U_LINE"Test Sorted List Size:\n"RESET);
	
	printf("After insert:\n");
	SortedListInsert(test_sor_l, (void *)&val1);
	SortedListInsert(test_sor_l, (void *)&val2);
	SortedListInsert(test_sor_l, (void *)&val3);
	
	PRINT_TEST(size == SortedListSize(test_sor_l));
	
	printf("After Pop:\n");
	SortedListPopBack(test_sor_l);
	SortedListPopBack(test_sor_l);
	SortedListPopBack(test_sor_l);
	
	PRINT_TEST(0 == SortedListSize(test_sor_l));
	
	SortedListDestroy(test_sor_l);
}

static void TestSortedListInsertFind()
{
	int val1 = 2;
	int val2 = 3;
	int val3 = 1;
	int val4 = 4;
	sol_iterator_t insert_node = {NULL};
	sol_iterator_t check_node = {NULL};
	sol_t *test_sor_l = SortedListCreate(CompareFunc);
	
	printf(U_LINE"Test Sorted List Insert:\n"RESET);
	
	SortedListInsert(test_sor_l, (void *)&val1);
	SortedListInsert(test_sor_l, (void *)&val2);
	insert_node = SortedListInsert(test_sor_l, (void *)&val3);
	check_node = SortedListBeginIter(test_sor_l);
	PrintSortedList(test_sor_l);
	PRINT_TEST(SortedListIsSameIter(insert_node, check_node));
	
	insert_node = SortedListInsert(test_sor_l, (void *)&val4);
	check_node = SortedListPrevIter(SortedListEndIter(test_sor_l));
	PrintSortedList(test_sor_l);
	PRINT_TEST(SortedListIsSameIter(insert_node, check_node));
	
	SortedListDestroy(test_sor_l);
}

static void TestSortedListRemove()
{
	int val1 = 2;
	int val2 = 3;
	int val3 = 1;
	sol_iterator_t delete_node = {NULL};
	sol_iterator_t check_node = {NULL};
	sol_t *test_sor_l = SortedListCreate(CompareFunc);
	
	printf(U_LINE"Test Sorted List Remove:\n"RESET);
	
	SortedListInsert(test_sor_l, (void *)&val1);
	SortedListInsert(test_sor_l, (void *)&val2);
	SortedListInsert(test_sor_l, (void *)&val3);
	printf("Before remove:\n");
	PrintSortedList(test_sor_l);
	
	delete_node = SortedListBeginIter(test_sor_l);
	check_node = SortedListRemove(delete_node);
	PRINT_TEST(val1 == *(int *)SortedListGetData(check_node));
	
	printf("After remove:\n");
	PrintSortedList(test_sor_l);
	
	SortedListDestroy(test_sor_l);
}

static void TestSortedListPopFrontBack()
{
	int val1 = 1;
	int val2 = 3;
	int val3 = 2;
	int checker = 0;
	
	sol_t *test_sor_l = SortedListCreate(CompareFunc);

	SortedListInsert(test_sor_l, (void *)&val1);
	SortedListInsert(test_sor_l, (void *)&val2);
	SortedListInsert(test_sor_l, (void *)&val3);
	
	printf(U_LINE"Test Sorted List Pop Back:\n"RESET);
	
	checker = *(int *)SortedListPopBack(test_sor_l);
	PRINT_TEST(val2 == checker);
	PrintSortedList(test_sor_l);
	
	checker = *(int *)SortedListPopFront(test_sor_l);
	printf(U_LINE"Test Sorted List Pop Back:\n"RESET);
	PRINT_TEST(val1 == checker);

	PrintSortedList(test_sor_l);
	
	SortedListDestroy(test_sor_l);
}

static void TestSortedListForEach()
{
	int val1 = 2;
	int val2 = 3;
	int val3 = 1;
	int val4 = 5;
	int val5 = 4;
	int checker = 0;
	int param_to_add = 3;
	sol_iterator_t from = {NULL};
	sol_iterator_t to = {NULL};
	sol_t *test_sor_l = SortedListCreate(CompareFunc);
	
	SortedListInsert(test_sor_l, (void *)&val1);
	SortedListInsert(test_sor_l, (void *)&val2);
	SortedListInsert(test_sor_l, (void *)&val3);
	SortedListInsert(test_sor_l, (void *)&val4);
	SortedListInsert(test_sor_l, (void *)&val5);
	
	printf(U_LINE"Test Sorted List ForEach:\n"RESET);
	from = SortedListNextIter(SortedListBeginIter(test_sor_l));
	to = SortedListPrevIter(SortedListEndIter(test_sor_l));
	printf("Before adding %d from two to four:\n", param_to_add);
	PrintSortedList(test_sor_l);
	checker = SortedListForEach(from, to, AddParam, (void *)&param_to_add);
	PRINT_TEST(SUCCESS == checker);
	
	printf("After adding %d from two to four:\n", param_to_add);
	PrintSortedList(test_sor_l);
	
	SortedListDestroy(test_sor_l);
}


static void TestSortedListIsSameIter()
{
	int val1 = 1;
	sol_iterator_t from = {NULL};
	sol_iterator_t to = {NULL};
	sol_t *test_sor_l = SortedListCreate(CompareFunc);
	
	printf(U_LINE"Test Sorted List Is Same Iter:\n"RESET);
	
	SortedListInsert(test_sor_l, (void *)&val1);
	from = SortedListBeginIter(test_sor_l);
	to = SortedListEndIter(test_sor_l);
	
	PRINT_TEST(SortedListIsSameIter(from, SortedListPrevIter(to)));

	SortedListDestroy(test_sor_l);
}

static void TestSortedListFind()
{
	int val1 = 1;
	int val2 = 2;
	sol_iterator_t from = {NULL};
	sol_iterator_t to = {NULL};
	sol_iterator_t check_node = {NULL};
	sol_t *test_sor_l = SortedListCreate(CompareFunc);
	
	printf(U_LINE"Test sorted list Find:\n"RESET);
	
	SortedListInsert(test_sor_l, (void *)&val1);
	SortedListInsert(test_sor_l, (void *)&val2);
	from = SortedListBeginIter(test_sor_l);
	to = SortedListPrevIter(SortedListEndIter(test_sor_l));
	PrintSortedList(test_sor_l);

	check_node = SortedListFind(test_sor_l, from, to, (void *)&val2);
	PRINT_TEST(val2 == *(int *)(SortedListGetData(check_node)));
	
	SortedListDestroy(test_sor_l);
}

static void TestSortedListFindIf()
{
	int val1 = 1;
	int val2 = 2;
	int val3 = 2;
	int val4 = 3;
	int val5 = 2;
	int val6 = 5;
	
	sol_iterator_t from = {NULL};
	sol_iterator_t to = {NULL};
	sol_iterator_t check_node = {NULL};
	sol_t *test_sor_l = SortedListCreate(CompareFunc);

	SortedListInsert(test_sor_l, (void *)&val1);
	SortedListInsert(test_sor_l, (void *)&val2);
	SortedListInsert(test_sor_l, (void *)&val3);
	SortedListInsert(test_sor_l, (void *)&val4);
	SortedListInsert(test_sor_l, (void *)&val5);
	SortedListInsert(test_sor_l, (void *)&val6);
	
	printf(U_LINE"Test Sorted List FindIf:\n"RESET);
	PrintSortedList(test_sor_l);
	
	from = SortedListBeginIter(test_sor_l);
	to = SortedListNextIter(SortedListBeginIter(test_sor_l));
	check_node = SortedListFindIf(from, to, IsMatch, (void *)&val2);
	printf("Need to find:\n");
	PRINT_TEST(to.dll_iterator == check_node.dll_iterator);
	
	printf("Doesn't need to find:\n");
	
	check_node = SortedListFindIf(from, to, IsMatch, (void *)&val5);
	PRINT_TEST(*(int *)to.dll_iterator != val5);
	
	SortedListDestroy(test_sor_l);
}

static void TestSortedListMerge()
{
	int val1 = 2;
	int val2 = 6;
	int val3 = 4;
	int val4 = 8;
	int val5 = 9;
	int val6 = 1;
	int val7 = 3;
	int val8 = 5;
	int val9 = 8;
	size_t result_count = 9;
	sol_t *dest_sor_l = SortedListCreate(CompareFunc);
	sol_t *src_sor_l = SortedListCreate(CompareFunc);
	
	printf(U_LINE"Test Sorted List Merge:\n"RESET);
	printf("Init dest list:\n");
	SortedListInsert(dest_sor_l, (void *)&val1);
	SortedListInsert(dest_sor_l, (void *)&val2);
	SortedListInsert(dest_sor_l, (void *)&val3);
	SortedListInsert(dest_sor_l, (void *)&val4);
	PrintSortedList(dest_sor_l);
	
	printf("Init src list:\n");
	SortedListInsert(src_sor_l, (void *)&val5);
	SortedListInsert(src_sor_l, (void *)&val6);
	SortedListInsert(src_sor_l, (void *)&val7);
	SortedListInsert(src_sor_l, (void *)&val8);
	SortedListInsert(src_sor_l, (void *)&val9);
	PrintSortedList(src_sor_l);
	
	dest_sor_l = SortedListMerge(dest_sor_l, src_sor_l);
	
	PRINT_TEST(result_count == SortedListSize(dest_sor_l));
	
	printf("After merge dest list:\n");
	PrintSortedList(dest_sor_l);
	printf("After merge src list:\n");
	PrintSortedList(src_sor_l);
	
	SortedListDestroy(dest_sor_l);
	SortedListDestroy(src_sor_l);
}

static void PrintSortedList(sol_t *sorted_list)
{
	sol_iterator_t iter = SortedListBeginIter(sorted_list);
	
	printf("Sorted List IS:\n");
	printf("NULL<---->");
	while (NULL != (SortedListNextIter(iter)).dll_iterator)
	{
		printf("(%d)<---->", *(int *)SortedListGetData(iter));
		iter = SortedListNextIter(iter);
	}
	
	printf("NULL\n\n");
}

int AddParam(void *data, void *param)
{
	*(int *)data += *(int *)param;
	
	return SUCCESS;
}

int IsMatch(void *data, const void *parameter)
{
	return (*(int *)data == *(int *)parameter);
}

int CompareFunc(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);  
}
