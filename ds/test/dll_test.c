/**************************************
*	Developer :	Yossi Matzliah        *
*	Reviewer  :	Oran Freidin		  *
*	Date      : 18/02/2023			  *
**************************************/

#include <stdio.h> /* printf */

#include "../../ds/include/dll.h"

#define U_LINE 	"\033[1m\033[4m"
#define RED   	"\033[1m\033[41m\x1B[30m"
#define GRN   	"\033[1m\033[42m\x1B[30m"
#define RESET 	"\033[0m"

#define TRUE (1)
#define FALSE (0)

#define PRINT_TEST(x) ((TRUE == (x)) ? printf(GRN"SUCCESS!"RESET"\n\n") : printf(RED"FAILURE!, line %d"RESET"\n\n", __LINE__))

static void TestDLLCreate();
static void TestDLLIsEmpty();
static void TestDLLCount();
static void TestDLLInsert();
static void TestDLLRemove();
static void TestDLLPushPopBack();
static void TestDLLPushPopFront();
static void TestDLLGetSetData();
static void TestDLLIsSameIter();
static void TestDLLFind();
static void TestDLLMultiFind();
static void TestDLLSplice();
static void PrintDLL(dll_t *dll);

int IsMatch(void *data, const void *parameter);

/*****************************************************************/

int main()
{
	TestDLLCreate();
	TestDLLIsEmpty();
	TestDLLCount();
	TestDLLInsert();
	TestDLLRemove();
	TestDLLPushPopBack();
	TestDLLPushPopFront();
	TestDLLGetSetData();
	TestDLLFind();
	TestDLLIsSameIter();
	TestDLLMultiFind();
	TestDLLSplice();
	
	return 0;
}

static void TestDLLCreate()
{
	dll_t *create_dll = NULL;
	 
	printf(U_LINE"Test DLL Create:\n"RESET);
	create_dll = DLLCreate();
	
	PRINT_TEST(DLLIsEmpty(create_dll));

	DLLDestroy(create_dll);
}

static void TestDLLIsEmpty()
{
	int val1 = 1;
	int is_empty = 0;
	dll_t *test_dll = DLLCreate();
	
	printf(U_LINE"Test DLL Is Empty:\n"RESET);
	
	printf("After insert:\n");
	DLLPushBack(test_dll, (void *)&val1);
	is_empty = DLLIsEmpty(test_dll);
	PRINT_TEST(FALSE == is_empty);
	
	printf("After Pop:\n");
	DLLPopBack(test_dll);
	is_empty = DLLIsEmpty(test_dll);
	PRINT_TEST(TRUE == is_empty);
	
	DLLDestroy(test_dll);
}

static void TestDLLCount()
{
	int val1 = 1;
	int val2 = 2;
	int val3 = 3;
	dll_t *test_dll = DLLCreate();
	
	printf(U_LINE"Test DLL Count:\n"RESET);
	
	printf("After insert:\n");
	DLLPushBack(test_dll, (void *)&val1);
	DLLPushBack(test_dll, (void *)&val2);
	DLLPushBack(test_dll, (void *)&val3);
	
	PRINT_TEST(3 == DLLCount(test_dll));
	
	printf("After Pop:\n");
	DLLPopBack(test_dll);
	DLLPopBack(test_dll);
	DLLPopBack(test_dll);
	
	PRINT_TEST(0 == DLLCount(test_dll));
	
	DLLDestroy(test_dll);
}

static void TestDLLInsert()
{
	int val1 = 1;
	int val2 = 2;
	iterator_t insert_node = NULL;
	iterator_t check_node = NULL;
	dll_t *test_dll = DLLCreate();
	
	printf(U_LINE"Test DLL Insert:\n"RESET);
	
	insert_node = DLLInsert(DLLEndIter(test_dll), (void *)&val1);
	check_node = DLLBeginIter(test_dll);
	
	PrintDLL(test_dll);
	PRINT_TEST(insert_node == check_node);
	
	insert_node = DLLInsert(DLLEndIter(test_dll), (void *)&val2);
	check_node = DLLNextIter(DLLBeginIter(test_dll));
	PrintDLL(test_dll);
	PRINT_TEST(insert_node == check_node);
	
	DLLDestroy(test_dll);
}

