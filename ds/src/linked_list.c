/**************************************
*	Developer :	Yossi Matzliah        *
*	Date      : 09/02/2023			  *
*	Reviewer  :	Lilach				  *
**************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* perror */

#include "../../ds/include/linked_list.h"
/* typedef need to be here */
struct Node /* node */
{
    void *data;
    node_t *next;
};

struct SingleLinkedList /* single_linked_list */
{
	node_t *head;
	node_t *tail;
};

/**********************************************************/

sll_t *SLLCreate(void)
{
	node_t *dummy = NULL;
	sll_t *new_list = (sll_t *)malloc(sizeof(sll_t));
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
	
	dummy->data = (void *)new_list; /* in a func InitNode */
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
	/* assert(NULL != iterator->next);  */	
	return iterator->next;
}

iterator_t SLLEndIter(const sll_t *sll)
{
	assert(NULL != sll);
	
	return sll->tail;
}

iterator_t SLLRemove(iterator_t iterator)
{
	iterator_t remove_node = NULL;
	
	assert(NULL != iterator);
	/* assert(NULL != iterator->next); because we said he should not touch dummy*/	
	remove_node = iterator->next;
	
	if (NULL != iterator->next) /**/
	{
		iterator->data = SLLNextIter(iterator)->data; /* should use SetData or InitNode */
		iterator->next = SLLNextIter(iterator)->next;
		free(remove_node);
	}
	/* should add the if with the iterator->next like did with InsertBefore */
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
		
		while (NULL != iterator->next)  /* could be in func */
		{
			iterator = iterator->next; /* if using iter use func IterNext */
		}
		
		return iterator;
	}
	
	new_node->next = iterator->next; /* as said func IntiNode */
	new_node->data = iterator->data;
							/* Gidi said not need free space here, cause doing the same */
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
	assert(NULL != iterator->next); 
	
	return iterator->data;
}
	
void SLLSetData(const iterator_t iterator, void *data)
{
	assert(NULL != iterator);
	assert(NULL != data); /* remove, he can send NULL if want to, we don't do dereferance to it */ 
	assert(NULL != iterator->next); 
	
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

static int CountFunc(void *data, void *counter)
{
	assert(NULL != data);
	
	++(*(size_t *)counter);
	
	return 0;
}

size_t SLLCount(const sll_t *sll)
{
	size_t counter = 0;

	assert(NULL != sll);
	
	if (SLLForEach(SLLBeginIter(sll), SLLEndIter(sll), CountFunc, (void *)&counter))
	{
		counter = 0;
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
	assert(NULL != param); /* remove, could send NULL in param */
	
	while (to != iter && 0 == return_val)
	{
		return_val = user_func(iter->data, param);
		iter = SLLNextIter(iter);
	}
	
	return return_val;
}

iterator_t SLLFind(iterator_t from, iterator_t to, is_match user_func, void *param)
{
	assert (NULL != from);							
	assert (NULL != to);
	assert (NULL != user_func);
	
	while (!SLLIsSameIter(from, to) && (0 == user_func(from->data, param)))
	{		
		from = SLLNextIter(from);
	}
	
	return from;
}
	
sll_t *SLLAppend(sll_t *dest ,sll_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);

	dest->tail->data = src->head->data; /* in functions Init or SetNode  */
	dest->tail->next = src->head->next;
	
	src->tail->data = (void *)dest;
	
	src->head->next = NULL;
	src->head->data = (void *)src;

	dest->tail = src->tail;
	src->tail = src->head;
	
	return dest;
}


