/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Daniel Wurtzel 		*
*	Date      : 11/03/2023			*
************************************/

#include <assert.h>	/* assert */

#include "vsa.h"	

/*************** MACROS ******************/

#define ALLOCED (1)
#define FREE 	(0)
#define WORD_SIZE 			(sizeof(void *))
#define VSA_STRUCT_SIZE 	(sizeof(vsa_t))
#define B_INFO_STRUCT_SIZE 	(sizeof(b_info_t))
#define REAL_BLOCK_SIZE(x) 	(x - (x & 1))
#define ALIGN_WORD_SIZE(x) 	(x - (x % WORD_SIZE))

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
	
	new_vsa->segment_size = ALIGN_WORD_SIZE(segment_size);
	b_info = (b_info_t *)((char *)memory_pool + VSA_STRUCT_SIZE);
	b_info->block_size = new_vsa->segment_size - VSA_STRUCT_SIZE - B_INFO_STRUCT_SIZE;
	
	return new_vsa;
}

void *VSAAlloc(vsa_t *pool, size_t block_size)
{
	b_info_t *runner = NULL;
	b_info_t *new_info_block = NULL;
	size_t max_chunk_size = 0;
	
	assert(NULL != pool);
	assert(0 != block_size);
	
	max_chunk_size = VSALargestChunkAvailable(pool);
	
	block_size = AlignBlock(block_size);
	
	if (max_chunk_size < block_size) 
	{
		return runner;
	}
	
	runner = (b_info_t *)((char *)pool + VSA_STRUCT_SIZE);
	
	while (((char *)pool + pool->segment_size) != (char *)runner)
	{
		if ((REAL_BLOCK_SIZE(runner->block_size) >= block_size) && (FREE == (runner->block_size & 1)))
		{
			if((char *)pool + pool->segment_size > (char *)runner + B_INFO_STRUCT_SIZE + block_size)
			{
				new_info_block = (b_info_t *)((char *)runner + B_INFO_STRUCT_SIZE + block_size);
				new_info_block->block_size = REAL_BLOCK_SIZE(runner->block_size) - B_INFO_STRUCT_SIZE - block_size;
			}
			runner->block_size = block_size;
			runner->block_size = runner->block_size ^ 1;
			break;
		}
		
		runner = (b_info_t *)((char *)runner + (B_INFO_STRUCT_SIZE + REAL_BLOCK_SIZE(runner->block_size)));
	}
	
	return (void *)((char *)runner + B_INFO_STRUCT_SIZE);
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
    
    DeFrag(pool);
    
    runner = (b_info_t *)((char *)pool + VSA_STRUCT_SIZE);
    
    while (((char *)pool + pool->segment_size) != (char *)runner)
    {
        if (FREE == (runner->block_size & 1))
        {
            next = (b_info_t *)((char *)runner + REAL_BLOCK_SIZE(runner->block_size) + B_INFO_STRUCT_SIZE);
            
            while (((char *)pool + pool->segment_size) != (char *)next && FREE == (next->block_size & 1))
            {
                next = (b_info_t *)((char *)next + B_INFO_STRUCT_SIZE + REAL_BLOCK_SIZE(runner->block_size));
            }
            
            if (max_chunk < (size_t)((char *)next - (char *)runner) - B_INFO_STRUCT_SIZE)
            {
                max_chunk = (size_t)((char *)next - (char *)runner) - B_INFO_STRUCT_SIZE;
            }
        }
        runner = (b_info_t *)((char *)runner + B_INFO_STRUCT_SIZE + REAL_BLOCK_SIZE(runner->block_size));
    }
    
    return max_chunk;
}

/************* static functions ********************/

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

static void DeFrag(vsa_t *pool)
{
	b_info_t *runner = NULL;
    b_info_t *next = NULL;
    
    assert(NULL != pool);
    
    runner = (b_info_t *)((char *)pool + VSA_STRUCT_SIZE);
    
    while (((char *)pool + pool->segment_size) != (char *)runner)
    {
        if (FREE == (runner->block_size & 1))
        {
            next = (b_info_t *)((char *)runner + runner->block_size + VSA_STRUCT_SIZE);
            
            while (((char *)pool + pool->segment_size) != (char *)next && FREE == (next->block_size & 1))
            {
            	runner->block_size += next->block_size + B_INFO_STRUCT_SIZE;
                next = (b_info_t *)((char *)next + B_INFO_STRUCT_SIZE + next->block_size);
            }
            
            runner = next;
        }
        
        else
        {
        	runner = (b_info_t *)((char *)runner + B_INFO_STRUCT_SIZE + REAL_BLOCK_SIZE(runner->block_size));
 		}       
    }
}

