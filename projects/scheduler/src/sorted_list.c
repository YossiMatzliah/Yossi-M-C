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

typedef struct cmp_wrapper cmp_wrapper_t;

struct sorted_linked_list
{
	dll_t *list;
	cmp_func_st user_func;
};

struct cmp_wrapper
{
	cmp_func_st cmp;
	void *param;
};

/**************************************************/

static int IsBiggerCmp(const void *data, const void *wrapper);
static int CmpToIsMatch(const void *data, const void *wrapper);

/**************************************************/

sol_t *SortedListCreate(cmp_func_st compare_func)
{
	sol_t *sorted_list = NULL;
	
	assert(NULL != compare_func);
 
	sorted_list = (sol_t *)malloc(sizeof(sol_t));
	if (NULL == sorted_list)
	{
		errno = ENOMEM;
    	perror("Error");
	}
	
	else
	{
		sorted_list->list = DLLCreate();
		sorted_list->user_func = compare_func;
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

sol_iterator_t SortedListInsert(sol_t *sol, void *data)
{
	cmp_wrapper_t wrap = {0};
	sol_iterator_t insert_position_iter = {0};
	
	assert(NULL != sol);
	
	wrap.cmp = sol->user_func;
	wrap.param = data;
	
	insert_position_iter = SortedListFindIf(SortedListBeginIter(sol), SortedListEndIter(sol), IsBiggerCmp, &wrap);
	
	insert_position_iter.dll_iterator = DLLInsert(insert_position_iter.dll_iterator, data);
	
	#ifndef NDEBUG
	insert_position_iter.dll = sol->list;
	#endif	

	return insert_position_iter;

}

sol_iterator_t SortedListRemove(sol_iterator_t iterator)
{
	sol_iterator_t next_iter = {NULL};
	
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

sol_iterator_t SortedListFindIf(sol_iterator_t from, sol_iterator_t to, is_match_t user_func, void *param)
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
	
	from.dll_iterator = DLLFind(from.dll_iterator, to.dll_iterator, user_func, param);
	
	return from;
}

sol_iterator_t SortedListFind(sol_t *sol, sol_iterator_t from, sol_iterator_t to, const void *to_find)
{
	cmp_wrapper_t wrap = {0};
	
	assert(NULL != sol);
	assert(NULL != from.dll_iterator);
	assert(NULL != to.dll_iterator);
	assert(from.dll_iterator != to.dll_iterator);
	
	#ifndef NDEBUG
	if (from.dll != to.dll)
	{
		return to;
	}
	#endif
	
	wrap.cmp = sol->user_func;
	wrap.param = (void *)to_find;
	
	from.dll_iterator = DLLFind(from.dll_iterator, to.dll_iterator, CmpToIsMatch, &wrap);

	return from;
}

int SortedListForEach(sol_iterator_t from, sol_iterator_t to, action_func_t user_func, void *param)
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

void *SortedListGetData(sol_iterator_t iterator)
{
	assert(NULL != iterator.dll_iterator);
	
	return DLLGetData(iterator.dll_iterator);
}

sol_iterator_t SortedListBeginIter(const sol_t *sol)
{
	sol_iterator_t begin_iter = {NULL};
	
	assert(NULL != sol);
	
	begin_iter.dll_iterator = DLLBeginIter(sol->list);
	
	#ifndef NDEBUG
	begin_iter.dll = sol->list;
	#endif
	
	return begin_iter;
}

sol_iterator_t SortedListEndIter(const sol_t *sol)
{
	sol_iterator_t end_iter = {NULL};
	
	assert(NULL != sol);
	
	end_iter.dll_iterator = DLLEndIter(sol->list);
	
	#ifndef NDEBUG
	end_iter.dll = sol->list;
	#endif
	
	return end_iter;
}

sol_iterator_t SortedListNextIter(sol_iterator_t iterator)
{
	sol_iterator_t next_iter = {NULL};
		
	assert(NULL != iterator.dll_iterator);
	
	next_iter.dll_iterator = DLLNextIter(iterator.dll_iterator);
	
	#ifndef NDEBUG
    next_iter.dll = iterator.dll;
    #endif
    
	return next_iter;
}

sol_iterator_t SortedListPrevIter(sol_iterator_t iterator)
{
	sol_iterator_t prev_iter = {NULL};
	
	assert(NULL != iterator.dll_iterator);
	
	prev_iter.dll_iterator = DLLPrevIter(iterator.dll_iterator);
	
	#ifndef NDEBUG
    prev_iter.dll = iterator.dll;
    #endif
    
	return prev_iter;
}

int SortedListIsSameIter(sol_iterator_t iter1, sol_iterator_t iter2)
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
	sol_iterator_t dest_run = {0};
	sol_iterator_t src_run = {0};
	
	assert(NULL != dest_sol);
	assert(NULL != src_sol);
	
	dest_run = SortedListBeginIter(dest_sol);
	src_run = SortedListBeginIter(src_sol);
	
	while (TRUE != SortedListIsEmpty(src_sol))
	{
		while ((NULL != SortedListNextIter(dest_run).dll_iterator) && (0 < dest_sol->user_func(SortedListGetData(src_run), SortedListGetData(dest_run))))
		{
			dest_run = SortedListNextIter(dest_run);
		}
		
		while ((NULL != SortedListNextIter(src_run).dll_iterator) && (NULL != SortedListNextIter(dest_run).dll_iterator) &&
				(0 >= dest_sol->user_func(SortedListGetData(src_run), SortedListGetData(dest_run))))
		{
			src_run = SortedListNextIter(src_run);
		}
		
		if (NULL == SortedListNextIter(dest_run).dll_iterator)
		{
			while (NULL != SortedListNextIter(src_run).dll_iterator)
			{
				src_run = SortedListNextIter(src_run);
			}
		}
		
		dest_run.dll_iterator = DLLSplice(dest_run.dll_iterator, SortedListBeginIter(src_sol).dll_iterator, src_run.dll_iterator);
		src_run = SortedListBeginIter(src_sol);
	}
	
	return dest_sol;
}

static int IsBiggerCmp(const void *data, const void *wrapper)
{
	const cmp_wrapper_t *wrap = (cmp_wrapper_t *)wrapper;
	cmp_func_st compare;
	
	assert(NULL != wrapper);

	compare = wrap->cmp;

	return (compare(data, wrap->param) > 0);
}

static int CmpToIsMatch(const void *data, const void *wrapper)
{
	const cmp_wrapper_t *wrap = (cmp_wrapper_t *)wrapper;
	cmp_func_st compare;
	
	assert(NULL != wrap);

	compare = wrap->cmp;

	return !(compare(data, wrap->param));
}

