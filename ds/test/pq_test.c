/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Moshe	  			*
*	Date      : 28/02/2023			*
************************************/

#include <stdio.h> /* printf */

#include "../include/pq.h"

#define U_LINE 	"\033[1m\033[4m"
#define RED   	"\033[1m\033[41m\x1B[30m"
#define GRN   	"\033[1m\033[42m\x1B[30m"
#define RESET 	"\033[0m"

#define TRUE (1)
#define FALSE (0)
#define FAILURE (1)
#define SUCCESS (0)

#define PRINT_TEST(x) ((TRUE == (x)) ? printf(GRN"SUCCESS!"RESET"\n\n") : printf(RED"FAILURE!, line %d"RESET"\n\n", __LINE__))

static void TestPriorityQueueCreate();
static void TestPriorityQueueIsEmpty();
static void TestPriorityQueueEnqueuePeekDequeue();
static void TestPriorityQueueSize();
static void TestPriorityQueueClear();
static void TestPriorityQueueErase();
static void TestPriorityQueueMerge();

/*****************************************************************/

int PriorityFunc(const void *data1, const void *data2);
int IsMatch(const void *data, const void *parameter);

/*****************************************************************/

int main()
{
	TestPriorityQueueIsEmpty();
	TestPriorityQueueCreate();
	TestPriorityQueueEnqueuePeekDequeue();
	TestPriorityQueueSize();
	TestPriorityQueueErase();
	TestPriorityQueueClear();
	TestPriorityQueueMerge();
	
	return 0;
}

static void TestPriorityQueueCreate()
{
	pq_t *create_prior_q = PQCreate(PriorityFunc);
	 
	printf(U_LINE"Test PriorityQueue Create:\n"RESET);
	PRINT_TEST(PQIsEmpty(create_prior_q));

	PQDestroy(create_prior_q);
}

static void TestPriorityQueueIsEmpty()
{
	int val1 = 1;
	int is_empty = FALSE;
	pq_t *test_prior_q = PQCreate(PriorityFunc);
	
	printf(U_LINE"Test PriorityQueue Is Empty:\n"RESET);
	
	printf("After Enqueue:\n");
	PQEnqueue(test_prior_q, (void *)&val1);
	is_empty = PQIsEmpty(test_prior_q);
	PRINT_TEST(FALSE == is_empty);
	
	printf("After Dequeue:\n");
	PQDequeue(test_prior_q);
	is_empty = PQIsEmpty(test_prior_q);
	PRINT_TEST(TRUE == is_empty);
	
	PQDestroy(test_prior_q);
}

static void TestPriorityQueueEnqueuePeekDequeue()
{
	int val1 = 2;
	int val2 = 3;
	int val3 = 1;
	
	pq_t *test_prior_q = PQCreate(PriorityFunc);
	
	printf(U_LINE"Test Priority Queue Enqueue:\n"RESET);
	
	PRINT_TEST(SUCCESS == PQEnqueue(test_prior_q, (void *)&val1));
	PRINT_TEST(SUCCESS == PQEnqueue(test_prior_q, (void *)&val2));
	PRINT_TEST(SUCCESS == PQEnqueue(test_prior_q, (void *)&val3));
	printf(U_LINE"Test Priority Queue Peek + Dequeue:\n"RESET); 
	PRINT_TEST(val3 == *(int *)PQPeek(test_prior_q));
	PQDequeue(test_prior_q);
	PRINT_TEST(val1 == *(int *)PQPeek(test_prior_q));
	PQDequeue(test_prior_q);
	PRINT_TEST(val2 == *(int *)PQPeek(test_prior_q));
	PQDequeue(test_prior_q);
	PRINT_TEST(TRUE == PQIsEmpty(test_prior_q));
	
	PQDestroy(test_prior_q);
}

static void TestPriorityQueueSize()
{
	int val1 = 2;
	int val2 = 1;
	int val3 = 3;
	size_t size = 3;
	pq_t *test_prior_q = PQCreate(PriorityFunc);
	
	printf(U_LINE"Test Priority Queue Size:\n"RESET);
	
	printf("After Enqueue:\n");
	PQEnqueue(test_prior_q, (void *)&val1);
	PQEnqueue(test_prior_q, (void *)&val2);
	PQEnqueue(test_prior_q, (void *)&val3);
	
	PRINT_TEST(size == PQSize(test_prior_q));
	
	printf("After Dequeue:\n");
	PQDequeue(test_prior_q);
	PQDequeue(test_prior_q);
	PQDequeue(test_prior_q);
	
	PRINT_TEST(0 == PQSize(test_prior_q));
	
	PQDestroy(test_prior_q);
}

