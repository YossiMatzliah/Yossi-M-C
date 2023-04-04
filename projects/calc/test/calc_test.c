/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :					*
*	Date      : 04/04/2023			*
************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc, free */
#include <string.h>	/* str funcs */

#include "calc.h"

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

static void TestCalcCreateDestroy();

/*****************************************************************/

int main()
{
	TestCalcCreateDestroy();
	
	return 0;
}


static void TestCalcCreateDestroy()
{
	calc_t *calc = CalcCreate(100);
	char expression[100] = "1+1";
	double result = 0;
	
	PRINT_TEST(calc != NULL);
	
	Calculator(calc, expression, &result);
	
	PRINT_TEST(result == (double)2);
	
	CalcDestroy(calc);
}






/***************************************************************/

