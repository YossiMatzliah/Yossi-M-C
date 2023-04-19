/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :		  				*
*	Date      : 19/04/2023			*
************************************/

#include <errno.h>	/* errno */
#include <stdlib.h>	/* malloc, free */
#include <assert.h>	/* assert */
#include <stdio.h>  /* perror */

#include "pq_by_heap.h"
#include "heap.h"

#define TRUE  (1)
#define FALSE (0)

struct pq
{
	heap_t *heap;
};

/********************************************************************/

pq_t *PQCreate(int (*priority_func)(const void *lhs, const void *rhs))
{
	pq_t *new_pq = NULL;
	
	assert(NULL != priority_func);
	
	new_pq = (pq_t *)malloc(sizeof(pq_t));
	if (NULL == new_pq)
	{
		errno = ENOMEM;
		perror("Allocation Failed\n");
		return NULL;
	}
	
	new_pq->heap = HeapCreate(priority_func);
	if (NULL == new_pq->heap)
	{
		free(new_pq);
		errno = ENOMEM;
		perror("Allocation Failed\n");
		return NULL;
	}
	
	return new_pq;
}

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);
	
	HeapDestroy(pq->heap);
	pq->heap = NULL;
	
	free(pq);
	pq = NULL;
}

int PQEnqueue(pq_t *pq, void *data)
{
	assert(NULL != pq);
	assert(NULL != data);
	
	return HeapPush(pq->heap, data);
}

void PQDequeue(pq_t *pq)
{
	assert(NULL != pq);
	
	HeapPop(pq->heap);
}

void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapPeek(pq->heap);
}

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapIsEmpty(pq->heap);
}

size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapSize(pq->heap);
}

void *PQErase(pq_t *pq, int (*is_match)(const void *data, const void *param), void *param)
{
	assert(NULL != pq);
	assert(NULL != is_match);

	return HeapRemove(pq->heap, is_match, param);
}
	
void PQClear(pq_t *pq)
{
	assert(NULL != pq);
	
	while (TRUE != PQIsEmpty(pq))	
	{
		PQDequeue(pq);
	}
}
	
