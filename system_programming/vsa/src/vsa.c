/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Daniel Wurtzel 		*
*	Date      : 08/03/2023			*
************************************/

#include <assert.h>	/* assert */
#include <stdio.h>			/* delete after testing */

#include "vsa.h"	

/*************** MACROS ******************/

#define TRUE (1)
#define FALSE (0)

#define WORD_SIZE (sizeof(void *))
#define VSA_STRUCT_SIZE (sizeof(vsa_t))
#define B_INFO_STRUCT_SIZE (sizeof(b_info_t))

/*************** managerial struct ******************/

struct vsa
{
	size_t segment_size;
};

typedef struct block_start
{
	size_t block_size;
}b_info_t;

/***************** static functions ******************/

static size_t AlignBlock(size_t block_size);
static void DeFrag(vsa_t *pool);
/*static size_t GetAlingnmentOffset(void *memory_segment);*/

/****************************************************************************/

vsa_t *VSAInit(void *memory_pool, size_t segment_size)
{
	vsa_t *new_vsa = NULL;
	b_info_t *b_info = NULL; 
	size_t align_offset = 0;
    
    assert(NULL != memory_pool);
	assert(0 != segment_size);
	
    if (0 != ((size_t)memory_pool % WORD_SIZE))
    {
    	align_offset = WORD_SIZE - ((size_t)memory_pool % WORD_SIZE);
    	segment_size -= (align_offset + ((size_t)memory_pool % WORD_SIZE));
    }

    memory_pool = (char *)memory_pool + align_offset;
	new_vsa = (vsa_t *)memory_pool;
	/*segment_size -= VSA_STRUCT_SIZE;*/
	
	new_vsa->segment_size = segment_size;
	b_info = (b_info_t *)((char *)memory_pool + VSA_STRUCT_SIZE);
	b_info->block_size = new_vsa->segment_size - VSA_STRUCT_SIZE - B_INFO_STRUCT_SIZE;
	
	return new_vsa;
}

void *VSAAlloc(vsa_t *pool, size_t block_size)
{
	b_info_t *runner = NULL;
	size_t max_chunk_size = 0;
	
	assert(NULL != pool);
	assert(0 != block_size);
	
	DeFrag(pool);
	max_chunk_size = VSALargestChunkAvailable(pool);
	
	block_size = AlignBlock(block_size);
	
	if (max_chunk_size < block_size + WORD_SIZE) 
	{
		return runner;
	}
	
	while (pool->segment_size != (size_t)((char *)runner - (char *)pool) || (runner->block_size >= block_size && TRUE != (runner->block_size & 1)))
	{
		runner += (B_INFO_STRUCT_SIZE + runner->block_size);
	}
	
	runner->block_size = runner->block_size ^ 1;
	
	return (void *)(runner + B_INFO_STRUCT_SIZE);
}

static void DeFrag(vsa_t *pool)
{
	b_info_t *runner = NULL;
	b_info_t *next = NULL;
	
	assert(NULL != pool);
	
	runner = (b_info_t *)((char *)pool + VSA_STRUCT_SIZE);
	
	while (pool->segment_size != (size_t)((char *)runner - (char *)pool))
	{
		if (TRUE != (runner->block_size & 1))
		{
			next = (b_info_t *)((char *)runner + runner->block_size + B_INFO_STRUCT_SIZE);
			while (TRUE != (next->block_size & 1) && pool->segment_size != (size_t)((char *)next - (char *)pool))
			{
			    next += B_INFO_STRUCT_SIZE + runner->block_size;
			}
		}
		
		runner->block_size = (size_t)((char *)next - (char *)runner) - B_INFO_STRUCT_SIZE;
		runner += B_INFO_STRUCT_SIZE + runner->block_size;
	}
}

void VSAFree(void *block_pointer)
{
	b_info_t *b_ptr = NULL;
	
	if (NULL != block_pointer)
	{
        b_ptr = (b_info_t *)((char *)block_pointer - B_INFO_STRUCT_SIZE);

		b_ptr->block_size = b_ptr->block_size ^ 1;
	}
}

