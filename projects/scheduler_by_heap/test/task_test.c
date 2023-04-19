/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Lilach 	  			*
*	Date      : 05/03/2023			*
************************************/

#include <stdio.h>	/* perror */
#include <stdlib.h>	/* malloc, free */
#include <unistd.h>	/* sleep */

#define __USE_XOPEN /* to remove warning for strptime */

#include "uid.h"	
#include "task.h"

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

static void CreateDestroyTest();
static void RunTaskTest();
static void GetExecTimeTest();
static void GetIntervalTest();
static void GetUIDTest();
static void GetFuncTest();
static void GetParamsTest();
static void SetExecTimeTest();
static void SetIntervalTest();
static void SetFuncTest();
static void SetParamsTest();

int PrintFunc(void *params);
int FailedFunc(void *params);
int DoNothing(void *params);

/**********************************************************/

int main()
{
	CreateDestroyTest();
	
	RunTaskTest();
		
	GetExecTimeTest();
	
	GetIntervalTest();
	
	GetUIDTest();
	
	GetFuncTest();
	
	GetParamsTest();
	
	SetExecTimeTest();
	
	SetIntervalTest();
	
	SetFuncTest();
	
	SetParamsTest();

	return 0; 
}

static void CreateDestroyTest()
{
	task_t *task = NULL;
	
	printf(U_LINE"\nTesting Create\n"RESET);
	task = TaskCreate(PrintFunc, NULL, 0, 0);
	PRINT_TEST(NULL != task);
	PRINT_TEST(FALSE == UIDIsSame(TaskGetUID(task), UIDGetBad())); 
	NEW_LINE;
	
	TaskDestroy(task);
}

static void RunTaskTest()
{
	task_t *task_print = NULL;
	task_t *task_fail = NULL;
	
	printf(U_LINE"\nTesting Run Task\n"RESET);
	task_print = TaskCreate(PrintFunc, NULL, 0, 0);
	PRINT_TEST(NULL != task_print);
	
	PRINT_TEST(SUCCESS == TaskRunTask(task_print));
	
	task_fail = TaskCreate(FailedFunc, NULL, 0, 0);
	PRINT_TEST(FAILURE == TaskRunTask(task_fail));
	NEW_LINE;
	
	TaskDestroy(task_fail);
	TaskDestroy(task_print);
}

static void GetExecTimeTest()
{
	task_t *task = NULL;
	struct tm tm = {0};
	time_t t;

	printf(U_LINE"\nTesting GetExecTime\n"RESET);
	strptime("23 Aug 1989 08:22:31", "%d %b %Y %H:%M:%S", &tm);
	t = mktime(&tm);
	
	task = TaskCreate(DoNothing, NULL, t, 0);
	
	PRINT_TEST(t == TaskGetExecTime(task));
	
	t = time(0);
	
	PRINT_TEST(t != TaskGetExecTime(task));
	NEW_LINE;
	
	TaskDestroy(task);
}

static void GetIntervalTest()
{
	task_t *task = NULL;
	
	printf(U_LINE"\nTesting GetInterval\n"RESET);
	task = TaskCreate(DoNothing, NULL, 0, 1);
	
	PRINT_TEST(1 == TaskGetInterval(task));
	
	PRINT_TEST(2 != TaskGetInterval(task));
	NEW_LINE;
	
	TaskDestroy(task);
}

static void GetUIDTest()
{
	task_t *task = NULL;
	task_t *task2 = NULL;
	ilrd_uid_t uid;
	ilrd_uid_t bad;
	
	printf(U_LINE"\nTesting GetUID\n"RESET);
	task = TaskCreate(DoNothing, NULL, 1, 1);
	
	bad = UIDGetBad();
	
	PRINT_TEST(FALSE == UIDIsSame(TaskGetUID(task), bad));
	
	PRINT_TEST(TRUE == UIDIsSame(TaskGetUID(task), TaskGetUID(task)));
	
	uid = TaskGetUID(task);
	task2 = TaskCreate(DoNothing, NULL, 1, 1);
	PRINT_TEST(TRUE == UIDIsSame(uid, TaskGetUID(task)));
	PRINT_TEST(FALSE == UIDIsSame(uid, TaskGetUID(task2)));
	NEW_LINE;
	
	TaskDestroy(task);
	TaskDestroy(task2);
}

