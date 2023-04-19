/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	????				*
*	Date      : ?/04/2023			*
************************************/

#include <stdio.h>	/* perror */
#include <assert.h>	/* assert */
#include <errno.h>	/* errno */
#include <stdlib.h>	/* malloc */

#include "heap.h"
#include "dynamic_vector.h"

#define START_CAPACITY (3)
#define SUCCESS (0)
#define FAILURE (1)
#define TRUE 	(1)
#define FALSE 	(0)

#define GET_DATA(heap, index) (VectorGetAccessToElement(heap->vec, index))
#define LAST_ELEMENT_IDX(heap) (VectorSize(heap->vec) - 1) 
#define GET_PARENT_IDX(index) ((size_t)(((index) - 1) / (2)))
#define GET_LEFT_CHILD_IDX(index) ((2 * (index)) + 1)
#define GET_RIGHT_CHILD_IDX(index) ((2 * (index)) + 2)

struct heap 
{
	vector_t *vec;
    int (*cmp_func)(const void *, const void *);
};

/******************************** Static Functions *********************************/

static void HeapifyUp(const heap_t *heap);
static void HeapifyDown(const heap_t *heap, size_t index);
static void Swap(void **ptr1, void **ptr2);

/********************************** API Functions **********************************/

heap_t *HeapCreate(int(* cmp_func)(const void *, const void *))
{
	heap_t *new_heap = NULL;

	assert(NULL != cmp_func);

	new_heap = malloc(sizeof(heap_t));
	if (NULL == new_heap)
    {
        perror("Allocation Error");
        return NULL;
    }

	new_heap->vec = VectorCreate(START_CAPACITY, sizeof(void *));
	if (NULL == new_heap)
    {
        perror("Allocation Error");
		free(new_heap);
        return NULL;
    }

	new_heap->cmp_func = cmp_func;

	return new_heap;
}

void HeapDestroy(heap_t *heap)
{
	VectorDestroy(heap->vec);
	free(heap);
}

int HeapPush(heap_t *heap, void *data)  
{
    int status = SUCCESS;
    
    assert(NULL != heap);
    
    status = VectorPushBack(heap->vec, data);
    HeapifyUp(heap);
    
    return status;
}

void HeapPop(heap_t *heap)  
{
	size_t root_idx = 0;
    
    assert(NULL != heap);
    
    Swap(GET_DATA(heap, root_idx), GET_DATA(heap, LAST_ELEMENT_IDX(heap)));
    VectorPopBack(heap->vec);
    HeapifyDown(heap, root_idx);
}

void *HeapRemove(heap_t *heap, int (*is_match_func)(const void *data, const void *param), const void *param)
{
    size_t i = 0;
    size_t size = 0;
    void *removed_data = NULL;
    
    assert(NULL != heap);
    assert(NULL != is_match_func);
    
    size = HeapSize(heap);
    
    for (i = 0; i < size; ++i)
    {
        if (TRUE == is_match_func(GET_DATA(heap, i), param))
        {
            Swap(GET_DATA(heap, i), GET_DATA(heap, LAST_ELEMENT_IDX(heap)));
            removed_data = GET_DATA(heap, LAST_ELEMENT_IDX(heap));
            VectorPopBack(heap->vec);
            HeapifyDown(heap, i);
            break;
        }
    }
    
    return removed_data;
}

void *HeapRemoveByKey(heap_t *heap, void *data)
{
    size_t i = 0;
    size_t size = 0;
    void *removed_data = NULL;
    
    assert(NULL != heap);
    
    size = HeapSize(heap);
    
    for (i = 0; i < size; ++i)
    {
        if (0 == heap->cmp_func(GET_DATA(heap, i), data))
        {
			Swap(GET_DATA(heap, i), GET_DATA(heap, LAST_ELEMENT_IDX(heap)));
			removed_data = GET_DATA(heap, LAST_ELEMENT_IDX(heap));
            VectorPopBack(heap->vec);
            HeapifyDown(heap, i);
			break;
        }
    }
    
    return removed_data;
}

void *HeapPeek(const heap_t *heap)
{
	size_t peek_idx = 0;

	assert(NULL != heap);

    return VectorGetAccessToElement(heap->vec, peek_idx);
}

size_t HeapSize(const heap_t *heap)
{
	assert(NULL != heap);

    return VectorSize(heap->vec);
}

int HeapIsEmpty(const heap_t *heap)
{
	assert(NULL != heap);

    return VectorIsEmpty(heap->vec);
}


/********************************** Static Functions **********************************/

static void HeapifyUp(const heap_t *heap)
{
	size_t element_index = 0;
	size_t parent_index = 0;

	assert(NULL != heap);
	
	element_index = LAST_ELEMENT_IDX(heap);
	parent_index = GET_PARENT_IDX(element_index);
    
    while (0 < element_index && (0 < heap->cmp_func(GET_DATA(heap, element_index), GET_DATA(heap, parent_index))))
    {
        Swap(GET_DATA(heap, parent_index), GET_DATA(heap, element_index));

        element_index = GET_PARENT_IDX(element_index);
	    parent_index = GET_PARENT_IDX(element_index);
    }
}

static void HeapifyDown(const heap_t *heap, size_t index)
{
    size_t go_down_index = index;
    size_t index_to_swap = go_down_index;
    size_t right_child_index = 0;
    size_t left_child_index = 0;
    size_t size = 0;
    
    assert(NULL != heap);
    
    size = VectorSize(heap->vec);
    
    while (go_down_index < size)
    {
        right_child_index = GET_RIGHT_CHILD_IDX(go_down_index);
        left_child_index = GET_LEFT_CHILD_IDX(go_down_index);
        
        if (left_child_index < size && 0 < heap->cmp_func(GET_DATA(heap, left_child_index), GET_DATA(heap, index_to_swap)))
        {
            index_to_swap = left_child_index;
        }
        
        if (right_child_index < size && 0 < heap->cmp_func(GET_DATA(heap, right_child_index), GET_DATA(heap, index_to_swap)))
        {
            index_to_swap = right_child_index;
        }
        
        if (index_to_swap != go_down_index)
        {
            Swap(GET_DATA(heap, index_to_swap), GET_DATA(heap, go_down_index));
            go_down_index = index_to_swap;
        }
        
        else
        {
            break;
        }
    }
}

static void Swap(void **ptr1, void **ptr2)
{
    void *temp = NULL;

    assert(NULL != ptr1);
    assert(NULL != ptr2);

    temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

