/************************************
 *	Developer :	Yossi Matzliah      *
 *	Reviewer  :	Lilach				*
 *	Date      : 09/04/2023			*
 ***********************************/

#include <stdio.h>	/* printf */

#include "calc.h"

#define U_LINE 	"\033[1m\033[4m"
#define RED   	"\033[1m\033[41m\x1B[30m"
#define GRN   	"\033[1m\033[42m\x1B[30m"
#define RESET 	"\033[0m"

#define TRUE 	(1)
#define FALSE 	(0)
#define FAILURE (1)

#define PRINT_TEST(x) ((TRUE == (x)) ? printf(GRN"SUCCESS!"RESET"\n\n") : printf(RED"FAILURE!, line %d"RESET"\n\n", __LINE__))

#define NEW_LINE printf("\n")

#define MAX_EXP (100)
#define NUM_OF_TESTS (84)
#define NUM_ERR_TESTS (7)

/*****************************************************************/

static void TestCalcCreateDestroy();
static void TestCalculator();
static void TestErrCalculator();

/*****************************************************************/

int main()
{
	TestCalcCreateDestroy();
	TestCalculator();
	TestErrCalculator();

	return 0;
}


static void TestCalcCreateDestroy()
{
	calc_t *calc = CalcCreate(MAX_EXP);

	printf(U_LINE"Test Calc Create:\n"RESET);

	PRINT_TEST(calc != NULL);

	CalcDestroy(calc);
}

