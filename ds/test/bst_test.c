/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Daniel				*
*	Date      : 21/03/2023			*
************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc, free */
#include <string.h>	/* str funcs */

#include "bst.h"

#define U_LINE 	"\033[1m\033[4m"
#define RED   	"\033[1m\033[41m\x1B[30m"
#define GRN   	"\033[1m\033[42m\x1B[30m"
#define RESET 	"\033[0m"

#define TRUE 	(1)
#define FALSE 	(0)
#define FAILURE (1)
#define SUCCESS (0)

#define PRINT_TEST(x) ((TRUE == (x)) ? printf(GRN"SUCCESS!"RESET"\n\n") : printf(RED"FAILURE!, line %d"RESET"\n\n", __LINE__))

#define NEW_LINE printf("\n")

/*****************************************************************/

static void TestBSTCreate();
static void TestBSTIsEmpty();
static void TestBSTInsert();
static void TestBSTBeginIter();
static void TestBSTNextIter();
static void TestBSTPrevIter();
static void TestBSTFind();
static void TestBSTRemove();
static void TestBSTForEach();
static void TestBSTHeight();

int CompareFunc(const void *data1, const void *data2);
int AddParam(void *data, void *parameter);

/*****************************************************************/

int main()
{
	TestBSTCreate();
	TestBSTIsEmpty();
	TestBSTInsert();
	TestBSTInsertFind();
	TestBSTBeginIter();
	TestBSTIsSameIter();
	TestBSTFind();
	TestBSTRemove();
	TestBSTForEach();
	
	return 0;
}




int AddParam(void *data, void *param)
{
	*(int *)data += *(int *)param;
	
	return SUCCESS;
}

int CompareFunc(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);  
}
