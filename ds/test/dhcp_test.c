/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Yotam S				*
*	Date      : 01/05/2023			*
************************************/

#include <stdio.h>	/* printf */
#include <math.h>   /* pow */
#include <string.h> /* strncmp */

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
static void TestDHCPAllocateIp9Bits();
static void TestDHCPFreeIp();


/*****************************************************************/

int main()
{
	TestDHCPCreateDestroy();
	TestDHCPAllocateIp();
	TestDHCPAllocateIp9Bits();
	TestDHCPFreeIp();
	
	return 0;
}

/**************************************************************/

static void TestDHCPCreateDestroy()
{
	dhcp_t *test_dhcp = NULL;
	size_t free_bits = 8;
	unsigned char test_ip[BYTES_IN_IP] = {10, 10, 0, 5};

	printf(U_LINE"\nTest DHCP Create:\n\n"RESET);

	test_dhcp = DHCPCreate(test_ip, free_bits);

	PRINT_TEST(NULL != test_dhcp);
	PRINT_TEST(pow(2, free_bits) - 3 == DHCPCountFree(test_dhcp));
	
	DHCPDestroy(test_dhcp);
}

static void TestDHCPAllocateIp()
{
	dhcp_t *test_dhcp = NULL;
	unsigned char test_ip[BYTES_IN_IP] = {10, 10, 0, 5};
	size_t free_bits = 8;
	unsigned char result[BYTES_IN_IP] = {0};
	unsigned char requested_ip_1[BYTES_IN_IP] = {10, 10, 0, 8};
	unsigned char requested_ip_2[BYTES_IN_IP] = {10, 10, 0, 9};
	unsigned char requested_ip_3[BYTES_IN_IP] = {10, 10, 0, 253};
	unsigned char requested_ip_4[BYTES_IN_IP] = {10, 20, 0, 253};
	unsigned char invalid_requested_ip[BYTES_IN_IP] = {10, 10, 0, 254};
	
	printf(U_LINE"\nTest DHCP Allocate Ip:\n\n"RESET);

	test_dhcp = DHCPCreate(test_ip, free_bits);

    DHCPAllocateIp(test_dhcp, requested_ip_1, result);
	PRINT_TEST(pow(2, free_bits) - 4 == DHCPCountFree(test_dhcp));
	PrintCharPtr(result);

	DHCPAllocateIp(test_dhcp, requested_ip_2, result);
	PRINT_TEST(pow(2, free_bits) - 5 == DHCPCountFree(test_dhcp));
	PrintCharPtr(result);
	
	DHCPAllocateIp(test_dhcp, requested_ip_2, result);
	PRINT_TEST(pow(2, free_bits) - 6 == DHCPCountFree(test_dhcp));
	PrintCharPtr(result);

	DHCPAllocateIp(test_dhcp, requested_ip_3, result);
	PRINT_TEST(pow(2, free_bits) - 7 == DHCPCountFree(test_dhcp));
	PrintCharPtr(result);

	DHCPAllocateIp(test_dhcp, invalid_requested_ip, result);
	PRINT_TEST(pow(2, free_bits) - 8 == DHCPCountFree(test_dhcp));
	PrintCharPtr(result);

	DHCPAllocateIp(test_dhcp, requested_ip_4, result);
	PRINT_TEST(pow(2, free_bits) - 9 == DHCPCountFree(test_dhcp));
	PrintCharPtr(result);

	PRINT_TEST(SUCCESS == DHCPAllocateIp(test_dhcp, requested_ip_4, result));
	PRINT_TEST(pow(2, free_bits) - 10 == DHCPCountFree(test_dhcp));
	PrintCharPtr(result);

	DHCPDestroy(test_dhcp);
}

