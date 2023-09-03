/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Lilach 	  			*
*	Date      : 02/03/2023			*
************************************/

#include <stdio.h>			/* printf */
#include <string.h>			/* strcmp */
#include <unistd.h> 		/* sleep  */

#include "../include/uid.h"

#define U_LINE 	"\033[1m\033[4m"
#define RED   	"\033[1m\033[41m\x1B[30m"
#define GRN   	"\033[1m\033[42m\x1B[30m"
#define RESET 	"\033[0m"

#define TRUE  	(1)
#define FALSE 	(0)
#define FAILURE (1)
#define SUCCESS (0)

#define PRINT_TEST(x) ((TRUE == (x)) ? printf(GRN"SUCCESS!"RESET"\n\n") : printf(RED"FAILURE!, line %d"RESET"\n\n", __LINE__))

static void TestUIDCreate();
static void TestUIDIsSame();
static void TestUIDGetBad();

int main()
{
	TestUIDCreate();
	TestUIDIsSame();
	TestUIDGetBad();
	
	return 0;
}


static void TestUIDCreate()
{
	uid_t uid_create = {0};
	uid_t uid_check = {0};
	
	uid_create = UIDCreate();
	
	printf(U_LINE"\nTest UID Create:\n"RESET);
	PRINT_TEST(FALSE == UIDIsSame(UIDGetBad(), uid_create));
	
	printf("time_stamp = %ld\n", uid_create.time_stamp);
	printf("counter = %lu\n", uid_create.counter);
	printf("pid = %d\n", uid_create.pid);
	printf("ip is: %s\n", uid_create.ip);
	
	sleep(1);
	
	uid_check = UIDCreate();
	printf("time_stamp = %ld\n", uid_check.time_stamp);
	printf("counter = %lu\n", uid_check.counter);
	printf("pid = %d\n", uid_check.pid);
	printf("ip is: %s\n", uid_check.ip);
	PRINT_TEST(FALSE == UIDIsSame(uid_check, uid_create));
}

static void TestUIDIsSame()
{
	uid_t test_uid_1 = UIDCreate();
	uid_t test_uid_2 = UIDCreate();
	
	printf(U_LINE"\nTest UID Is Same:\n"RESET);
	printf("Test 1:\n");
	PRINT_TEST(TRUE == UIDIsSame(test_uid_1, test_uid_1));
	
	printf("Test 2:\n");
	PRINT_TEST(FALSE == UIDIsSame(test_uid_1, test_uid_2));
}

static void TestUIDGetBad()
{
	uid_t uid_bad = {0};
	char *test_bad_ip = "";
	int diff = 0;
	
	uid_bad = UIDGetBad();
	diff = uid_bad.time_stamp + uid_bad.counter + uid_bad.pid;
	
	printf(U_LINE"\nTest UID Get Bad:\n"RESET);
	PRINT_TEST((SUCCESS == strcmp((char *)uid_bad.ip, test_bad_ip)) && (0 == diff));
	
	printf("time_stamp = %ld\n", uid_bad.time_stamp);
	printf("counter = %lu\n", uid_bad.counter);
	printf("pid = %d\n", uid_bad.pid);
	printf("ip is: %s\n", uid_bad.ip);
}

