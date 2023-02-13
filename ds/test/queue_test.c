/************************************
*	Developer :	Yossi Matzliah		*
*	Date      :	12.02.2023			*
*	Reviewer  :	Oran				*
************************************/
#include <stdio.h>	/* printf */

#include "../../ds/include/queue.h"

#define U_LINE 	"\033[1m\033[4m"
#define RED   	"\033[1m\033[41m\x1B[30m"
#define GRN   	"\033[1m\033[42m\x1B[30m"
#define RESET 	"\033[0m"

static void TestQueueIsEmpty(queue_t *queue);
static void TestQueueEnqueue(queue_t *queue, int *value);
static void TestQueuePeek(queue_t *queue, int value);
static void TestQueueDequeue(queue_t *queue);
static void TestQueueSize(queue_t *queue, size_t size);
static void TestQueueAppend(queue_t *dest, queue_t *src);

/**************************************************/

int main()
{
	int val1 = 1;
	int val2 = 2;
	int val3 = 3;
	int val4 = 4;
	int val5 = 5;
	int val6 = 6;
	int val7 = 7;
	queue_t *test_queue = NULL;
	queue_t *src_queue = NULL;
		
	test_queue = QueueCreate();
	src_queue = QueueCreate();
	
	TestQueueIsEmpty(test_queue);
	
	printf("Inserting four values:\n");
	TestQueueEnqueue(test_queue, &val1);
	TestQueueEnqueue(test_queue, &val2);
	TestQueueEnqueue(test_queue, &val3);
	TestQueueEnqueue(test_queue, &val4);
	PrintQueue(test_queue);
	
	TestQueuePeek(test_queue, val1);
	TestQueueDequeue(test_queue);
	printf("After one Dequeue:\n");
	PrintQueue(test_queue);
	TestQueueSize(test_queue, 3);
	
	/************************ Append *******************************/
	
	printf("Creating src by inserting values:\n");
	TestQueueEnqueue(src_queue, &val5);
	TestQueueEnqueue(src_queue, &val6);
	TestQueueEnqueue(src_queue, &val7);
	
	printf("Before Queue Append, dest is:\n");
	PrintQueue(test_queue);
	printf("Before Queue Append, src is:\n");
	PrintQueue(src_queue);
	
	TestQueueAppend(test_queue, src_queue);
	printf("After Queue Append:\n");
	PrintQueue(test_queue);
	
	QueueDestroy(test_queue);
	QueueDestroy(src_queue);
	
	return 0;
}

static void TestQueueIsEmpty(queue_t *queue)
{
	printf(U_LINE"Test Queue IsEmpty:\n"RESET);
	
	if (1 == QueueIsEmpty(queue))
	{
		printf(GRN"SUCCESS!"RESET"\n\n");
	}
	
	else
	{
		printf(RED"FAILURE!"RESET"\n\n");
	}
}

static void TestQueueEnqueue(queue_t *queue, int *value)
{	
	printf(U_LINE"Test Queue Enqueue:\n"RESET);
	
	if (0 == QueueEnqueue(queue, (void *)value))
	{
		printf(GRN"SUCCESS!"RESET"\n\n");
	}
	
	else
	{
		printf(RED"FAILURE!"RESET"\n\n");
	}	
}

static void TestQueuePeek(queue_t *queue, int value)
{
	printf(U_LINE"Test Queue Peek:\n"RESET);	
		
	if (value == *(int *)QueuePeek(queue))
	{
		printf(GRN"SUCCESS!"RESET"\n\n");
	}
	
	else
	{
		printf(RED"FAILURE!"RESET"\n\n");
	}
}

static void TestQueueDequeue(queue_t *queue)
{
	int *peek_value = (int *)QueuePeek(queue);
	
	printf(U_LINE"Test Queue Dequeue:\n"RESET);
	QueueDequeue(queue);
	
	if (peek_value != (int *)QueuePeek(queue))
	{
		printf(GRN"SUCCESS!"RESET"\n\n");
	}
	
	else
	{
		printf(RED"FAILURE!"RESET"\n\n");
	}
}

static void TestQueueSize(queue_t *queue, size_t size)
{
	printf(U_LINE"Test Queue Size:\n"RESET);
	
	if (size == QueueSize(queue))
	{
		printf(GRN"SUCCESS!"RESET"\n\n");
	}
	
	else
	{
		printf(RED"FAILURE!"RESET"\n\n");
	}
}

static void TestQueueAppend(queue_t *dest, queue_t *src)
{
	size_t dest_size = QueueSize(dest);
	size_t src_size = QueueSize(src);
	size_t afte_append_size = 0;
	
	dest = QueueAppend(dest, src);
	afte_append_size = QueueSize(dest);
	
	printf(U_LINE"Test Queue Append:\n"RESET);
	
	if (afte_append_size == (dest_size + src_size))
	{
		printf(GRN"SUCCESS!"RESET"\n\n");
	}
	
	else
	{
		printf(RED"FAILURE!"RESET"\n\n");
	}
}

