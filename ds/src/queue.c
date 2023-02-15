/**************************************
*	Developer :	Yossi Matzliah        *
*	Date      : 12/02/2023			  *
*	Reviewer  :	Oran				  *
**************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* perror */

#include "../../ds/include/linked_list.h"
#include "../../ds/include/queue.h"

struct queue
{
    sll_t *list;
};

/**********************************************************/

queue_t *QueueCreate(void)
{
	queue_t *new_queue = (queue_t *)malloc(sizeof(queue_t));
	
	if (NULL == new_queue)
	{
		perror("Allocation Failed\n");
		
		return NULL;
	}
	
	new_queue->list = SLLCreate(); 
	/* add if NULL == new_queue->list free it and put NULL */
	
	return new_queue;
}

void QueueDestroy(queue_t *queue)
{
	assert(NULL != queue);
	
	SLLDestroy(queue->list);
	free(queue); 
}

void QueueDequeue(queue_t *queue)
{
	assert(NULL != queue);
	
	SLLRemove(SLLBeginIter(queue->list));
}
   
int QueueEnqueue(queue_t *queue, void *data)
{	
	iterator_t iter = NULL;
	
	assert(NULL != queue);
	assert(NULL != data); /* remove */

	iter = SLLInsertBefore(SLLEndIter(queue->list), data);
	
	return ((iter != SLLEndIter(queue->list))? 0 : 1 ); /* should use func IsSameIter */
}

void *QueuePeek(const queue_t *queue)
{
	assert (NULL != queue);
	
	return SLLGetData(SLLBeginIter(queue->list));
}

int QueueIsEmpty(const queue_t *queue)
{
	assert (NULL != queue);
	
	return SLLIsEmpty(queue->list);
}

size_t QueueSize(const queue_t *queue)
{
	assert(NULL != queue);
	
	return SLLCount(queue->list);
}
	
queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	dest->list = SLLAppend(dest->list, src->list);
	
	return dest;
}

void PrintQueue(const queue_t *queue)
{
	iterator_t iter = NULL;
	assert(NULL != queue);
	
	iter = SLLBeginIter(queue->list);
	
	while (NULL != SLLNextIter(iter))
	{
		printf("(%d)---->", *(int *)SLLGetData(iter));
		iter = SLLNextIter(iter);
	}
	
	printf("NULL\n\n");
}