static void TestDLLRemove()
{
	int val1 = 1;
	int val2 = 2;
	iterator_t delete_node = NULL;
	iterator_t check_node = NULL;
	iterator_t end = NULL;
	dll_t *test_dll = DLLCreate();
	
	printf(U_LINE"Test DLL Remove:\n"RESET);
	
	end = DLLEndIter(test_dll);
	DLLInsert(end, (void *)&val1);
	DLLInsert(end, (void *)&val2);
	printf("Before remove:\n");
	PrintDLL(test_dll);
	
	delete_node = DLLBeginIter(test_dll);
	check_node = DLLRemove(delete_node);
	PRINT_TEST(val2 == *(int *)DLLGetData(check_node));
	
	printf("After remove:\n");
	PrintDLL(test_dll);
	
	DLLDestroy(test_dll);
}

static void TestDLLPushPopBack()
{
	int val1 = 1;
	int val2 = 2;
	int val3 = 3;
	int checker = 0;
	iterator_t check_node = NULL;
	dll_t *test_dll = DLLCreate();
	
	printf(U_LINE"Test DLL Push Back:\n"RESET);
	
	check_node = DLLPushBack(test_dll, (void *)&val1);
	check_node = DLLPushBack(test_dll, (void *)&val2);
	check_node = DLLPushBack(test_dll, (void *)&val3);
	
	checker = *(int *)DLLGetData(check_node);
	PRINT_TEST(val3 == checker);
	PrintDLL(test_dll);
	checker = *(int *)DLLPopBack(test_dll);
	printf(U_LINE"Test DLL Pop Back:\n"RESET);
	PRINT_TEST(val3 == checker);

	PrintDLL(test_dll);
	
	DLLDestroy(test_dll);
}

static void TestDLLPushPopFront()
{
	int val1 = 1;
	int val2 = 2;
	int val3 = 3;
	iterator_t check_node = NULL;
	dll_t *test_dll = DLLCreate();
	
	printf(U_LINE"Test DLL Push Front:\n"RESET);
	
	check_node = DLLPushFront(test_dll, (void *)&val1);
	check_node = DLLPushFront(test_dll, (void *)&val2);
	check_node = DLLPushFront(test_dll, (void *)&val3);
	
	PRINT_TEST(val3 == *(int *)DLLGetData(check_node));
	PrintDLL(test_dll);
	
	printf(U_LINE"Test DLL Pop Front:\n"RESET);
	PRINT_TEST(val3 == *(int *)DLLPopFront(test_dll));
	PrintDLL(test_dll);
	
	DLLDestroy(test_dll);
}

static void TestDLLGetSetData()
{
	int val1 = 1;
	int val2 = 2;
	iterator_t check_node = NULL;
	dll_t *test_dll = DLLCreate();
	
	printf(U_LINE"Test DLL Get Data:\n"RESET);
	
	DLLInsert(DLLEndIter(test_dll), (void *)&val1);
	check_node = DLLBeginIter(test_dll);
	
	PRINT_TEST(val1 == *(int *)DLLGetData(check_node));
	PrintDLL(test_dll);
	
	printf(U_LINE"Test DLL Set Data:\n"RESET);
	DLLSetData(check_node, (void *)&val2);
	
	PRINT_TEST(val2 == *(int *)DLLGetData(check_node));
	PrintDLL(test_dll);
	
	DLLDestroy(test_dll);
}

static void TestDLLIsSameIter()
{
	int val1 = 1;
	iterator_t start = NULL;
	iterator_t end = NULL;
	dll_t *test_dll = DLLCreate();
	
	printf(U_LINE"Test DLL Is Same Iter:\n"RESET);
	
	DLLInsert(DLLEndIter(test_dll), (void *)&val1);
	start = DLLBeginIter(test_dll);
	end = DLLEndIter(test_dll);
	
	PRINT_TEST(DLLIsSameIter(start, DLLPrevIter(end)));

	DLLDestroy(test_dll);
}

static void TestDLLFind()
{
	int val1 = 1;
	int val2 = 2;
	iterator_t start = NULL;
	iterator_t end = NULL;
	iterator_t check_node = NULL;
	dll_t *test_dll = DLLCreate();
	
	printf(U_LINE"Test DLL Find:\n"RESET);
	
	end = DLLEndIter(test_dll);
	DLLInsert(end, (void *)&val1);
	DLLInsert(end, (void *)&val2);
	start = DLLBeginIter(test_dll);
	
	PrintDLL(test_dll);

	check_node = DLLFind(start, end, IsMatch, (void *)&val2);
	PRINT_TEST(val2 == *(int *)(DLLGetData(check_node)));
	
	DLLDestroy(test_dll);
}

