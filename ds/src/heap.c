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

#define GET_DATA(heap, index) (VectorGetAccessToElement(heap->vec, index))
#define inserted_elem_IDX(heap) (VectorSize(heap->vec) - 1) 
#define GET_PARENT_IDX(index) ((size_t)(((index) - 1) / (2)))
#define GET_LEFT_CHILD_IDX(index) ((2 * (index)) + 1)
#define GET_RIGHT_CHILD_IDX(index) ((2 * (index)) + 2)

struct heap 
{
	vector_t *vec;
    int (*cmp_func)(const void *, const void *);
};

/******************************** Static Functions *********************************/

static void Swap(void **lhd, void **rhd);
static void HeapifyUp(const heap_t *heap);
static void HeapifyDown(const heap_t *heap);


/********************************** API Functions **********************************/

heap_t * HeapCreate(int(* cmp_func)(const void *, const void *))
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

int HeapPush(heap_t *heap, void *data)  /* Heapify Up */
{
    int status = SUCCESS;
    
    assert(NULL != heap);
    
    status = VectorPushBack(heap->vec, data);
    HeapifyUp(heap);
    
    return status;
}

void HeapPop(heap_t *heap)  /* First, swap of root and last element, then Heapify Down */
{
	size_t root_idx = 0;
    
    assert(NULL != heap);
    
    Swap(GET_DATA(heap, root_idx), GET_DATA(heap, inserted_elem_IDX(heap)));
    VectorPopBack(heap->vec);
    HeapifyDown(heap);
}

void *HeapRemove(heap_t *heap, int (*is_match_func)(const void *data, const void *param), const void *param)
{
    return NULL;
}

void *HeapRemoveByKey(heap_t *heap, void *data)
{
    return NULL;
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
	size_t last_index = 0;
	size_t parent_index = 0;
	void *inserted_elem = 0;
	void *parent_element = 0;

	assert(NULL != heap);
	
	last_index = inserted_elem_IDX(heap);
	parent_index = GET_PARENT_IDX(last_index);
    
    while (last_index > 0 && (0 < heap->cmp_func(GET_DATA(heap, last_index), GET_DATA(heap, parent_index))))
    {
		inserted_elem = GET_DATA(heap, last_index);
		parent_element = GET_DATA(heap, parent_index);

        Swap(&inserted_elem, &parent_element);

        last_index = GET_PARENT_IDX(last_index);
	    parent_index = GET_PARENT_IDX(last_index);
    }
    /*
    for (last_index = inserted_elem_IDX(heap); last_index >= 0; last_index = GET_PARENT_IDX(last_index))
    {
        parent_index = GET_PARENT_IDX(last_index);
        
        if (0 < heap->cmp_func(GET_DATA(heap, last_index), GET_DATA(heap, parent_index)))
        {
            Swap(GET_DATA(heap, last_index), GET_DATA(heap, parent_index));
        }
        
        else
        {
            break;
        }
    }
	*/
}

static void HeapifyDown(const heap_t *heap)
{
    assert(NULL != heap);
    
	return;
}

static void Swap(void **lhd, void **rhd) 
{
    void *temp = *lhd;
    *lhd = *rhd;
    *rhd = temp;
}



