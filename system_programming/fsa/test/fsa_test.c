/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Or Beruven 	  		*
*	Date      : 08/03/2023			*
************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* system */

#include "fsa.h"

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
static void AllocTest();
static void CountTest();
static void FreeTest();
static void SuggestSizeTest();

/***********************************************/

int main()
{
	InitTest();

	AllocTest();

	CountTest();
	
	FreeTest();
	
	SuggestSizeTest();

	return 0; 
}

void InitTest()
{
	fsa_t *fsa = NULL;
	char *pool = (char *)malloc(160); 
	
	fsa = FSAInit(pool, 160, 16);
	printf(U_LINE"\nTesting FSAInit\n"RESET);
	
	PRINT_TEST(NULL != fsa);
	PRINT_TEST(pool == (char *)fsa);
	
	free(pool);
	
	printf("Testing if not aligned:\n");
	pool = (char *) malloc(160);
	fsa = FSAInit((pool + 1), 160, 16);
	PRINT_TEST(pool + WORD_SIZE == (char *)fsa);
	NEW_LINE;
	
	free(pool);
}

void AllocTest()
{
	fsa_t *fsa = NULL;
	char *alloc1 = NULL;
	char *alloc2 = NULL;
	int *alloc3 = NULL;
	
	char *pool = (char *)malloc(160); 
	
	printf(U_LINE"\nTesting FSAAlloc\n"RESET);
	fsa = FSAInit(pool, 160, 16);
	alloc1 = (char *)FSAAlloc(fsa);
	PRINT_TEST(pool + WORD_SIZE == alloc1);
	alloc2 = (char *)FSAAlloc(fsa);
	PRINT_TEST(pool + WORD_SIZE + (2 * WORD_SIZE) == alloc2);
	PRINT_TEST((2 * WORD_SIZE) == alloc2 - alloc1);
	
	alloc3 = (int *)FSAAlloc(fsa);
	PRINT_TEST((2 * WORD_SIZE) == (char *)alloc3 - alloc2);
	
	free(pool);
}

void CountTest()
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

void FreeTest()
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

void SuggestSizeTest()
{
	printf(U_LINE"\nTesting FSASuggestSize\n"RESET);
	PRINT_TEST(168 == FSASuggestSize(10,16));
	PRINT_TEST(4 * 8 + WORD_SIZE == FSASuggestSize(4,6));
	PRINT_TEST(168 == FSASuggestSize(10,10));
}

