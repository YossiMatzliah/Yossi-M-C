/**************************************
*	Developer :	Yossi Matzliah        *
*	Date      : 09/02/2023			  *
*	Reviewer  :	Lilach				  *
**************************************/

#include <stdio.h> /* printf */

#include "../../ds/include/linked_list.h"

#define U_LINE 	"\033[1m\033[4m"
#define RED   	"\033[1m\033[41m\x1B[30m"
#define GRN   	"\033[1m\033[42m\x1B[30m"
#define RESET 	"\033[0m"

static void TestSLLIsEmpty(sll_t *sll);
static void TestSLLInsertBefore(iterator_t iter, int *value);
static void TestSLLBeginIter(sll_t *sll, int *value);
static void TestSLLEndIter(sll_t *sll);
static void TestSLLNextIter(iterator_t iter, int *value);
static void TestSLLCount(sll_t *sll);
static void TestSLLRemove(iterator_t iter, int *value);
static void TestSLLSetGetData(iterator_t iterator, int *value);
static void TestIsSameIter(iterator_t iter1, iterator_t iter2);
static void TestSLLFind(iterator_t start, iterator_t end, int *value);
static void TestSLLForEach(iterator_t start, iterator_t end, int *value);
static void PrintSLL(sll_t *sll);
int AddParamToData(void *data, void *parameter);
int IsMatch(void *data, const void *parameter);

/*****************************************************************/

int main()
{
	int val1 = 1;
	int val2 = 2;
	int val3 = 3;
	int val4 = 4;
	int val5 = 5;
	int add_param = 1;
	iterator_t iter_head = NULL;
	iterator_t iter_tail = NULL;
	sll_t *sll_test = NULL;
	
	sll_test = SLLCreate();
	
	iter_head = SLLBeginIter(sll_test);
	iter_tail = SLLEndIter(sll_test);
	TestSLLIsEmpty(sll_test);
	printf("before");
	TestSLLInsertBefore(iter_head, &val1);
	printf("after");
	iter_tail = SLLEndIter(sll_test);
	
	TestSLLBeginIter(sll_test, &val1);
	TestSLLEndIter(sll_test);
	
	TestSLLInsertBefore(iter_tail, &val2);
	iter_tail = SLLEndIter(sll_test);
	PrintSLL(sll_test);
	TestSLLNextIter(iter_head, &val2);
	TestSLLCount(sll_test);
	TestSLLRemove(iter_head, &val2);
	PrintSLL(sll_test);
	
	TestSLLSetGetData(iter_head, &val3);
	TestSLLInsertBefore(iter_tail, &val4);
	iter_tail = SLLEndIter(sll_test);
	
	TestIsSameIter(SLLNextIter(iter_head), SLLNextIter(iter_head));
	
	TestSLLInsertBefore(iter_tail, &val5);
	iter_tail = SLLEndIter(sll_test);
	
	TestSLLFind(iter_head, iter_tail, &val3);
	
	printf(U_LINE"Before addind %d to SLL:\n"RESET, add_param);
	PrintSLL(sll_test);
	
	TestSLLForEach(iter_head, iter_tail, &add_param);
	printf(U_LINE"After addind %d to SLL:\n"RESET, add_param);
	PrintSLL(sll_test);
	
	SLLDestroy(sll_test);
	
	return 0;
}

static void TestSLLIsEmpty(sll_t *sll)
{
	printf(U_LINE"Test SLL IsEmpty:\n"RESET);
	
	if (1 == SLLIsEmpty(sll))
	{
		printf(GRN"SUCCESS!"RESET"\n\n");
	}
	
	else
	{
		printf(RED"FAILURE!"RESET"\n\n");
	}
}

static void TestSLLInsertBefore(iterator_t iter, int *value)
{
	iterator_t val_iter = SLLInsertBefore(iter, (void *)value);
	
	printf(U_LINE"Test SLL Insert Before:\n"RESET);
	
	if (*value == *(int *)SLLGetData(val_iter))
	{
		printf(GRN"SUCCESS!"RESET"\n\n");
	}
	
	else
	{
		printf(RED"FAILURE!"RESET"\n\n");
	}
}

static void TestSLLBeginIter(sll_t *sll, int *value)
{
	iterator_t result_iter = SLLBeginIter(sll);
	
	printf(U_LINE"Test SLL Begin Iter:\n"RESET);
	
	if (*value == *(int *)SLLGetData(result_iter))
	{
		printf(GRN"SUCCESS!"RESET"\n\n");
	}
	
	else
	{
		printf(RED"FAILURE!"RESET"\n\n");
	}
}

