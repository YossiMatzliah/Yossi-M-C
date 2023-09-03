/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Lilach 	  			*
*	Date      : 05/03/2023			*
************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* system */

#include "../include/sched.h"

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

int num_to_check = 7;	/* to check param */

static void CreateDestroyTest();                           	  
static void AddRemoveTest();  
static void SizeTest();
static void ClearTest();
static void RunStopTest();

int CheckParamFunc(void *param);
int PrintFunc(void *param);
int FailedFunc(void *param);
int DoNothing(void *param);
int StopSched(void *sched_to_stop);

/***********************************************/

int main()
{
	CreateDestroyTest();
	
	AddRemoveTest();
	
	SizeTest();
	
	ClearTest();
	
	RunStopTest();

	return 0; 
}

static void CreateDestroyTest()
{
	sch_t *sched = NULL;
	
	printf(U_LINE"\nTesting SchCreate\n"RESET);
	sched = SchCreate();
	PRINT_TEST(NULL != sched);
	
	printf(U_LINE"\nTesting SchIsEmpty\n"RESET);
	PRINT_TEST(TRUE == SchIsEmpty(sched));
	NEW_LINE; 
	
	SchDestroy(sched);
}

static void AddRemoveTest()
{
	sch_t *sched = NULL;
	uid_t task_uid = {0};
	
	printf(U_LINE"\nTesting SchAdd & SchRemove\n"RESET);
	sched = SchCreate();
	
	printf("\nTest Scheduler Add Task:\n");
	task_uid = SchAddTask(sched, CheckParamFunc, (void *)&num_to_check, time(NULL) + 2, 0);
	PRINT_TEST(1 == SchSize(sched));
	PRINT_TEST(TRUE != UIDIsSame(UIDGetBad(), task_uid));
	
	printf("\nTest Scheduler Remove Task:\n");
	SchRemoveTask(sched, task_uid);
	PRINT_TEST(TRUE == SchIsEmpty(sched));
	NEW_LINE;
	
	SchDestroy(sched);
}

static void SizeTest()
{
	sch_t *sched = NULL;
	uid_t task_uid = {0};
	
	printf(U_LINE"\nTesting SchSize\n"RESET);
	sched = SchCreate();
	
	task_uid = SchAddTask(sched, CheckParamFunc, (void *)&num_to_check, time(NULL) + 2, 0);
	PRINT_TEST(1 == SchSize(sched));
	PRINT_TEST(TRUE != UIDIsSame(UIDGetBad(), task_uid));
	
	SchAddTask(sched, FailedFunc, (void *)&num_to_check, time(NULL) + 3, 0);
	SchAddTask(sched, PrintFunc, (void *)&num_to_check, time(NULL) + 5, 0);
	SchAddTask(sched, DoNothing, NULL, time(NULL) + 8, 0);
	PRINT_TEST(4 == SchSize(sched));
	NEW_LINE;
	
	SchDestroy(sched);
}

static void ClearTest()
{
	sch_t *sched = NULL;
	
	printf(U_LINE"\nTesting SchClear\n"RESET);
	sched = SchCreate();
	
	SchAddTask(sched, CheckParamFunc, (void *)&num_to_check, time(NULL) + 2, 0);
	SchAddTask(sched, FailedFunc, (void *)&num_to_check, time(NULL) + 3, 0);
	SchAddTask(sched, PrintFunc, (void *)&num_to_check, time(NULL) + 5, 0);
	SchAddTask(sched, DoNothing, NULL, time(NULL) + 8, 0);
	PRINT_TEST(4 == SchSize(sched));
	
	SchClear(sched);
	PRINT_TEST(TRUE == SchIsEmpty(sched));
	NEW_LINE;

	SchDestroy(sched);
}

static void RunStopTest()
{
	sch_t *sched = NULL;
	
	printf(U_LINE"\nTesting SchRun & SchStop\n"RESET);
	printf("Stops with failed func:\n");
	sched = SchCreate();
	SchAddTask(sched, CheckParamFunc, (void *)&num_to_check, time(NULL) + 2, 2);
	SchAddTask(sched, FailedFunc, (void *)&num_to_check, time(NULL) + 5, 0);
	SchAddTask(sched, PrintFunc, (void *)&num_to_check, time(NULL) + 1, 2);
	SchAddTask(sched, DoNothing, NULL, time(NULL) + 8, 0);
	PRINT_TEST(FAILURE == SchRun(sched));
	
	printf("Stops with SchStop func:\n");
	SchClear(sched);
	SchAddTask(sched, CheckParamFunc, (void *)&num_to_check, time(NULL) + 2, 2);
	SchAddTask(sched, PrintFunc, (void *)&num_to_check, time(NULL) + 1, 2);
	SchAddTask(sched, StopSched, sched, time(NULL) + 7, 0);
	SchAddTask(sched, PrintFunc, (void *)&num_to_check, time(NULL) + 8, 2);
	PRINT_TEST(FAILURE == SchRun(sched));
	
	printf("Stops because finished: (well done)\n");
	SchClear(sched);
	SchAddTask(sched, CheckParamFunc, (void *)&num_to_check, time(NULL) + 3, 0);
	SchAddTask(sched, PrintFunc, (void *)&num_to_check, time(NULL) + 1, 0);
	PRINT_TEST(SUCCESS == SchRun(sched));
	NEW_LINE;
	
	SchDestroy(sched);
}

int CheckParamFunc(void *param)
{
	return !(num_to_check == *(int *)param);
}

int PrintFunc(void *param)
{
	printf("print func num is: %d\n", *(int *)param);
	
	return SUCCESS;
}

int FailedFunc(void *param)
{
	(void)param;
	printf("just checking if failed is possible, XD\n");
	
	return FAILURE;
}

int DoNothing(void *param)
{
	(void)param;
	
	return SUCCESS;
}

int StopSched(void *sched_to_stop)
{
	SchStop(((sch_t *)sched_to_stop));
	
	return FAILURE;
}


