/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Daniel Wurtzel 		*
*	Date      : 08/03/2023			*
************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* system */

#include "vsa.h"

#define WORD_SIZE (sizeof(void *))

#define U_LINE 	"\033[1m\033[4m"
#define RED   	"\033[1m\033[41m\x1B[30m"
#define GRN   	"\033[1m\033[42m\x1B[30m"
#define RESET 	"\033[0m"

#define TRUE  	(1)
#define FALSE 	(0)
#define FAILURE (1)
#define SUCCESS (0)

#define PRINT_TEST(x) ((TRUE == (x)) ? printf(GRN"SUCCESS!"RESET"\n\n") : printf(RED"FAILURE!, line %d"RESET"\n\n", __LINE__))

#define NEW_LINE printf("\n")

static void InitTest();
static void LargestChunkAvailableTest();/*
static void AllocTest();
static void CountTest();
static void FreeTest();*/

/***********************************************/

int main()
{
	InitTest();

	LargestChunkAvailableTest();
/*
	AllocTest();*/
/*
	CountTest();
	
	FreeTest();
	
	
*/
	return 0; 
}

static void InitTest()
{
	vsa_t *vsa = NULL;
	char *pool = (char *)malloc(160); 
	
	vsa = VSAInit(pool, 160);
	printf(U_LINE"\nTesting VSAInit\n"RESET);
	
	PRINT_TEST(NULL != vsa);
	PRINT_TEST(pool == (char *)vsa);
	
	free(pool);
	
	printf("Testing if not aligned:\n");
	pool = (char *)malloc(160);
	vsa = VSAInit((pool + 1), 160);
	PRINT_TEST(pool + WORD_SIZE == (char *)vsa);
	
	NEW_LINE;
	
	free(pool);
}

static void LargestChunkAvailableTest()
{
	vsa_t *vsa = NULL;
	size_t segment_size = 64;
	size_t largest_chunk = 0;
	void *memory_pool_ptr = NULL;
	
	memory_pool_ptr = malloc(segment_size);
	
	printf(U_LINE"Test vsa Largest Chunk Available:\n"RESET);
	
	vsa = VSAInit(memory_pool_ptr, segment_size);
	
	largest_chunk = VSALargestChunkAvailable(vsa);
	PRINT_TEST(largest_chunk == segment_size - WORD_SIZE);
	
	free(memory_pool_ptr);
}
/*
static void AllocTest()
{
	vsa_t *vsa = NULL;
	char *alloc1 = NULL;
	char *alloc2 = NULL;
	int *alloc3 = NULL;
	
	char *pool = (char *)malloc(160); 
	
	printf(U_LINE"\nTesting VSAAlloc\n"RESET);
	vsa = VSAInit(pool, 160, 16);
	alloc1 = (char *)VSAAlloc(fsa);
	PRINT_TEST(pool + WORD_SIZE == alloc1);
	alloc2 = (char *)VSAAlloc(fsa);
	PRINT_TEST(pool + WORD_SIZE + (2 * WORD_SIZE) == alloc2);
	PRINT_TEST((2 * WORD_SIZE) == alloc2 - alloc1);
	
	alloc3 = (int *)VSAAlloc(fsa);
	PRINT_TEST((2 * WORD_SIZE) == (char *)alloc3 - alloc2);
	
	free(pool);
}*/
/*
static void CountTest()
{
	fsa_t *fsa = NULL;
	size_t count = 0;
	char *pool = (char *)malloc(160); 
	char *alloc = NULL;
	
	printf(U_LINE"\nTesting FSACountFree\n"RESET);
	fsa = FSAInit(pool, 160, 16);
	
	count = FSACountFree(fsa);
	printf("count is: %ld\n", count);
	printf("Count Test before alloc\n");
	PRINT_TEST(9 == count);
	
	FSAAlloc(fsa);
	count = FSACountFree(fsa);
	printf("count is: %ld\n", count);
	printf("Count Test after Alloc\n");
	PRINT_TEST(8 == count);
	FSAAlloc(fsa);
	alloc = (char *)FSAAlloc(fsa);
	FSAAlloc(fsa);
	FSAAlloc(fsa);
	FSAAlloc(fsa);
	FSAAlloc(fsa);
	FSAAlloc(fsa);
	
	count = FSACountFree(fsa);
	printf("count is: %ld\n", count);
	FSAAlloc(fsa);
	count = FSACountFree(fsa);
	printf("count is: %ld\n", count);
	FSAFree(fsa, alloc);
	count = FSACountFree(fsa);
	printf("count is: %ld\n", count);
	
	free(pool);
}

static void FreeTest()
{
	fsa_t *fsa = NULL;
	size_t count = 0;
	char *pool = (char *)malloc(40); 
	char *alloc1 = NULL;
	char *alloc2 = NULL;
	printf(U_LINE"\nTesting FSAFree\n"RESET);
	fsa = FSAInit(pool, 40, 16);
	
	count = FSACountFree(fsa);
	printf("count is: %ld\n", count);
	printf("Count Test before alloc\n");
	PRINT_TEST(2 == count);
	
	alloc1 = (char *)FSAAlloc(fsa);
	count = FSACountFree(fsa);
	printf("count is: %ld\n", count);
	printf("Count Test after Alloc\n");
	PRINT_TEST(1 == count);
	alloc2 = (char *)FSAAlloc(fsa);
	
	count = FSACountFree(fsa);
	printf("count is: %ld\n", count);
	PRINT_TEST(0 == count);
	PRINT_TEST(40 - WORD_SIZE == alloc2 - pool + WORD_SIZE);
	printf("alloc2 ptr is: %p, pool ptr is: %p\n", alloc2, pool);
	FSAFree(fsa, alloc2);
	count = FSACountFree(fsa);
	printf("count is: %ld\n", count);
	FSAFree(fsa, alloc1);
	count = FSACountFree(fsa);
	printf("count is: %ld\n", count);
	PRINT_TEST(2 == count);
	
	free(pool);
}
*/


