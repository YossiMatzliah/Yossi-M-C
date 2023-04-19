/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	????				*
*	Date      : ?/04/2023			*
************************************/

#include <stdio.h>	/* perror */
#include <assert.h>	/* assert */
#include <stdlib.h>	/* malloc */

#include "heap.h"
#include "dynamic_vector.h"

#define SUCCESS (0)
#define FAILURE (1)
#define TRUE 	(1)
#define FALSE 	(0)

#define START_CAPACITY (3)
#define ROOT_IDX (0)
#define GET_DATA(heap, index) (VectorGetAccessToElement(heap->vec, index))
#define LAST_ELEMENT_IDX(heap) (VectorSize(heap->vec) - 1) 
#define GET_PARENT_IDX(index) ((size_t)(((index) - 1) / (2)))
#define GET_LEFT_CHILD_IDX(index) ((2 * (index)) + 1)
#define GET_RIGHT_CHILD_IDX(index) ((2 * (index)) + 2)
#define HAS_LEFT_CHILD(index) (GET_LEFT_CHILD_IDX(index) < VectorSize(heap->vec))

struct heap 
{
	vector_t *vec;
    int (*cmp_func)(const void *, const void *);
};

/******************************** Static Functions *********************************/

static void HeapifyUp(const heap_t *heap, size_t index);
static void HeapifyDown(const heap_t *heap, size_t index);
static void *RemoveByIndex(heap_t *heap, size_t index);
static size_t GetBiggerElementIndex(const heap_t *heap, size_t index, size_t size);
static int GetCompareResult(const heap_t *heap, size_t index_1, size_t index_2);
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
	assert(NULL != heap);
	
	VectorDestroy(heap->vec);
	free(heap);
}

int HeapPush(heap_t *heap, void *data)  
{
    int status = SUCCESS;
    
    assert(NULL != heap);
    
    status = VectorPushBack(heap->vec, (void *)&data);
    HeapifyUp(heap, LAST_ELEMENT_IDX(heap));
    
    return status;
}

void HeapPop(heap_t *heap)  
{
    assert(NULL != heap);
    
    Swap(GET_DATA(heap, ROOT_IDX), GET_DATA(heap, LAST_ELEMENT_IDX(heap)));
    VectorPopBack(heap->vec);
    HeapifyDown(heap, ROOT_IDX);
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
        if (TRUE == is_match_func(*(void **)GET_DATA(heap, i), param))
        {
            removed_data = RemoveByIndex(heap, i);
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
        if (0 == heap->cmp_func(*(void **)GET_DATA(heap, i), data))
        {
            removed_data = RemoveByIndex(heap, i);
            break;
        }
    }
    
    return removed_data;
}

void *HeapPeek(const heap_t *heap)
{
	assert(NULL != heap);

    return *(void **)VectorGetAccessToElement(heap->vec, ROOT_IDX);
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

static void HeapifyUp(const heap_t *heap, size_t index)
{
	size_t element_index = index;
	size_t parent_index = 0;

	assert(NULL != heap);
	
	parent_index = GET_PARENT_IDX(element_index);
    
    while (0 < element_index && (0 < heap->cmp_func(*(void **)GET_DATA(heap, element_index), *(void **)GET_DATA(heap, parent_index))))
    {
        Swap(GET_DATA(heap, parent_index), GET_DATA(heap, element_index));

        element_index = GET_PARENT_IDX(element_index);
	    parent_index = GET_PARENT_IDX(element_index);
    }
}

static void HeapifyDown(const heap_t *heap, size_t index)
{
    size_t bigger_element_index = 0;
    size_t size = 0;
    
    assert(NULL != heap);
    
    size = VectorSize(heap->vec);
    
    while (HAS_LEFT_CHILD(index))
    {
        bigger_element_index = GetBiggerElementIndex(heap, index, size);
        
        if (bigger_element_index != index)
        {
            Swap(GET_DATA(heap, bigger_element_index), GET_DATA(heap, index));
            index = bigger_element_index;
        }
        
        else
        {
            break;
        }
    }
}

static size_t GetBiggerElementIndex(const heap_t *heap, size_t index, size_t size)
{
    size_t bigger_element_index = index;
    size_t right_child_index = 0;
    size_t left_child_index = 0;

    assert(NULL != heap);

    right_child_index = GET_RIGHT_CHILD_IDX(index);
    left_child_index = GET_LEFT_CHILD_IDX(index);

    if (0 < GetCompareResult(heap, left_child_index, bigger_element_index))
    {
        bigger_element_index = left_child_index;
    }
    
    if (right_child_index < size && 0 < GetCompareResult(heap, right_child_index, bigger_element_index))
    {
        bigger_element_index = right_child_index;
    }

    return bigger_element_index;
}

static int GetCompareResult(const heap_t *heap, size_t index_1, size_t index_2)
{
    return (heap->cmp_func(*(void **)GET_DATA(heap, index_1), *(void **)GET_DATA(heap, index_2)));
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

static void *RemoveByIndex(heap_t *heap, size_t index)
{
    void *return_data = NULL;
    
    assert(NULL != heap);

    Swap(GET_DATA(heap, index), GET_DATA(heap, LAST_ELEMENT_IDX(heap)));
    return_data = *(void **)GET_DATA(heap, LAST_ELEMENT_IDX(heap));
    VectorPopBack(heap->vec);
    HeapifyDown(heap, index);
    HeapifyUp(heap, index);
   
    return return_data;
}

