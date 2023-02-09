/**************************************
*	Developer :	Yossi Matzliah        *
*	Date      : 09/02/2023			  *
*	Reviewer  :	Lilach				  *
**************************************/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/
#include <stdio.h> /* perror */

#include "../../ds/include/linked_list.h"

struct Node
{
    void *data;
    node_t *next;
};

struct SingleLinkedList
{
	node_t *head;
	node_t *tail;
};

/**********************************************************/

sll_t *SLLCreate()
{
	node_t *dummy = NULL;
	
	sll_t *new_list = (sll_t *) malloc(sizeof(sll_t));
	if (NULL == new_list)
	{
		perror("Allocation Failed\n");
		
		return NULL;
	}

	dummy = (node_t *)malloc(sizeof(node_t));
	if (NULL == dummy)
	{
		perror("Allocation Failed\n");
		free(new_list);
		
		return NULL;
	}
	
	dummy->data = (void *)new_list; 
	dummy->next = NULL;
	
	new_list->head = dummy;
	new_list->tail = dummy;
	
	return new_list;
}

void SLLDestroy(sll_t *sll)
{
	assert(NULL != sll);
	while (!SLLIsEmpty(sll))
	{
		sll->head = SLLRemove(sll->head);
	}
	free(sll->head);
	free(sll);
}

iterator_t SLLBeginIter(const sll_t *sll)
{
	assert(NULL != sll);
	
	return sll->head;
}

iterator_t SLLNextIter(const iterator_t iterator)
{
	assert(NULL != iterator);
	
	return iterator->next;
}

iterator_t SLLEndIter(const sll_t *sll)
{
	assert(NULL != sll);
	
	return sll->tail;
}

iterator_t SLLRemove(iterator_t iterator)
{
	iterator_t next_iter = NULL;
	
	assert(NULL != iterator);
		
	next_iter = iterator->next;
	
	if (NULL == iterator->next)
	{
		free(next_iter);
		return NULL;
	}
	
	iterator->data = next_iter->data;
	iterator->next = next_iter->next;
	free(next_iter);
	
	return iterator;
}

iterator_t SLLInsertBefore(iterator_t iterator, void *data)
{	
	iterator_t new_node = NULL;
	
	assert(NULL != iterator);
	assert(NULL != data); 

	new_node = (node_t *)malloc(sizeof(node_t));
	if (NULL == new_node)
	{
		perror("Allocation Failed\n");
		
		while (NULL != iterator->next)
		{
			iterator = iterator->next;
		}
		
		return iterator;
	}
	
	new_node->next = iterator->next;
	new_node->data = iterator->data;
	
	iterator->next = new_node;
	iterator->data = data;
	
	if (NULL == new_node->next)
	{
		((sll_t*)new_node->data)->tail = new_node;
	}
	
	return iterator;
}

void *SLLGetData(iterator_t iterator)
{
	assert(NULL != iterator);
	
	return iterator->data;
}
	
void SLLSetData(const iterator_t iterator, void *data)
{
	assert(NULL != iterator);
	assert(NULL != data);
	
	iterator->data = data;
}

int SLLIsSameIter(const iterator_t iter1, const iterator_t iter2)
{	
	assert(NULL != iter1);
	assert(NULL != iter2);
	
	return (iter1 == iter2);
}

int SLLIsEmpty(const sll_t *sll)
{
	assert(NULL != sll);
	
	return (NULL == sll->head->next);
}

size_t SLLCount(const sll_t *sll)
{
	size_t counter = 0;
	iterator_t iter = NULL;
	
	assert(NULL != sll);
	
	iter = sll->head;
	
	while (NULL != SLLNextIter(iter))
	{
		++counter;
		iter = SLLNextIter(iter);
	}
	
	return counter;
}
	
int SLLForEach(iterator_t from, const iterator_t to, action_func user_func, void *param)
{
	int return_val = 0;
	iterator_t iter = from;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != user_func);
	assert(NULL != param);
	
	while (to != iter)
	{
		return_val = user_func(iter->data, param);
		if (0 != return_val)
		{
			break;
		}
		
		iter = SLLNextIter(iter);
	}
	
	return return_val;
}

iterator_t SLLFind(iterator_t from, iterator_t to, is_match user_func, void *param)
{
	assert (NULL != from);
	assert (NULL != to);
	assert (NULL != user_func);
	
	while (!SLLIsSameIter(from, to))
	{		
		if(1 == user_func(from->data, param))
		{
			break;
		}		
		from = SLLNextIter(from);
	}
	
	return from;
}
	
sll_t *SLLAppend(sll_t *dest ,sll_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);

	dest->tail->data = src->head->data;
	dest->tail->next = src->head->next;
	
	src->tail->data = (void *)dest;
	
	src->head->next = NULL;
	src->head->data = (void *)src;

	dest->tail = src->tail;
	src->tail = src->head;
	
	return dest;
}


