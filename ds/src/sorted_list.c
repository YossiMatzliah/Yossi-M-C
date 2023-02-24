/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Omri	  			*
*	Date      : 20/02/2023			*
************************************/

#include <errno.h>	/* errno */
#include <stdlib.h>	/* malloc */
#include <assert.h>	/* assert */
#include <stdio.h> /* perror */

#include "../include/sorted_list.h"

#define TRUE (1)
#define FALSE (0)

struct sorted_linked_list
{
	dll_t *list;
	cmp_func_st user_func;
};

/**************************************************/

static int IsBefore(sol_t *sol, const void *num_in_list, const void *num_to_check);

/**************************************************/

sol_t *SortedListCreate(cmp_func_st user_func)
{
	sol_t *sorted_list = NULL;
	/* assert user_func */
	sorted_list = (sol_t *)malloc(sizeof(sol_t));
	if (NULL == sorted_list)
	{
		errno = ENOMEM;
    	perror("Error");
	}
	
	else
	{
		sorted_list->list = DLLCreate();
		sorted_list->user_func = user_func;
	}
	
	return sorted_list;
}

void SortedListDestroy(sol_t *sol)
{
	assert(NULL != sol);
	
	DLLDestroy(sol->list);
	free(sol);
}

int SortedListIsEmpty(const sol_t *sol)
{
	assert(NULL != sol);
	
	return DLLIsEmpty(sol->list);
}

size_t SortedListSize(const sol_t *sol)
{
	assert(NULL != sol);
	
	return DLLCount(sol->list);
}

iterator_st SortedListInsert(sol_t *sol, void *data)
{
	iterator_st iter_position = {NULL};
	iterator_st inserted_node = {NULL};
	
	assert(NULL != sol);
	assert(NULL != data);
	
	iter_position = SortedListFind(sol, SortedListBeginIter(sol), SortedListEndIter(sol), data); /* find need to find the exact data, and return iter to the node, if not return end. need to use findif for insert or dllfind */
	
	inserted_node.dll_iterator = DLLInsert(iter_position.dll_iterator, data);
	
	#ifndef NDEBUG
	inserted_node.dll = sol->list;
	#endif
	
	return inserted_node;
}

iterator_st SortedListRemove(iterator_st iterator)
{
	iterator_st next_iter = {NULL};
	
	assert(NULL != iterator.dll_iterator);
	
	#ifndef NDEBUG
    next_iter.dll = iterator.dll;
    #endif
    
	next_iter.dll_iterator = DLLRemove(iterator.dll_iterator);
    
	return next_iter;
}

void *SortedListPopBack(sol_t *sol)
{
	assert(NULL != sol);
	
	return DLLPopBack(sol->list);
}

void *SortedListPopFront(sol_t *sol)
{
	assert(NULL != sol);
	
	return DLLPopFront(sol->list);
}

iterator_st SortedListFindIf(iterator_st from, iterator_st to, is_match_t user_func, void *param)
{
	assert(NULL != from.dll_iterator);
	assert(NULL != to.dll_iterator);
	assert(NULL != user_func);
	
	#ifndef NDEBUG
	if (from.dll != to.dll)
	{
		return to;
	}
	#endif
	
	while (TRUE != SortedListIsSameIter(to, from) && (FALSE == user_func(SortedListGetData(from), param)))
	{
		from = SortedListNextIter(from);
	}
	
	return from;
}

iterator_st SortedListFind(sol_t *sol, iterator_st from, iterator_st to, const void *to_find)
{
	int is_before = FALSE;
	
	assert(NULL != sol);
	assert(NULL != from.dll_iterator);
	assert(NULL != to.dll_iterator);
	/*assert (from.dll != to.dll) */
	
	#ifndef NDEBUG
	if (from.dll != to.dll) /*  */
	{
		return to;
	}
	#endif
	
	while (TRUE != SortedListIsSameIter(to, from) && (FALSE == is_before))
	{
		is_before = IsBefore(sol, SortedListGetData(from), to_find);
		if (TRUE == is_before)
		{
			return from;
		}
		from = SortedListNextIter(from);
	}
	
	return from;
}

