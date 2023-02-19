/**************************************
*	Developer :	Yossi Matzliah        *
*	Reviewer  :	Oran Freidin		  *
*	Date      : 18/02/2023			  *
**************************************/

#include <stdio.h>	/*perror */
#include <errno.h>	/*errno */
#include <stdlib.h>	/*malloc, free */
#include <assert.h>	/*assert */

#include "../../ds/include/dll.h"

#define TRUE (1)
#define FALSE (0)

typedef struct node node_t;	

struct node
{
	void *data;
	node_t *next;
	node_t *prev;
};

struct doubly_linked_list
{
	node_t *head;
	node_t *tail;
};

/***********************************************************/

static int CountNode(void *data, void *parameter);
static void InitNode(node_t *node ,void *data, node_t *next_node, node_t *prev_node);

/***********************************************************/

dll_t *DLLCreate(void)
{
	node_t *dummy_tail = NULL;
	node_t *dummy_head = NULL;
	dll_t *new_dll = NULL;
	
	new_dll = (dll_t *)malloc(sizeof(dll_t));
	if (NULL == new_dll)
	{
		errno = ENOMEM;
    	perror("Failed to malloc memory for new node\n");
	}
	else
	{
		dummy_tail = (node_t *)malloc(sizeof(node_t));
		if (NULL == dummy_tail)
		{
			errno = ENOMEM;
			perror("Failed to malloc memory for new node\n");
			free(new_dll);
		}
		
		else
		{
			dummy_head = (node_t *)malloc(sizeof(node_t));
			if (NULL == dummy_head)
			{
				errno = ENOMEM;
				perror("Failed to malloc memory for new node\n");
				free(new_dll);
				free(dummy_tail);
			}
			
			else
			{
				InitNode(dummy_tail, new_dll, NULL, dummy_head);
				InitNode(dummy_head, new_dll, dummy_tail, NULL);
				
				new_dll->head = dummy_head;
				new_dll->tail = dummy_tail;
			}
		}
	}
	
	return new_dll;
}

void DLLDestroy(dll_t *dll)
{
	node_t *delete_node = NULL;
	
	assert(NULL != dll);
	
	while (NULL != dll->head)
	{
		delete_node = dll->head;
		dll->head = dll->head->next;
		free(delete_node);
	}
	
	free(dll);
}

int DLLIsEmpty(const dll_t *dll)
{
	assert(NULL != dll);
	
	return (DLLBeginIter(dll) == DLLEndIter(dll));
}

void DLLSetData(const iterator_t iterator, void *data)
{
	assert(NULL != iterator);
	assert(NULL != iterator->next);
	assert(NULL != iterator->prev);
	
	iterator->data = data;
}

void *DLLGetData(iterator_t iterator)
{
	assert(NULL != iterator);
	assert(NULL != iterator->next);
	assert(NULL != iterator->prev);
	
	return iterator->data;
}

iterator_t DLLBeginIter(const dll_t *dll)
{
	assert(NULL != dll);
	
	return dll->head->next;
}

iterator_t DLLEndIter(const dll_t *dll)
{
	assert(NULL != dll);
	
	return dll->tail;
}

iterator_t DLLNextIter(const iterator_t iterator)
{
	assert(NULL != iterator);
	
	return iterator->next;
}

iterator_t DLLPrevIter(const iterator_t iterator)
{
	assert(NULL != iterator);
	
	return iterator->prev;
}

int DLLIsSameIter(const iterator_t iter1, const iterator_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);
	
	return (iter1 == iter2);
}

size_t DLLCount(const dll_t *dll)
{
	size_t counter = 0;
	
	assert(NULL != dll);
	
	DLLForEach(DLLBeginIter(dll), DLLEndIter(dll), CountNode, (void *)&counter);
	
	return counter;
}