static void TestDHCPAllocateIp9Bits()
{
	size_t free_bits = 9;
    dhcp_t *dhcp = NULL;
    dhcp_status_t status = SUCCESS;
    unsigned char subnet_ip[BYTES_IN_IP] = {192, 168, 111, 0};
    unsigned char result_ip[BYTES_IN_IP] = {0, 0, 0, 0};
    unsigned char new_ip_1[BYTES_IN_IP] = {0, 0, 0, 0};
    unsigned char new_ip_2[BYTES_IN_IP] = {0, 0, 0, 0};
    unsigned char new_ip_3[BYTES_IN_IP] = {0, 0, 0, 0};
    unsigned char new_ip_4[BYTES_IN_IP] = {0, 0, 0, 0};
    unsigned char new_ip_5[BYTES_IN_IP] = {0, 0, 0, 0};
    unsigned char new_ip_6[BYTES_IN_IP] = {0, 0, 0, 0};
    unsigned char new_ip_7[BYTES_IN_IP] = {0, 0, 0, 0};
    unsigned char new_ip_8[BYTES_IN_IP] = {0, 0, 0, 0};
    unsigned char requested_ip_1[BYTES_IN_IP] = {192, 168, 111, 254};
    unsigned char requested_ip_2[BYTES_IN_IP] = {192, 168, 110, 1};
    unsigned char requested_ip_3[BYTES_IN_IP] = {192, 168, 110, 2};
    unsigned char requested_ip_4[BYTES_IN_IP] = {0, 0, 0, 0};
    unsigned char requested_ip_5[BYTES_IN_IP] = {192, 168, 110, 252};
    unsigned char requested_ip_6[BYTES_IN_IP] = {192, 168, 110, 252};
    unsigned char requested_ip_7[BYTES_IN_IP] = {192, 168, 110, 255};
    unsigned char requested_ip_8[BYTES_IN_IP] = {192, 168, 110, 255};
    
    dhcp = DHCPCreate(subnet_ip, free_bits);

    printf(U_LINE"Test DHCP Allocate 9 Free Bits IP:\n"RESET);

    printf("Test 1:\n");
    status = DHCPAllocateIp(dhcp, requested_ip_1, new_ip_1);
    result_ip[0] = 192;
    result_ip[1] = 168;
    result_ip[2] = 110;
    result_ip[3] = 1;
    printf("The new ip_1 is: %d.%d.%d.%d\n", new_ip_1[0], new_ip_1[1], new_ip_1[2], new_ip_1[3]);
    PRINT_TEST(0 == strncmp((char *)new_ip_1, (char *)result_ip, BYTES_IN_IP));
	PRINT_TEST(SUCCESS == status);

    printf("Test 2:\n");
    status = DHCPAllocateIp(dhcp, requested_ip_2, new_ip_2);
    result_ip[0] = 192;
    result_ip[1] = 168;
    result_ip[2] = 110;
    result_ip[3] = 2;
    printf("The new ip_2 is: %d.%d.%d.%d\n", new_ip_2[0], new_ip_2[1], new_ip_2[2], new_ip_2[3]);
    PRINT_TEST(0 == strncmp((char *)new_ip_2, (char *)result_ip, BYTES_IN_IP));
	PRINT_TEST(SUCCESS == status);

    printf("Test 3:\n");
    status = DHCPAllocateIp(dhcp, requested_ip_3, new_ip_3);
    printf("The new ip_3 is: %d.%d.%d.%d\n", new_ip_3[0], new_ip_3[1], new_ip_3[2], new_ip_3[3]);
	PRINT_TEST(SUCCESS == status);

    printf("Test 4:\n");
    status = DHCPAllocateIp(dhcp, requested_ip_4, new_ip_4);
    printf("The new ip_4 is: %d.%d.%d.%d\n", new_ip_4[0], new_ip_4[1], new_ip_4[2], new_ip_4[3]);
	PRINT_TEST(SUCCESS == status);

    printf("Test 5:\n");
    status = DHCPAllocateIp(dhcp, requested_ip_5, new_ip_5);
    printf("The new ip_5 is: %d.%d.%d.%d\n", new_ip_5[0], new_ip_5[1], new_ip_5[2], new_ip_5[3]);
	PRINT_TEST(SUCCESS == status);

    printf("Test 6:\n");
    status = DHCPAllocateIp(dhcp, requested_ip_6, new_ip_6);
    printf("The new ip_6 is: %d.%d.%d.%d\n", new_ip_6[0], new_ip_6[1], new_ip_6[2], new_ip_6[3]);
	PRINT_TEST(SUCCESS == status);

    printf("Test 7:\n");
    status = DHCPAllocateIp(dhcp, requested_ip_7, new_ip_7);
    printf("The new ip_7 is: %d.%d.%d.%d\n", new_ip_7[0], new_ip_7[1], new_ip_7[2], new_ip_7[3]);
	PRINT_TEST(SUCCESS == status);

    printf("Test 8:\n");
    status = DHCPAllocateIp(dhcp, requested_ip_8, new_ip_8);
    printf("The new ip_8 is: %d.%d.%d.%d\n", new_ip_8[0], new_ip_8[1], new_ip_8[2], new_ip_8[3]);
	PRINT_TEST(SUCCESS == status);

	DHCPDestroy(dhcp);
}