int SortedListForEach(iterator_st from, iterator_st to, action_func_t user_func, void *param)
{
	assert(NULL != from.dll_iterator);
	assert(NULL != to.dll_iterator);
	assert(NULL != user_func);
	
	#ifndef NDEBUG
	if (from.dll != to.dll)
	{
		return -1;
	}
	#endif
	
	return DLLForEach(from.dll_iterator, to.dll_iterator, user_func, param);
}

void *SortedListGetData(iterator_st iterator)
{
	assert(NULL != iterator.dll_iterator);
	
	return DLLGetData(iterator.dll_iterator);
}

iterator_st SortedListBeginIter(const sol_t *sol)
{
	iterator_st begin_iter = {NULL};
	
	assert(NULL != sol);
	
	begin_iter.dll_iterator = DLLBeginIter(sol->list);
	
	#ifndef NDEBUG
	begin_iter.dll = sol->list;
	#endif
	
	return begin_iter;
}

iterator_st SortedListEndIter(const sol_t *sol)
{
	iterator_st end_iter = {NULL};
	
	assert(NULL != sol);
	
	end_iter.dll_iterator = DLLEndIter(sol->list);
	
	#ifndef NDEBUG
	end_iter.dll = sol->list;
	#endif
	
	return end_iter;
}

iterator_st SortedListNextIter(iterator_st iterator)
{
	iterator_st next_iter = {NULL};
		
	assert(NULL != iterator.dll_iterator);
	
	next_iter.dll_iterator = DLLNextIter(iterator.dll_iterator);
	
	#ifndef NDEBUG
    next_iter.dll = iterator.dll;
    #endif
    
	return next_iter;
}

iterator_st SortedListPrevIter(iterator_st iterator)
{
	iterator_st prev_iter = {NULL};
	
	assert(NULL != iterator.dll_iterator);
	
	prev_iter.dll_iterator = DLLPrevIter(iterator.dll_iterator);
	
	#ifndef NDEBUG
    prev_iter.dll = iterator.dll;
    #endif
    
	return prev_iter;
}

int SortedListIsSameIter(iterator_st iter1, iterator_st iter2)
{
	assert(NULL != iter1.dll_iterator);
	assert(NULL != iter2.dll_iterator);
	
	#ifndef NDEBUG
	assert(iter1.dll == iter2.dll);
	#endif
	
	return DLLIsSameIter(iter1.dll_iterator, iter2.dll_iterator);
}

sol_t *SortedListMerge(sol_t *dest_sol, sol_t *src_sol)
{
	iterator_st from_iter = {NULL};
	iterator_st to_iter = {NULL};
	iterator_st src_merge_iter = {NULL};
	iterator_st dest_splice_iter = {NULL};
	
	assert(NULL != dest_sol);
	assert(NULL != src_sol);
	
	from_iter = SortedListBeginIter(dest_sol);
	to_iter = SortedListEndIter(dest_sol);
	src_merge_iter = SortedListBeginIter(src_sol);
	
	while (TRUE != SortedListIsEmpty(src_sol))
	{
		dest_splice_iter = SortedListFind(dest_sol, from_iter, to_iter, SortedListGetData(src_merge_iter));	/* findif with IsBigger */
		
		/* should use another while to advance 'to' till not bigger and than do splice */
		DLLSplice(dest_splice_iter.dll_iterator, src_merge_iter.dll_iterator, DLLNextIter(src_merge_iter.dll_iterator));
		src_merge_iter = SortedListBeginIter(src_sol);
		from_iter = dest_splice_iter;
	}
	
	return dest_sol;	
}

static int IsBefore(sol_t *sol, const void *num_in_list, const void *num_to_check)
{
	return (0 < sol->user_func(num_in_list, num_to_check));
}