static void TestPriorityQueueErase()
{
	int val1 = 1;
	int val2 = 3;
	int val3 = 2;
	
	pq_t *test_prior_q = PQCreate(PriorityFunc);

	PQEnqueue(test_prior_q, (void *)&val1);
	PQEnqueue(test_prior_q, (void *)&val2);
	PQEnqueue(test_prior_q, (void *)&val3);
	
	printf(U_LINE"Test Priority Queue Erase:\n"RESET);
	PQErase(test_prior_q, IsMatch, (void *)&val1);
	PRINT_TEST(val3 == *(int *)PQPeek(test_prior_q));
	PQEnqueue(test_prior_q, (void *)&val1);
	PRINT_TEST(val1 == *(int *)PQPeek(test_prior_q));
	PQErase(test_prior_q, IsMatch, (void *)&val3);
	PQDequeue(test_prior_q);
	PRINT_TEST(val2 == *(int *)PQPeek(test_prior_q));
	PQErase(test_prior_q, IsMatch, (void *)&val2);
	PRINT_TEST(TRUE == PQIsEmpty(test_prior_q));
	
	PQDestroy(test_prior_q);
}

static void TestPriorityQueueClear()
{
	int val1 = 2;
	int val2 = 3;
	int val3 = 1;
	int val4 = 5;
	int val5 = 4;
 
	pq_t *test_prior_q = PQCreate(PriorityFunc);
	
	PQEnqueue(test_prior_q, (void *)&val1);
	PQEnqueue(test_prior_q, (void *)&val2);
	PQEnqueue(test_prior_q, (void *)&val3);
	PQEnqueue(test_prior_q, (void *)&val4);
	PQEnqueue(test_prior_q, (void *)&val5);
	
	printf(U_LINE"Test Priority Queue Clear:\n"RESET);
	PQClear(test_prior_q);
	PRINT_TEST(TRUE == PQIsEmpty(test_prior_q));
	PQEnqueue(test_prior_q, (void *)&val1);
	PQEnqueue(test_prior_q, (void *)&val2);
	PRINT_TEST(val1 == *(int *)PQPeek(test_prior_q));
	
	PQDestroy(test_prior_q);
}

static void TestPriorityQueueMerge()
{
	int val1 = 2;
	int val2 = 6;
	int val3 = 4;
	int val4 = 8;
	int val5 = 9;
	int val6 = 1;
	int val7 = 3;
	int val8 = 5;
	int val9 = 7;
	size_t result_count = 9;
	pq_t *dest_prior_q = PQCreate(PriorityFunc);
	pq_t *src_prior_q = PQCreate(PriorityFunc);
	
	printf(U_LINE"Test Priority Queue Merge:\n"RESET);
	/* Init dest list */
	PQEnqueue(dest_prior_q, (void *)&val1);
	PQEnqueue(dest_prior_q, (void *)&val2);
	PQEnqueue(dest_prior_q, (void *)&val3);
	PQEnqueue(dest_prior_q, (void *)&val4);
	
	/* Init src list */
	PQEnqueue(src_prior_q, (void *)&val5);
	PQEnqueue(src_prior_q, (void *)&val6);
	PQEnqueue(src_prior_q, (void *)&val7);
	PQEnqueue(src_prior_q, (void *)&val8);
	PQEnqueue(src_prior_q, (void *)&val9);
	
	dest_prior_q = PQMerge(dest_prior_q, src_prior_q);
	PRINT_TEST(result_count == PQSize(dest_prior_q));
	PRINT_TEST(TRUE == PQIsEmpty(src_prior_q));
	
	PRINT_TEST(1 == *(int *)PQPeek(dest_prior_q));
	PQDequeue(dest_prior_q);
	PRINT_TEST(2 == *(int *)PQPeek(dest_prior_q));
	PQDequeue(dest_prior_q);
	PRINT_TEST(3 == *(int *)PQPeek(dest_prior_q));
	PQDequeue(dest_prior_q);
	PRINT_TEST(4 == *(int *)PQPeek(dest_prior_q));
	PQDequeue(dest_prior_q);
	PRINT_TEST(5 == *(int *)PQPeek(dest_prior_q));
	PQDequeue(dest_prior_q);
	PRINT_TEST(6 == *(int *)PQPeek(dest_prior_q));
	PQDequeue(dest_prior_q);
	PRINT_TEST(7 == *(int *)PQPeek(dest_prior_q));
	PQDequeue(dest_prior_q);
	PRINT_TEST(8 == *(int *)PQPeek(dest_prior_q));
	PQDequeue(dest_prior_q);
	PRINT_TEST(9 == *(int *)PQPeek(dest_prior_q));
	PQDequeue(dest_prior_q);
	PRINT_TEST(TRUE == PQIsEmpty(dest_prior_q));

	PQDestroy(dest_prior_q);
	PQDestroy(src_prior_q);
}

int IsMatch(const void *data, const void *parameter)
{
	return (*(int *)data == *(int *)parameter);
}

int PriorityFunc(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);  
}
