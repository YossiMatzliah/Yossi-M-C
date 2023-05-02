/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Yotam S				*
*	Date      : 01/05/2023			*
************************************/

#include <stdio.h>	/* printf */
#include <math.h>   /* pow */

#include "trie.h"

#define U_LINE 	"\033[1m\033[4m"
#define RED   	"\033[1m\033[41m\x1B[30m"
#define GRN   	"\033[1m\033[42m\x1B[30m"
#define RESET 	"\033[0m"

#define TRUE 	(1)
#define FALSE 	(0)

#define PRINT_TEST(x) ((TRUE == (x)) ? printf(GRN"SUCCESS!"RESET"\n\n") : printf(RED"FAILURE!, line %d"RESET"\n\n", __LINE__))

#define NEW_LINE printf("\n")

typedef enum trie_status
{
    SUCCESS = 0,
    FAILURE = 1,
    FULL_TREE = 2,
    DOUBLE_FREE = 3,
    DS_FAILURE = 4,
    SEARCH_BIGGER = 5,
    FIND_SMALLER = 6
} trie_status_t;

/*****************************************************************/

static void TestTrieCreateDestroy();
static void TestTrieInsert();
static void TestTrieFree();

/*****************************************************************/

int main()
{
	TestTrieCreateDestroy();
	TestTrieInsert();
	TestTrieFree();
	
	return 0;
}

/**************************************************************/

static void TestTrieCreateDestroy()
{
	trie_t *test_trie = NULL;

	printf(U_LINE"\nTest Trie Create:\n\n"RESET);

	test_trie = TrieCreate(1);

	PRINT_TEST(NULL != test_trie);

	TrieDestroy(test_trie);
}

void TestTrieInsert()
{
	trie_t *test_trie = NULL;
	size_t height = 3;
	unsigned int ip_1 = 2;
	unsigned int ip_2 = 3;
	unsigned int ip_3 = 7;
	unsigned int result = ip_1;
	int status = 0;

	printf(U_LINE"\nTest Trie Insert:\n\n"RESET);

	test_trie = TrieCreate(height);
	
	PRINT_TEST(TRUE == TrieIsEmpty(test_trie));

    status = TrieInsert(test_trie, ip_1, &result);
	PRINT_TEST(SUCCESS == status);
	PRINT_TEST(pow(2, height) - 1 == TrieCountFree(test_trie));

    status = TrieInsert(test_trie, ip_2, &result);
	PRINT_TEST(pow(2, height) - 2 == TrieCountFree(test_trie));

	status = TrieInsert(test_trie, ip_3, &result);
	PRINT_TEST(pow(2, height) - 3 == TrieCountFree(test_trie));

	status = TrieInsert(test_trie, ip_2, &result);
	
	status = TrieInsert(test_trie, ip_2, &result);
	
	status = TrieInsert(test_trie, ip_2, &result);
	
	status = TrieInsert(test_trie, ip_2, &result);
	
	status = TrieInsert(test_trie, ip_2, &result);
	PRINT_TEST(SUCCESS == status);

	status = TrieInsert(test_trie, ip_2, &result);
	PRINT_TEST(FULL_TREE == status);
	PRINT_TEST(0 == TrieCountFree(test_trie));
	
	TrieDestroy(test_trie);
}

static void TestTrieFree()
{
	trie_t *test_trie = NULL;
	size_t height = 3;
	unsigned int ip_1 = 2;
	unsigned int ip_2 = 3;
	unsigned int ip_3 = 7;
	unsigned int ip_not_allocated = 4;

	unsigned int result = ip_1;
	int status = 0;

	printf(U_LINE"\nTest Trie Free:\n\n"RESET);

	test_trie = TrieCreate(height);

    TrieInsert(test_trie, ip_1, &result);
    TrieInsert(test_trie, ip_2, &result);
	TrieInsert(test_trie, ip_3, &result);

	status = TrieFree(test_trie, ip_1);
	PRINT_TEST(SUCCESS == status);
	PRINT_TEST(pow(2, height) - 2 == TrieCountFree(test_trie));
	
	status = TrieFree(test_trie, ip_1);
	PRINT_TEST(DOUBLE_FREE == status);

	status = TrieFree(test_trie, ip_not_allocated);
	PRINT_TEST(DOUBLE_FREE == status);

	status = TrieFree(test_trie, ip_2);
	PRINT_TEST(SUCCESS == status);

	status = TrieFree(test_trie, ip_3);
	PRINT_TEST(SUCCESS == status);
	PRINT_TEST(TRUE == TrieIsEmpty(test_trie));
	PRINT_TEST(pow(2, height) == TrieCountFree(test_trie));

	status = TrieInsert(test_trie, ip_1, &result);
	PRINT_TEST(SUCCESS == status);

	TrieDestroy(test_trie);
}