static void TestDLLMultiFind()
{
	int val1 = 1;
	int val2 = 2;
	int val3 = 2;
	int val4 = 3;
	int val5 = 2;
	int val6 = 5;
	size_t should_find_counter = 3;
	iterator_t start = NULL;
	iterator_t end = NULL;
	dll_t *dest_dll = DLLCreate();
	dll_t *test_dll = DLLCreate();
	
	printf(U_LINE"Test DLL Multi Find:\n"RESET);
	
	DLLPushBack(test_dll, (void *)&val1);
	DLLPushBack(test_dll, (void *)&val2);
	DLLPushBack(test_dll, (void *)&val3);
	DLLPushBack(test_dll, (void *)&val4);
	DLLPushBack(test_dll, (void *)&val5);
	DLLPushBack(test_dll, (void *)&val6);
	
	printf("Find all %d's appearences in dll:\n", val2);
	PrintDLL(test_dll);
	
	end = DLLEndIter(test_dll);
	start = DLLBeginIter(test_dll);
	dest_dll = DLLMultiFind(dest_dll, start, end, IsMatch, (void *)&val2);
	
	PRINT_TEST(should_find_counter == DLLCount(dest_dll));
	
	printf("Dest dll containing found %d's in dll is:\n", val2);
	PrintDLL(dest_dll);
	
	DLLDestroy(dest_dll);
	DLLDestroy(test_dll);
}

static void TestDLLSplice()
{
	int val1 = 1;
	int val2 = 2;
	int val3 = 3;
	int val4 = 4;
	int val5 = 5;
	
	int val6 = 6;
	int val7 = 7;
	int val8 = 8;
	
	size_t src_dll_size_before = 0;
	size_t src_dll_size_after = 0;
	size_t dest_dll_size_before = 0;
	size_t dest_dll_size_after = 0;
	size_t spliced_size = 0;
	
	iterator_t insert_dest = NULL;
	iterator_t from = NULL;
	iterator_t to = NULL;
	dll_t *src_dll = DLLCreate();
	dll_t *dest_dll = DLLCreate();
	
	printf(U_LINE"Test DLL Splice:\n"RESET);
	
	printf("Before Splice:\n");
	printf("src list, ");
	DLLPushBack(src_dll, (void *)&val1);
	DLLPushBack(src_dll, (void *)&val2);
	DLLPushBack(src_dll, (void *)&val3);
	DLLPushBack(src_dll, (void *)&val4);
	DLLPushBack(src_dll, (void *)&val5);
	PrintDLL(src_dll);
	
	printf("dest list, ");
	DLLPushBack(dest_dll, (void *)&val6);
	DLLPushBack(dest_dll, (void *)&val7);
	DLLPushBack(dest_dll, (void *)&val8);
	PrintDLL(dest_dll);
	
	src_dll_size_before = DLLCount(src_dll);
	dest_dll_size_before = DLLCount(dest_dll);
	
	insert_dest = DLLPrevIter(DLLEndIter(dest_dll));	/* should be 8 */
	from = DLLFind(DLLBeginIter(src_dll), DLLEndIter(src_dll), IsMatch, (void *)&val3);	/* should be 3 */
	to = DLLEndIter(src_dll);
	
	DLLSplice(insert_dest, from, to);
	
	src_dll_size_after = DLLCount(src_dll);
	dest_dll_size_after = DLLCount(dest_dll);
	spliced_size = src_dll_size_before - src_dll_size_after;
	
	PRINT_TEST(dest_dll_size_after == dest_dll_size_before + spliced_size);
	
	printf("After Splice:\n");
	printf("src list, ");
	PrintDLL(src_dll);
	printf("dest list, ");
	PrintDLL(dest_dll);
	
	DLLDestroy(src_dll);
	DLLDestroy(dest_dll);
}

static void PrintDLL(dll_t *dll)
{
	iterator_t iter = DLLBeginIter(dll);
	
	printf("DLL IS:\n");
	printf("NULL<---->");
	while (NULL != DLLNextIter(iter))
	{
		printf("(%d)<---->", *(int *)DLLGetData(iter));
		iter = DLLNextIter(iter);
	}
	
	printf("NULL\n\n");
}

int IsMatch(void *data, const void *parameter)
{
	return (*(int *)data == *(int *)parameter);
}