static void GetFuncTest()
{
	task_t *task = NULL;
	task_t *task2 = NULL;
	int (*func_pointer)(void *) = NULL;
	int (*func_pointer2)(void *) = NULL;
	
	printf(U_LINE"\nTesting GetFunc\n"RESET);
	task = TaskCreate(DoNothing, NULL, 0, 0);
	func_pointer = TaskGetFunc(task);
	PRINT_TEST(func_pointer == DoNothing);
	PRINT_TEST(func_pointer != FailedFunc);
	
	task2 = TaskCreate(FailedFunc, NULL, 0, 0);
	func_pointer2 = TaskGetFunc(task2);
	PRINT_TEST(func_pointer2 == FailedFunc);
	PRINT_TEST(func_pointer != func_pointer2);
	NEW_LINE;
	
	TaskDestroy(task);
	TaskDestroy(task2);
}

static void GetParamsTest()
{
	task_t *task = NULL;
	task_t *task2 = NULL;
	void *param1 = NULL;
	void *param2 = NULL;
	int checker = 7;
	
	printf(U_LINE"\nTesting GetParams\n"RESET);
	task = TaskCreate(DoNothing, NULL, 0, 0);
	param1 = TaskGetParams(task);
	PRINT_TEST(NULL == param1);
	PRINT_TEST(&checker != param1);
	
	task2 = TaskCreate(FailedFunc, &checker, 0, 0);
	param2 = TaskGetParams(task2);	
	PRINT_TEST(*(int *)param2 == checker);
	PRINT_TEST(param2 == &checker);
	PRINT_TEST(param2 != param1);
	NEW_LINE;
	
	TaskDestroy(task);
	TaskDestroy(task2);
}

static void SetExecTimeTest()
{
	task_t *task = NULL;
	struct tm tm = {0};
	time_t t;
	
	printf(U_LINE"\nTesting SetExecTime\n"RESET);
	strptime("23 Aug 1989 08:22:31", "%d %b %Y %H:%M:%S", &tm);
	t = mktime(&tm);
	
	task = TaskCreate(DoNothing, NULL, 0, 0);
	PRINT_TEST(t != TaskGetExecTime(task));
	
	TaskSetExecTime(task, t);
	PRINT_TEST(t == TaskGetExecTime(task));
	NEW_LINE;
	
	TaskDestroy(task);
}

static void SetIntervalTest()
{
	task_t *task = NULL;
	struct tm tm = {0};
	time_t t;
	
	printf(U_LINE"\nTesting SetInterval\n"RESET);
	strptime("23 Aug 1989 08:22:31", "%d %b %Y %H:%M:%S", &tm);
	t = mktime(&tm);
	
	task = TaskCreate(DoNothing, NULL, 0, 0);
	PRINT_TEST(t != TaskGetInterval(task));
	
	TaskSetInterval(task, t);
	PRINT_TEST(t == TaskGetInterval(task));
	
	TaskDestroy(task);
	
	task = TaskCreate(DoNothing, NULL, 0, 1);
	TaskSetInterval(task, 3);
	PRINT_TEST(3 == TaskGetInterval(task));
	NEW_LINE;
	
	TaskDestroy(task);
}

static void SetFuncTest()
{
	task_t *task = NULL;
	int (*func_pointer)(void *) = NULL;
	
	printf(U_LINE"\nTesting SetFunc\n"RESET);
	task = TaskCreate(DoNothing, NULL, 0, 0);
	func_pointer = TaskGetFunc(task);
	PRINT_TEST(func_pointer == DoNothing);
	
	TaskSetFunc(task, FailedFunc);
	func_pointer = TaskGetFunc(task);
	PRINT_TEST(func_pointer != DoNothing);
	PRINT_TEST(func_pointer == FailedFunc);
	NEW_LINE;
	
	TaskDestroy(task);
}

static void SetParamsTest()
{
	task_t *task = NULL;
	void *param1 = NULL;
	int num = 7;
	
	printf(U_LINE"\nTesting SetParams\n"RESET);
	task = TaskCreate(DoNothing, NULL, 0, 0);
	param1 = TaskGetParams(task);
	PRINT_TEST(NULL == param1);
	
	TaskSetParams(task, &num);
	param1 = TaskGetParams(task);
	PRINT_TEST(NULL != param1);
	PRINT_TEST(&num == param1);
	PRINT_TEST(num == *(int *)param1);	
	NEW_LINE;
	
	TaskDestroy(task);
}

int PrintFunc(void *params)
{
	(void)params;
	printf("print func\n");
	
	return 0;
}

int FailedFunc(void *params)
{
	(void)params;
	printf("just checking if failed is possible, XD\n");
	
	return 1;
}

int DoNothing(void *params)
{
	(void)params;
	
	return 0;
}