iterator_t DLLInsert(iterator_t iterator, void *data)
{
	node_t *new_node = NULL;
	node_t *return_node = NULL;
	
	assert(NULL != iterator);
	assert(NULL != data);
	
	if (NULL == iterator->prev)
	{
		iterator = DLLNextIter(iterator);
	}
	
	new_node = (node_t *)malloc(sizeof(node_t));
	if (NULL == new_node)
	{
		errno = ENOMEM;
    	perror("Failed to malloc memory for new node\n");
		
		while (NULL != DLLNextIter(iterator))
		{
			iterator = DLLNextIter(iterator);
		}
		
		return_node = iterator;
	}
	
	else
	{		
		InitNode(new_node, data, iterator, iterator->prev);
		
		iterator->prev->next = new_node;
		iterator->prev = new_node;
		
		return_node = new_node;
	}
	
	return return_node;
}

iterator_t DLLRemove(iterator_t iterator)
{
	iterator_t return_iter = NULL;
	
	assert(NULL != iterator);
	assert(NULL != iterator->next);
	assert(NULL != iterator->prev);
	
	return_iter = iterator->next;
	
	iterator->prev->next = iterator->next;
	iterator->next->prev = iterator->prev;
	free(iterator);

	return return_iter;
}

iterator_t DLLPushBack(dll_t *dll, void *data)	
{
	assert(NULL != dll);
	assert(NULL != data);
	
	return DLLInsert(DLLEndIter(dll), data);
}

void *DLLPopBack(dll_t *dll)
{
	iterator_t *data = NULL;
	
	assert(NULL != dll);
	
	data = DLLGetData(dll->tail->prev);
	DLLRemove(dll->tail->prev);
	
	return data;
}

iterator_t DLLPushFront(dll_t *dll, void *data)
{
	assert(NULL != dll);
	assert(NULL != data);
	
	return DLLInsert(DLLBeginIter(dll), data);
}

void *DLLPopFront(dll_t *dll)
{
	void *data = NULL;
	
	assert(NULL != dll);
	
	data = DLLGetData(DLLBeginIter(dll));
	DLLRemove(DLLBeginIter(dll));
	
	return data;
}

int DLLForEach(iterator_t from, const iterator_t to, action_func_t user_func, void *param)	
{
	int return_val = FALSE;
	iterator_t iter = NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != user_func);
	
	iter = from;
	
	while (to != iter && FALSE == return_val)
	{
		return_val = user_func(iter->data, param);
		iter = DLLNextIter(iter);
	}
	
	return return_val;
}

iterator_t DLLFind(iterator_t from, iterator_t to, is_match_t user_func, void *param)
{
	iterator_t iter = NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != user_func);
	
	iter = from;
	
	while (to != iter && (FALSE == user_func(iter->data, param)))
	{
		iter = DLLNextIter(iter);
	}
	
	return iter;
}

dll_t *DLLMultiFind(dll_t *dll_dest, iterator_t from, iterator_t to, is_match_t user_func, void *param)
{
	iterator_t from_to_iter = NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != user_func);
	
	from_to_iter = from;
	
	while (to != from_to_iter)
	{
		if (TRUE == user_func(from_to_iter->data, param))
		{
			DLLPushBack(dll_dest, param);
		}
		
		from_to_iter = DLLNextIter(from_to_iter);
	}
	
	return dll_dest;
}

iterator_t DLLSplice(iterator_t dest, iterator_t src_from ,iterator_t src_to)
{
    iterator_t src_to_prev = NULL;
    
    assert(NULL != dest);
    assert(NULL != dest->prev);
    assert(NULL != src_from);
    assert(NULL != src_to);
    
    src_to_prev = src_to->prev;
    
    src_from->prev->next = src_to;
    src_to->prev = src_from->prev;
    
    src_from->prev = dest->prev;
    src_to_prev->next = dest;
    
    dest->prev->next = src_from;
    dest->prev = src_to_prev;
    
	return dest;
}

/********************* Extra functions *************************/

static int CountNode(void *data, void *parameter)
{
	assert(NULL != data);
	assert(NULL != parameter);
	
	(void)data;
	++(*(size_t *)parameter);
	
	return 0;
}

static void InitNode(node_t *node ,void *data, node_t *next_node, node_t *prev_node)
{
	node->data = data;
	node->next = next_node;
	node->prev = prev_node;
}