size_t VSALargestChunkAvailable(vsa_t *pool)
{
	size_t max_chunk = 0;
	b_info_t *runner = NULL;
	b_info_t *next = NULL;
	
	runner = (b_info_t *)((char *)pool + VSA_STRUCT_SIZE);
	printf("pool ptr: %p\n", pool);
		printf("pool + pool->segment_size: %p\n", (char *)pool + pool->segment_size);
		printf("next ptr: %p\n", next);
		printf("runner ptr: %p\n", runner);
		printf("runner + B_INFO_STRUCT_SIZE ptr: %p\n", ((char *)runner + 8));
		printf("max_chunk: %ld\n", max_chunk);
		 printf("before while: pool + pool->segment_size = %ld\n", (size_t)(char *)pool + pool->segment_size);
    printf("before while: runner + B_INFO_STRUCT_SIZE + runner->block_size = %ld\n", (size_t)(char *)runner + B_INFO_STRUCT_SIZE + runner->block_size);
	while (((char *)pool + pool->segment_size) != (char *)runner + B_INFO_STRUCT_SIZE)
	{
		if (TRUE != (runner->block_size & 1))
		{
			
			next = (b_info_t *)((char *)runner + runner->block_size + VSA_STRUCT_SIZE);
			
			
			while (TRUE != (next->block_size & 1) && ((char *)pool + pool->segment_size) != (char *)next)
			{
				
				next += B_INFO_STRUCT_SIZE + runner->block_size;
				break;
			}
			
			if (max_chunk < (size_t)((char *)next - (char *)runner) - B_INFO_STRUCT_SIZE)
			{
				max_chunk = (size_t)((char *)next - (char *)runner) - B_INFO_STRUCT_SIZE;
			}
		}
		
		runner += B_INFO_STRUCT_SIZE + runner->block_size;
	}
	
	return max_chunk;
}

/************* static functions ********************/
/*
static size_t GetAlingnmentOffset(void *memory_segment)
{
	size_t alignment_offset = 0;
	
	assert(NULL != memory_segment);
	
	alignment_offset = WORD_SIZE - ((size_t)memory_segment % WORD_SIZE);
	
	return alignment_offset;
}*/

static size_t AlignBlock(size_t block_size)
{
	size_t block_check = 0;
	block_check  = block_size % WORD_SIZE;
	
	if (block_check != 0)
	{
		block_size = block_size + (WORD_SIZE - block_check);	
	}
	
	return  block_size; 
}















/*

size_t VSALargestChunkAvailable(vsa_t *pool)
{
	size_t largest_chunk = 0;
	header_t *runner = NULL;
	header_t *next = NULL;
	
	assert(NULL != pool);
	
	runner = (header_t *)((char *)pool + VSA_STRUCT_SIZE);
		
	while (NULL != runner)
	{
		next = NEXTEMPTY(pool , runner);
		
		while (NULL != next && (size_t)((char *)runner + runner->block_size) == (size_t)next && 0 == IS_FULL(runner->block_size))
		{
			runner->block_size += next->block_size;
			next = NEXTEMPTY(pool , runner);			
		}
		
		if (largest_chunk < (runner->block_size & ((~0) << 1)) && 0 == IS_FULL(runner->block_size))
		{
			largest_chunk = runner->block_size;
		}
		
		runner = next;
	}
	
	return ((0 == largest_chunk)? 0: (largest_chunk - sizeof(header_t)) ;
}

static header_t *NextEmpty(vsa_t *pool, header_t *current)
{
	size_t current_set_off = (size_t)current - (size_t)pool;
	
	current_set_off += (current->block_size & ((~0) << 1));
	current += (current->block_size & ((~0) << 1));
	
	while (1 == IS_FULL(current->block_size) && current_set_off < pool->segment_size)
	{
		current_set_off += (current->block_size & ((~0) << 1));
		current += (current->block_size & ((~0) << 1));				
	}
	
	if (0 == IS_FULL(current->block_size))
	{
		return current;
	}
	else
	{
		return NULL;
	}
}


void *VSAAlloc(vsa_t *pool, size_t block_size)
{
	char *runner = NULL;
	size_t round_block_size = 0;
	
	assert(NULL != pool);	
	assert(0 != block_size);	
	
	round_block_size = ((0 == (block_size % WORD_SIZE))? block_size : (block_size + (WORD_SIZE - (block_size % WORD_SIZE))));
	
	if (VSALargestChunkAvailable(pool) < round_block_size)
	{
		return NULL;
	}
	
	runner = (char *)pool + VSA_STRUCT_SIZE;
	
	while (round_block_size > ((header_t *)runner)->block_size & ((~0) << 1)) && 0 == IS_FULL(runner->block_size))
	{
		runner = NEXT_EMPTY(pool , runner);
	}
	
	ChangeHeader(runner ,round_block_size);
	runner->block_size |= (1 >> 63);
	
	return (runner + sizeof(header_t));
}*/
