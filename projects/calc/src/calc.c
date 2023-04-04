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

#include "stack.h"
#include "calc.h"

#define NUM_OF_CHARS	(256)

#define FALSE	(0)
#define TRUE	(1)

#define FAILURE	(1)

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
} ;

typedef enum state
{
	INITIAL,
	ACCEPT,
	EXPECTING_OP,
	EXPECTING_NUM,
	ERROR,
	CALC,
	END,
	NUM_OF_STATES
} state_t;

typedef enum operator
{
	PLUS = '+',
	MINUS = '-',
	MULTIPLY = '*',
	DIVIDE = '/',
	POW = '^',
	LEFTPAR = '(',
	RIGHTPAR = ')',
	STRING_END = '\0',
	NUM_OF_OP = 8
} event_t;

typedef state_t (*EventHandler)(calc_t *calc, char *expression, calc_status_t *status, double *result);

/************** static func *****************/

static state_t PushNum(calc_t *calc, char *expression, calc_status_t *status, double *result);
static state_t PushOp(calc_t *calc, char *expression, calc_status_t *status, double *result);
static state_t CalcFunc(calc_t *calc, char *expression, calc_status_t *status, double *result);
static char PeekAndPop(stack_t *stack);
static state_t Add(stack_t *stack, calc_status_t *status);
static state_t Mul(stack_t *stack, calc_status_t *status);
static state_t Sub(stack_t *stack, calc_status_t *status);
static state_t Div(stack_t *stack, calc_status_t *status);
static state_t Pow(stack_t *stack, calc_status_t *status);
static state_t ErrorState(calc_t *calc, char *expression, calc_status_t *status, double *result);

/********************************************/

calc_t *CalcCreate(size_t max_exp)
{
	calc_t *calc = NULL;
	
	assert(max_exp != sizeof(double));
	
	calc = malloc(sizeof(calc_t));
	if (NULL != calc)
	{
		calc->stack[OPERAND] = StackCreate(max_exp, sizeof(double));
		calc->stack[OPERATOR] = StackCreate(max_exp, sizeof(unsigned char));
		
		if (NULL == calc->stack[OPERAND] || NULL == calc->stack[OPERATOR])
		{
			free(calc->stack[OPERAND]);
			free(calc->stack[OPERATOR]);
			free(calc);
		}
	}

	return calc;
}

calc_status_t Calculator(calc_t *calc, const char *expression, double *result)
{
	calc_status_t status = NOT_SUPPORTED;
	state_t state = INITIAL;
	state_t next_state = INITIAL;
	event_t event = PLUS;
	size_t i = 0;
	size_t j = 0;

	EventHandler states_lut[NUM_OF_CHARS][NUM_OF_STATES] = {{ErrorState}};

	for (i = 0; i < NUM_OF_STATES; ++i)
	{
		for (j = 0; j < NUM_OF_CHARS; ++j)
		{
			states_lut[i][j] = ErrorState;
		}
	}

	for (i = '0'; i <= '9'; ++i)
    {
        states_lut[i][INITIAL] = PushNum;
        states_lut[i][EXPECTING_NUM] = PushNum;
    }

	states_lut['+'][EXPECTING_OP] = PushOp;
	states_lut['-'][EXPECTING_OP] = PushOp;
	states_lut['*'][EXPECTING_OP] = PushOp;
	states_lut['/'][EXPECTING_OP] = PushOp;
	states_lut['^'][EXPECTING_OP] = PushOp;

	states_lut['\0'][EXPECTING_OP] = CalcFunc;

	while (event != STRING_END || state == ERROR)
	{
		event = *(char*)expression;
		next_state = states_lut[event][state](calc, (char *)expression, &status, result);
		state = next_state;
		++expression;
	}

	return status;
}

void CalcDestroy(calc_t *calc)
{
	assert(NULL != calc);
	
	StackDestroy(calc->stack[OPERATOR]);
	StackDestroy(calc->stack[OPERAND]);
	free(calc);
}


/************************ Static Functions ************************/

state_t PushNum(calc_t *calc, char *expression, calc_status_t *status, double *result)
{
	double num = 0;
	errno = 0;
	num = strtod(expression, &expression);
	
	if (errno == 0)
	{
		StackPush(calc->stack[OPERAND], (const void *)&num);
		*status = SUCCESS;
		
		return EXPECTING_OP;
	}
	else
	{
		*status = NOT_SUPPORTED;
		*result = 0;
		
		return ERROR;
	}
}

state_t PushOp(calc_t *calc, char *expression, calc_status_t *status, double *result)
{
	char operator = *expression;
	StackPush(calc->stack[OPERATOR], (const void *)&operator);
	
	*status = SUCCESS;
	(void)result;
	
	return EXPECTING_NUM;
}


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
	*status = SUCCESS;

	return CALC;
}

static state_t Sub(stack_t *stack, calc_status_t *status)
{
	double a = PeekAndPop(stack);
	double b = PeekAndPop(stack);
	double res = a - b;
	
	StackPush(stack, &res);
	status = SUCCESS;

	return CALC;
}

static state_t Mul(stack_t *stack, calc_status_t *status)
{
	double a = PeekAndPop(stack);
	double b = PeekAndPop(stack);
	double res = a * b;
	
	StackPush(stack, &res);
	*status = SUCCESS;

	return CALC;
}

static state_t Div(stack_t *stack, calc_status_t *status)
{
	double a = PeekAndPop(stack);
	double b = PeekAndPop(stack);
	double res = 0;
	
	if (0 == b)
	{
		*status = DIVISION_BY_ZERO;
		return ERROR;
	}
	res = a / b;
	
	StackPush(stack, &res);
	*status = SUCCESS;
	return CALC;
}

static state_t Pow(stack_t *stack, calc_status_t *status)
{
	double base = PeekAndPop(stack);
	double power = PeekAndPop(stack);
	double res = pow(base,power);
	
	StackPush(stack, &res);
	*status = SUCCESS;
	return CALC;
}

static state_t ErrorState(calc_t *calc, char *expression, calc_status_t *status, double *result)
{
	*status = SYNTAX_ERROR;
	*result = 0;
	calc = calc;
	expression = expression;
	return ERROR;
}	

static state_t CalcFunc(calc_t *calc, char *expression, calc_status_t *status, double *result)
{
	double lhs = 0;
	double rhs = 0;
	char operator = 0;
	
	rhs = *(double *)StackPeek(calc->stack[OPERAND]);
	StackPop(calc->stack[OPERAND]);
	lhs = *(double *)StackPeek(calc->stack[OPERAND]);
	StackPop(calc->stack[OPERAND]);
	operator = *(char *)StackPeek(calc->stack[OPERATOR]);
	StackPop(calc->stack[OPERATOR]);
	*result = lhs + rhs;

	StackPush(calc->stack[OPERAND], (void *)&result);
	*status = SUCCESS;
	
	*expression = *expression;

	return END;
}