static void TestSLLEndIter(sll_t *sll)
{
	iterator_t result_iter = SLLEndIter(sll);
	
	printf(U_LINE"Test SLL End Iter:\n"RESET);
	
	if(sll == SLLGetData(result_iter))
	{
		printf(GRN"SUCCESS!"RESET"\n\n");
	}
	
	else
	{
		printf(RED"FAILURE!"RESET"\n\n");
	}
}

static void TestSLLNextIter(iterator_t iter, int *value)
{
	iterator_t result_iter = SLLNextIter(iter);
	
	printf(U_LINE"Test SLL Next Iter:\n"RESET);
	
	if (*value == *(int *)SLLGetData(result_iter))
	{
		printf(GRN"SUCCESS!"RESET"\n\n");
	}
	
	else
	{
		printf(RED"FAILURE!"RESET"\n\n");
	}
}

static void TestSLLCount(sll_t *sll)
{
	printf(U_LINE"Test SLL Count:\n"RESET);
	
	if (2 == SLLCount(sll))
	{
		printf(GRN"SUCCESS!"RESET"\n\n");
	}
	
	else
	{
		printf(RED"FAILURE!"RESET"\n\n");
	}
}

static void TestSLLRemove(iterator_t iter, int *value)
{
	iterator_t result_iter = SLLRemove(iter);	
	
	printf(U_LINE"Test SLL Remove:\n"RESET);
	
	if (*value == *(int *)SLLGetData(result_iter))
	{
		printf(GRN"SUCCESS!"RESET"\n\n");
	}
	
	else
	{
		printf(RED"FAILURE!"RESET"\n\n");
	}
}

static void TestSLLSetGetData(iterator_t iterator, int *value)
{
	SLLSetData(iterator, (void *)value);
	
	printf(U_LINE"Test SLL Set & Get Data:\n"RESET);
	
	if (*value == *(int *)(SLLGetData(iterator)))
	{
		printf(GRN"SUCCESS!"RESET"\n\n");
	}
	
	else
	{
		printf(RED"FAILURE!"RESET"\n\n");
	}
}

static void TestIsSameIter(iterator_t iter1, iterator_t iter2)
{
	printf(U_LINE"Test SLL Is Same Iter:\n"RESET);
	
	if (1 == SLLIsSameIter(iter1, iter2))
	{
		printf(GRN"SUCCESS!"RESET"\n\n");
	}
	
	else
	{
		printf(RED"FAILURE!"RESET"\n\n");
	}
}

static void TestSLLFind(iterator_t start, iterator_t end, int *value)
{
	iterator_t result_iter = SLLFind(start, end, &IsMatch, (void *)value);
	
	printf(U_LINE"Test SLL Find:\n"RESET);
	
	if (*value == *(int *)SLLGetData(result_iter))
	{
		printf(GRN"SUCCESS!"RESET"\n\n");
	}
	
	else
	{
		printf(RED"FAILURE!"RESET"\n\n");
	}
}

static void TestSLLForEach(iterator_t start, iterator_t end, int *value)
{
	int return_value = SLLForEach(start, end, &AddParamToData, (void *)value);
	
	printf(U_LINE"Test SLL ForEach:\n"RESET);
	
	if (0 == return_value)
	{
		printf(GRN"SUCCESS!"RESET"\n\n");
	}
	
	else
	{
		printf(RED"FAILURE!"RESET"\n\n");
	}
}

static void PrintSLL(sll_t *sll)
{
	iterator_t iter = SLLBeginIter(sll);
	
	printf(U_LINE"SLL IS:\n"RESET);
	
	while (NULL != SLLNextIter(iter))
	{
		printf("%d---->", *(int *)SLLGetData(iter));
		iter = SLLNextIter(iter);
	}
	
	printf("NULL\n\n");
}

int AddParamToData(void *data, void *parameter)
{
	int result = *(int *)data;
	*(int *)data += *(int *)parameter;
	
	if (*(int *)data == (result + *(int *)parameter))
	{
		return 0;
	}
	
	else
	{
		return 1;
	}
}

int IsMatch(void *data, const void *parameter)
{
	return (*(int *)data == *(int *)parameter);
}

