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
#include "d_vector.h"

#define START_CAPACITY (3)
#define SUCCESS (0)
#define FAILURE (1)

struct heap 
{
	vector_t *vec;
    int (*cmp_func)(const void *, const void *);
};

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
    assert(NULL != heap);
    
    Swap();
    VectorPopBack(vector_t *vector);
    HeapifyDown(heap);
}

void *HeapRemove(heap_t *heap, void *data)
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

int ParentIndex(int i) {
    return ((i - 1) / 2);
}

int LeftChildIndex(int i) {
    return ((2 * i) + 1);
}

int RightChildIndex(int i) {
    return ((2 * i) + 2);
}

