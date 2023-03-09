/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Moshe	  			*
*	Date      : 28/02/2023			*
************************************/

#include <errno.h>	/* errno */
#include <stdlib.h>	/* malloc, free */
#include <assert.h>	/* assert */
#include <stdio.h>  /* perror */

#include "../include/pq.h"
#include "../include/sorted_list.h"

#define TRUE  (1)
#define FALSE (0)

struct pq
{
	sol_t *list;
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
	
	new_pq->list = SortedListCreate(priority_func);
	if (NULL == new_pq->list)
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
	
	SortedListDestroy(pq->list);
	pq->list = NULL;
	
	free(pq);
	pq = NULL;
}

int PQEnqueue(pq_t *pq, void *data)
{
	sol_iterator_t new_element = {0};
	
	assert(NULL != pq);
	assert(NULL != data);
	
	new_element = SortedListInsert(pq->list, data);
	
	return !(SortedListGetData(new_element) == data);
}

void PQDequeue(pq_t *pq)
{
	assert(NULL != pq);
	
	SortedListPopFront(pq->list);
}

void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);
	
	return SortedListGetData(SortedListBeginIter(pq->list));
}

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	
	return SortedListIsEmpty(pq->list);
}

size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);
	
	return SortedListSize(pq->list);
}

void *PQErase(pq_t *pq, int (*is_match)(const void *data, const void *param), void *param)
{
	void *data = NULL;
	sol_iterator_t list_iter = {0};
	
	assert(NULL != pq);
	assert(NULL != is_match);
	
	if (TRUE != PQIsEmpty(pq))
	{
		list_iter = SortedListFindIf(SortedListBeginIter(pq->list), SortedListEndIter(pq->list), is_match, param);
		
		data = SortedListGetData(list_iter);
		SortedListRemove(list_iter);
	}
	
	return data;
}
	
void PQClear(pq_t *pq)
{
	assert(NULL != pq);
	
	while (TRUE != PQIsEmpty(pq))	
	{
		SortedListPopFront(pq->list);
	}
}
	
pq_t *PQMerge(pq_t *pq_dest, pq_t *pq_src)
{
	assert(NULL != pq_dest);
	assert(NULL != pq_src);
	
	pq_dest->list = SortedListMerge(pq_dest->list, pq_src->list);
	
	return pq_dest;
}


