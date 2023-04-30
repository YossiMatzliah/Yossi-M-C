/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :					*
*	Date      : /04/2023			*
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
#define SUCCESS (0)
#define FAILURE (1)

#define PRINT_TEST(x) ((TRUE == (x)) ? printf(GRN"SUCCESS!"RESET"\n\n") : printf(RED"FAILURE!, line %d"RESET"\n\n", __LINE__))

#define NEW_LINE printf("\n")

/*****************************************************************/

static void TestTrieCreateDestroy();
static void TestTrieInsert();

/*****************************************************************/

int main()
{
	TestTrieCreateDestroy();
	TestTrieInsert();
	
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
	size_t height = 4;
	unsigned int result[4] = {0};
	unsigned int ip_1 = 2;
	unsigned int ip_2 = 3;
	unsigned int ip_3 = 8;

	printf(U_LINE"\nTest Trie Insert:\n\n"RESET);

	test_trie = TrieCreate(height);
	
    TrieInsert(test_trie, ip_1, result);
	PRINT_TEST(pow(2, height) - 1 == TrieCountFree(test_trie));
    TrieInsert(test_trie, ip_2, result);
	PRINT_TEST(pow(2, height) - 2 == TrieCountFree(test_trie));
	TrieInsert(test_trie, ip_3, result);
	PRINT_TEST(pow(2, height) - 3 == TrieCountFree(test_trie));
	
	
	TrieDestroy(test_trie);
}
