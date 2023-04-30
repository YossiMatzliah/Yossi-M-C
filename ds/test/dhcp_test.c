/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :					*
*	Date      : /04/2023			*
************************************/

#include <stdio.h>	

#include "dhcp.h"

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

static void TestDHCPCreateDestroy();
static void TestDHCPAllocateIp();
static void TestDHCPFreeIp();


/*****************************************************************/

int main()
{
	TestDHCPCreateDestroy();
	TestDHCPAllocateIp();
	TestDHCPFreeIp();
	
	return 0;
}

/**************************************************************/

static void TestDHCPCreateDestroy()
{
	dhcp_t *test_dhcp = NULL;

	printf(U_LINE"\nTest Trie Create:\n\n"RESET);

	test_dhcp = TrieCreate(1);

	PRINT_TEST(NULL != test_dhcp);

	TrieDestroy(test_dhcp);
}

static void TestDHCPAllocateIp()
{
	dhcp_t *test_dhcp = NULL;
	unsigned char *data[] = {"0010", "0011", "1000"};
	
	size_t i = 0;
	size_t n = sizeof(data) / sizeof(data[0]);

	printf(U_LINE"\nTest Trie Insert:\n\n"RESET);

	test_dhcp = TrieCreate(4);

	for(i = 0; i < n; ++i) 
	{
        TrieInsert(test_dhcp, data[i]);
		PRINT_TEST((i + 1) == DHCPCountFree(test_dhcp));
    }
	
	PRINT_TEST(NULL != test_dhcp);

	TrieDestroy(test_dhcp);
}

static void TestDHCPFreeIp()
{
	dhcp_t *test_dhcp = NULL;
	unsigned char *data[] = {"0010", "0011", "1000"};
	
	size_t i = 0;
	size_t n = sizeof(data) / sizeof(data[0]);

	printf(U_LINE"\nTest Trie Insert:\n\n"RESET);

	test_dhcp = TrieCreate(4);

	for(i = 0; i < n; ++i) 
	{
        TrieInsert(test_dhcp, data[i]);
    }

	DHCPFreeIp(test_dhcp, data[0]);

	TrieDestroy(test_dhcp);
}