static void TestDHCPFreeIp()
{
	dhcp_t *test_dhcp = NULL;
	unsigned char test_ip[BYTES_IN_IP] = {10, 10, 0, 5};
	size_t free_bits = 8;
	unsigned char result[BYTES_IN_IP] = {0};
	unsigned char requested_ip_1[BYTES_IN_IP] = {10, 10, 0, 8};
	unsigned char requested_ip_2[BYTES_IN_IP] = {10, 10, 0, 9};
	unsigned char requested_ip_3[BYTES_IN_IP] = {10, 10, 0, 253};
	unsigned char requested_ip_4[BYTES_IN_IP] = {10, 10, 0, 1};
	unsigned char invalid_free_ip_1[BYTES_IN_IP] = {10, 20, 0, 2};
	unsigned char invalid_free_ip_2[BYTES_IN_IP] = {10, 10, 0, 255};
	unsigned char duoble_free_ip_1[BYTES_IN_IP] = {10, 10, 0, 9};
	unsigned char duoble_free_ip_2[BYTES_IN_IP] = {10, 10, 0, 55};

	printf(U_LINE"\nTest DHCP Free Ip:\n\n"RESET);

	test_dhcp = DHCPCreate(test_ip, free_bits);

    DHCPAllocateIp(test_dhcp, requested_ip_1, result);
	DHCPAllocateIp(test_dhcp, requested_ip_2, result);
	DHCPAllocateIp(test_dhcp, requested_ip_3, result);

	PRINT_TEST(pow(2, free_bits) - 6 == DHCPCountFree(test_dhcp));

	PRINT_TEST(SUCCESS == DHCPFreeIp(test_dhcp, requested_ip_1));
	PRINT_TEST(pow(2, free_bits) - 5 == DHCPCountFree(test_dhcp));

	PRINT_TEST(INVALID_FREE == DHCPFreeIp(test_dhcp, invalid_free_ip_1));
	PRINT_TEST(pow(2, free_bits) - 5 == DHCPCountFree(test_dhcp));

	PRINT_TEST(INVALID_FREE == DHCPFreeIp(test_dhcp, invalid_free_ip_2));
	PRINT_TEST(pow(2, free_bits) - 5 == DHCPCountFree(test_dhcp));

	PRINT_TEST(SUCCESS == DHCPAllocateIp(test_dhcp, requested_ip_1, result));
	PRINT_TEST(pow(2, free_bits) - 6 == DHCPCountFree(test_dhcp));

	PRINT_TEST(SUCCESS == DHCPFreeIp(test_dhcp, requested_ip_2));
	PRINT_TEST(pow(2, free_bits) - 5 == DHCPCountFree(test_dhcp));

	PRINT_TEST(DOUBLE_FREE == DHCPFreeIp(test_dhcp, duoble_free_ip_1));
	PRINT_TEST(pow(2, free_bits) - 5 == DHCPCountFree(test_dhcp));

	PRINT_TEST(DOUBLE_FREE == DHCPFreeIp(test_dhcp, duoble_free_ip_2));
	PRINT_TEST(pow(2, free_bits) - 5 == DHCPCountFree(test_dhcp));

	PRINT_TEST(SUCCESS == DHCPAllocateIp(test_dhcp, requested_ip_4, result));
	PRINT_TEST(pow(2, free_bits) - 6 == DHCPCountFree(test_dhcp));

	PRINT_TEST(SUCCESS == DHCPFreeIp(test_dhcp, result));
	PRINT_TEST(pow(2, free_bits) - 5 == DHCPCountFree(test_dhcp));	

	PRINT_TEST(SUCCESS == DHCPAllocateIp(test_dhcp, requested_ip_4, result));
	PRINT_TEST(pow(2, free_bits) - 6 == DHCPCountFree(test_dhcp));

	DHCPDestroy(test_dhcp);
}