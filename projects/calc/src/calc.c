/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :					*
*	Date      : 04/04/2023			*
************************************/

#include <assert.h>	/*	assert	*/
#include <stdlib.h>	/*	malloc	*/
#include <stdio.h>	/*	perror	*/
#include <errno.h>	/*	errno	*/
#include <math.h> 	/*	pow		*/

#include "calc.h"

#define FALSE	(0)
#define TRUE	(1)

#define SUCCESS	(0)
#define FAILURE	(1)

#include "stack.h"

enum stack_type
{
    OPERAND = 0,
    OPERATOR = 1,
    NUM_OF_STACKS = 2
} stack_type_t;

struct calculator
{
	stack_t *stack[NUM_OF_STACKS];

	/* Implementation of calculator struct may vary */
};


/************** static func *****************/

static char PeekAndPop(stack_t *stack);
static state_t Add(stack_t *stack, calc_status_t *status);
static state_t Mul(stack_t *stack, calc_status_t *status);
static state_t Sub(stack_t *stack, calc_status_t *status);
static state_t Div(stack_t *stack, calc_status_t *status);
static state_t Pow(stack_t *stack, calc_status_t *status);

/********************************************/

calc_t *CalcCreate(size_t max_exp)
{
	calc_t *calc = NULL;
	

	assert (0 != max_expression);

	calc = (calc_t *)malloc(sizeof(calc_t) * max_expression);
	
	if (NULL != calc)
	{
		
	}
	return calc;
}

calc_status_t Calculator(calc_t *calc, const char *expression, double *result)
{
	calc_status_t status = NOT_SUPPORTED;
	
	return status;
}

void CalcDestroy(calc_t *calc)
{
	(void *)calc;
}


/************************ Static Functions ************************/

static char PeekAndPop(stack_t *stack)
{
	double peek = *(double *)StackPeek(stack);
	StackPop(stack);

	return peek;
}

static state_t Add(stack_t *stack, calc_status_t *status)
{
	double a = PeekAndPop(stack);
	double b = PeekAndPop(stack);
	double res = a + b;
	
	StackPush(stack, &res);
	status = (calc_status_t*)SUCCESS;

	return OPERATOR;
}

static state_t Sub(stack_t *stack, calc_status_t *status)
{
	double a = PeekAndPop(stack);
	double b = PeekAndPop(stack);
	double res = a - b;
	
	StackPush(stack, &res);
	status = SUCCESS;

	return OPERATOR;
}

static state_t Mul(stack_t *stack, calc_status_t *status)
{
	double a = PeekAndPop(stack);
	double b = PeekAndPop(stack);
	double res = a * b;
	
	StackPush(stack, &res);
	status = (calc_status_t*)SUCCESS;

	return OPERATOR;
}

static state_t Div(stack_t *stack, calc_status_t *status)
{
	double a = PeekAndPop(stack);
	double b = PeekAndPop(stack);
	double res = 0;
	
	if (0 == b)
	{
		status = (calc_status_t*)DIVISION_BY_ZERO;
		return ERROR;
	}
	res = a / b;
	
	StackPush(stack, &res);
	status = SUCCESS;
	return OPERATOR;
}

static state_t Pow(stack_t *stack, calc_status_t *status)
{
	double base = PeekAndPop(stack);
	double power = PeekAndPop(stack);
	double res = pow(base,power);
	
	StackPush(stack, &res);
	status = (calc_status_t*)SUCCESS;
	return OPERATOR;
}