static void TestCalculator()
{
	calc_t *calc = CalcCreate(MAX_EXP);
	double result = 0;
	size_t i = 0;
	
	typedef struct calc_test
	{
		char expression[MAX_EXP];
		double res;
	}calc_test_t;

	calc_test_t test_arr[NUM_OF_TESTS] = 
	{
		{"1 + 1", 2},
		{"1 + 3 - 7", -3},
		{"2 * 3", 6},
		{"7 - 10", -3},
		{"1 / 4", 0.25},
		{"2 ^ 3", 8},
		{"2 ^ 3 ^ 2", 512},
		{"2 + 5 +  3", 10},
		{"2 * 3 * 4", 24},
		{"-1 + 10", 9},
		{"+4 + 3", 7},
		{"1 + 3 * 7", 22},
		{"2 * 3 + 1", 7},
		{"1 + 2 * 3", 7},
		{"-1 + 8", 7},
		{"-1 - -8", 7},
		{"+9 - -8", 17},
		{"2 * (3 + 4)", 14},
		{"(3 + 4)*  2", 14},
		{"1 / 2 + 2", 2.5},
		{"2 + 1 / 2", 2.5},
		{"3*(2+1)", 9},
		{"10 - -5", 15},
		{"-5 + 10 + 15", 20},
		{"3 ^ 2", 9},
		{"9 / 3", 3},
		{"(5 + 3) * 2", 16},
		{"2 + 3 * 4", 14},
		{"(2 + 3) * 4", 20},
		{"2 ^ 0", 1},
		{"(2 + 3) ^ 2", 25},
		{"1 + 2 * 3 + 4 * 5 + 6", 33},
		{"(1 + 2) * (3 + 4)", 21},
		{"(1 + 2) * 3 + 4", 13},
		{"1 * 2 + 3 * 4", 14},
		{"3 ^ 2 + 4 ^ 2", 25},
		{"2 ^ 2 + 3 ^ 2 + 4 ^ 2", 29},
		{"(1 + 2) * 3", 9},
		{"(2 * 3) + 4", 10},
		{"(5 - 2) * (4 + 1)", 15},
		{"(10 - 5) / 5", 1},
		{"(3 + 5) / (2 * 2)", 2},
		{"(2 * 3) ^ 2", 36},
		{"(3 + 4) ^ 2", 49},
		{"(4 - 2) ^ 3", 8},
		{"2 * (3 + 4)", 14},
		{"4 / (2 + 2)", 1},
		{"(2 ^ 3) / 4", 2},
		{"3 * (4 + 5) / 2", 13.5},
		{"(3 + 4 * 5) / (2 - 3)", -23},
		{"(2 * 3 + 4) * 5", 50},
		{"(2 + 3) * (4 + 5)", 45},
		{"(1 + 2 + 3 + 4) * 5", 50},
		{"5 * (1 + 2 + 3 + 4)", 50},
		{"(2 + 3) * 4 - 5", 15},
		{"2 + (3 * 4 - 5)", 9},
		{"(1 + 2) ^ (3 - 1)", 9},
		{"2 ^ (1 + 3)", 16},
		{"(3 - 1) ^ (1 + 2)", 8},
		{"2 + 3 * 4 ^ 2", 50},
		{"(2 + 3) * 4 ^ 2", 80},
		{"(2 ^ 3) * (4 / 2)", 16},
		{"2 ^ (3 * 4) / 4", 1024},
		{"(2 * 3) + (4 * 5) - (6 / 3)", 24},
		{"(1 + 2) * (3 + 4) * (5 + 6)", 231},
		{"(1 + 1) ^ (0 + 2) ^ 3", 256},
		{"2 + (3 * 4) ^ 2 + 5", 151},
		{"(2 + 3 * 4) ^ 2 + 5", 201},
		{"(2 ^ 3) * (4 / 2) + 5", 21},
		{"2 ^ (3 * 4) / 4 - 5", 1019},
		{"(2 * 3) + (4 * 5) - (6 / 3) ^ 2", 22},
		{"(1 + 2) * (3 + 4) * (5 + 6) / 7", 33},
		{"3 ^ 2 ^ 2 * 3", 243},
		{"-(1 + 2)", -3},
		{"+(1 + 2)", 3},
		{"((+3 - -2) * 4 - 2) / (5 - 1)", 4.5},
		{"(2 + (3 * 4)) / ((-5 + +9) * 2)", 1.75},
		{"((2 + 3) * (4 - 1)) / (5 - (2 + 1))", 7.5},
		{"((10 / 2) - 3) * ((+6 - 2)^2)", 32},
		{"((2 * 3) + 4) / ((5 - 1) * (2 - 1))", 2.5},
		{"((10 - (3 * 2)) / 4) + (6 - 2)^2", 17},
		{"((5 - 2) * ((3 + 4) / 2)) / (2 + 1)", 3.5},
		{"(-2) *-(2^4)", 32},
		{"(1 + 1) ^ (0 + 2) ^ 3", 256}
	} ;

	printf(U_LINE"\nTest Calculator:\n"RESET);

	PRINT_TEST(calc != NULL);
	
	for (i = 0; i < NUM_OF_TESTS; ++i)
	{
		Calculator(calc, test_arr[i].expression, &result);
		printf("Result is %f\n", result);
		PRINT_TEST(result == (double)test_arr[i].res);
		NEW_LINE;
	}

	CalcDestroy(calc);
}

static void TestErrCalculator()
{
	calc_t *calc = CalcCreate(MAX_EXP);
	calc_status_t status = SUCCESS;
	double result = 0;
	size_t i = 0;

	typedef struct calc_err_test
	{
		char str[450];
		calc_status_t err_code;
	} calc_err_test_t;

	calc_err_test_t test_err[NUM_ERR_TESTS] = 
	{
		{"1 / 0", DIVISION_BY_ZERO},
		{"100 ^100 ^100 ^100 ^100 ^100 ^100 ^100 ^100", RANGE_EXCEEDED},
		{"1a + 2", SYNTAX_ERROR},
		{"1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1", EXPRESSION_EXCEEDED},
		{"(1 + 1", UNBALANCED_PARANTHESIS},
		{"1 + 1)", UNBALANCED_PARANTHESIS},
		{"(3-2)*5+ 5*(4+4+4", UNBALANCED_PARANTHESIS}
	};

	printf(U_LINE"\nTest Calculator Errors:\n"RESET);

	PRINT_TEST(calc != NULL);
	
	for (i = 0; i < NUM_ERR_TESTS; ++i)
	{
		status = Calculator(calc, test_err[i].str, &result);
		printf("Status is: %d\n", status);
		PRINT_TEST(test_err[i].err_code == status);
		NEW_LINE;
	}

	CalcDestroy(calc);

}

