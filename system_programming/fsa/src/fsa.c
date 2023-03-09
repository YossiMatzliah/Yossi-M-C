/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Or Beruven 	  		*
*	Date      : 08/03/2023			*
************************************/

#include <stddef.h>	/* size_t */		
#include <assert.h>	/* assert */

#include "fsa.h"	

/*************** MACROS ******************/

#define WORD_SIZE (sizeof(void *))
#define END_FLAG (0)
#define STRUCT_SIZE (sizeof(fsa_t))
#define LAST_BLOCK (1)

/*************** managerial struct ******************/

struct fsa
{
	size_t free_location;
};

/*************** static functions ******************/

static size_t AlignBlock(size_t block_size);
static size_t GetAlingnmentOffset(void *memory_segment);

/****************************************************************************/

fsa_t *FSAInit(void *memory_segment, size_t segment_size, size_t block_size)
{
	char *offset_placer = NULL;
	fsa_t *new_fsa = NULL;	
	size_t offset_counter = 0;
	size_t alignment_offset = 0;
	size_t block_number = 0;
	
	assert(NULL != memory_segment);
	assert(WORD_SIZE < segment_size);
	assert(block_size < segment_size);
	
	if(0 != ((size_t)memory_segment % WORD_SIZE))
	{
		alignment_offset = GetAlingnmentOffset(memory_segment);
	}
		
	block_size = AlignBlock(block_size);
	
	if((block_size + STRUCT_SIZE) > segment_size)
	{
		return NULL;
	}
	
	segment_size -= alignment_offset;
	
	offset_placer = (char *)memory_segment + alignment_offset;
	new_fsa = (fsa_t *)offset_placer;
	offset_placer += STRUCT_SIZE;
	offset_counter += STRUCT_SIZE;
	segment_size = segment_size - STRUCT_SIZE;

	new_fsa->free_location = offset_counter;
	offset_counter += block_size;
	block_number = segment_size / block_size; 
	
	for (;block_number > LAST_BLOCK ; offset_counter += block_size , --block_number)
	{
		*(size_t *)offset_placer = offset_counter;
		offset_placer += block_size;
	} 
	
	*(size_t *)offset_placer = END_FLAG;
	
	return new_fsa;	
}

void *FSAAlloc(fsa_t *fsa)
{
	size_t new_offset = 0;
	char *return_block = NULL;
	
	assert(NULL != fsa);
	
	if (END_FLAG != fsa->free_location)
	{
		return_block = (char *)fsa;
		return_block += fsa->free_location;
		
		new_offset = *(size_t *)return_block;
		fsa->free_location = new_offset;
	}
	
	return (void *)return_block;
}

void FSAFree(fsa_t *fsa, void *block_pointer)
{
	assert(NULL != fsa);
	assert(NULL != block_pointer);
	
	*(size_t *)block_pointer = fsa->free_location;
	fsa->free_location = (size_t)((char *)block_pointer - (char *)fsa);;
}

size_t FSACountFree(const fsa_t *fsa)
{
	size_t count = 0;
	size_t runner = 0;
	
	assert(NULL != fsa);
	
	runner =  fsa->free_location;
	while (END_FLAG != runner)
	{
		++count;
		runner = *(size_t *)((char *)fsa + runner);
	}
	
	return count;
}

size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{	
	block_size = AlignBlock(block_size);
	
	return (num_of_blocks * block_size + STRUCT_SIZE); 

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

static size_t GetAlingnmentOffset(void *memory_segment)
{
	size_t alignment_offset = 0;
	
	assert(NULL != memory_segment);
	
	alignment_offset = WORD_SIZE - ((size_t)memory_segment % WORD_SIZE);
	
	return alignment_offset;
}


