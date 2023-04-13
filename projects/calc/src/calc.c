/************************************
 *	Developer :	Yossi Matzliah      *
 *	Reviewer  :	Lilach				*
 *	Date      : 09/04/2023			*
 ***********************************/

#include <assert.h> /*	assert	*/
#include <stdlib.h> /*	malloc	*/
#include <stdio.h>	/*	perror	*/
#include <errno.h>	/*	errno	*/
#include <math.h>	/*	pow		*/
#include <string.h> /*	strlen	*/

#include "stack.h"
#include "calc.h"

#define NUM_OF_CHARS (256)

#define FALSE (0)
#define TRUE (1)

#define FAILURE (1)

enum stack_type
{
	OPERAND = 0,
	OPERATOR = 1,
	NUM_OF_STACKS = 2
} stack_type_t;

typedef enum operator
{
	PLUS = '+',
	MINUS = '-',
	MULTIPLY = '*',
	DIVIDE = '/',
	POW = '^',
	LEFTPAR = '(',
	RIGHTPAR = ')',
	SPACE = ' ',
	STRING_END = '\0',
	NUM_OF_OP = 9
} event_t;

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

enum calc_state
{
	NULL_TERM,
	PAREN_TERM,
	NUM_OF_CALC_STATES
};

typedef state_t (*event_handler_t)(calc_t *calc, char **expression, calc_status_t *status, double *result);
typedef state_t (*operator_handler_t)(stack_t *stack, calc_status_t *status, double *result);

operator_handler_t op_lut[NUM_OF_CHARS] = {0};

static int precedence_lut[NUM_OF_CHARS] = {0};

struct calculator
{
	stack_t *stack[NUM_OF_STACKS];
	event_handler_t states_lut[NUM_OF_STATES][NUM_OF_CHARS];
	state_t current_state;
	size_t max_exp;
};

/************** static func *****************/

static void InitLuts(event_handler_t states_lut[NUM_OF_STATES][NUM_OF_CHARS]);
static state_t PushNum(calc_t *calc, char **expression, calc_status_t *status, double *result);
static state_t PushOp(calc_t *calc, char **expression, calc_status_t *status, double *result);
static state_t CalcFunc(calc_t *calc, char **expression, calc_status_t *status, double *result);
static double PeekAndPop(stack_t *stack);
static state_t Add(stack_t *stack, calc_status_t *status, double *result);
static state_t Mul(stack_t *stack, calc_status_t *status, double *result);
static state_t Sub(stack_t *stack, calc_status_t *status, double *result);
static state_t Div(stack_t *stack, calc_status_t *status, double *result);
static state_t Pow(stack_t *stack, calc_status_t *status, double *result);
static state_t SkipSpace(calc_t *calc, char **expression, calc_status_t *status, double *result);
static state_t DiscardPar(stack_t *stack, calc_status_t *status, double *result);
static state_t ParError(stack_t *stack, calc_status_t *status, double *result);
static state_t ErrorState(calc_t *calc, char **expression, calc_status_t *status, double *result);
static state_t ErrorOp(stack_t *stack, calc_status_t *status, double *result);
static void CalcClean(calc_t *calc);

/********************************************/

calc_t *CalcCreate(size_t max_exp)
{
	calc_t *calc = NULL;

	assert(0 != max_exp);

	calc = malloc(sizeof(calc_t));
	if (NULL != calc)
	{
		calc->stack[OPERAND] = StackCreate(max_exp, sizeof(double));
		calc->stack[OPERATOR] = StackCreate(max_exp, sizeof(unsigned char));
		calc->current_state = INITIAL;
		calc->max_exp = max_exp;

		if (NULL == calc->stack[OPERAND] || NULL == calc->stack[OPERATOR])
		{
			perror("error");
			free(calc->stack[OPERAND]);
			free(calc->stack[OPERATOR]);
			free(calc);

			return NULL;
		}

		InitLuts((calc->states_lut));
	}

	return calc;
}

void CalcDestroy(calc_t *calc)
{
	assert(NULL != calc);

	StackDestroy(calc->stack[OPERATOR]);
	StackDestroy(calc->stack[OPERAND]);
	free(calc);
}

calc_status_t Calculator(calc_t *calc, const char *expression, double *result)
{
	calc_status_t status = SYNTAX_ERROR;
	event_t event = PLUS;
	char *input_runner = 0;

	assert(calc != NULL);
	assert(expression != NULL);
	assert(result != NULL);

	if (strlen(expression) > calc->max_exp)
	{
		*result = 0;
		calc->current_state = ERROR;
		return EXPRESSION_EXCEEDED;
	}

	input_runner = (char *)expression;
	calc->current_state = INITIAL;

	while (event != STRING_END && calc->current_state != ERROR)
	{
		event = *input_runner;
		calc->current_state = calc->states_lut[calc->current_state][event](calc, &input_runner, &status, result);
	}

	CalcClean(calc);

	return status;
}

/************************ Static Functions ************************/

static void InitLuts(event_handler_t states_lut[NUM_OF_STATES][NUM_OF_CHARS])
{
	size_t i = 0;
	size_t j = 0;

	for (i = 0; i < NUM_OF_CHARS; ++i)
	{
		op_lut[i] = ErrorOp;

		for (j = 0; j < NUM_OF_STATES; ++j)
		{
			states_lut[j][i] = ErrorState;
		}
	}

	for (i = '0'; i <= '9'; ++i)
	{
		states_lut[INITIAL][i] = PushNum;
		states_lut[EXPECTING_NUM][i] = PushNum;
		states_lut[CALC][i] = PushNum;
	}

	states_lut[INITIAL]['+'] = PushNum;
	states_lut[INITIAL]['-'] = PushNum;
	states_lut[INITIAL]['('] = PushOp;
	states_lut[INITIAL][' '] = SkipSpace;
	states_lut[INITIAL]['\0'] = ErrorState;

	states_lut[EXPECTING_NUM]['+'] = PushNum;
	states_lut[EXPECTING_NUM]['-'] = PushNum;
	states_lut[EXPECTING_NUM]['('] = PushOp;
	states_lut[EXPECTING_NUM][' '] = SkipSpace;

	states_lut[EXPECTING_OP]['+'] = PushOp;
	states_lut[EXPECTING_OP]['-'] = PushOp;
	states_lut[EXPECTING_OP]['*'] = PushOp;
	states_lut[EXPECTING_OP]['/'] = PushOp;
	states_lut[EXPECTING_OP]['^'] = PushOp;
	states_lut[EXPECTING_OP]['('] = PushOp;
	states_lut[EXPECTING_OP][' '] = SkipSpace;
	states_lut[EXPECTING_OP][')'] = CalcFunc;
	states_lut[EXPECTING_OP]['\0'] = CalcFunc;

	states_lut[CALC]['+'] = PushNum;
	states_lut[CALC]['-'] = PushNum;
	states_lut[CALC]['*'] = PushOp;
	states_lut[CALC]['/'] = PushOp;
	states_lut[CALC]['^'] = PushOp;
	states_lut[CALC]['('] = PushOp;
	states_lut[CALC][' '] = SkipSpace;
	states_lut[CALC][')'] = CalcFunc;
	states_lut[CALC]['\0'] = CalcFunc;

	op_lut['+'] = Add;
	op_lut['-'] = Sub;
	op_lut['*'] = Mul;
	op_lut['/'] = Div;
	op_lut['^'] = Pow;
	op_lut['('] = DiscardPar;
	op_lut[')'] = ParError;

	precedence_lut['+'] = 1;
	precedence_lut['-'] = 1;
	precedence_lut['*'] = 2;
	precedence_lut['/'] = 2;
	precedence_lut['^'] = 3;
	precedence_lut['('] = 4;
	precedence_lut[')'] = 4;
}

static state_t PushNum(calc_t *calc, char **expression, calc_status_t *status, double *result)
{
	double num = 0;
	char operator= ** expression;
	state_t state = INITIAL;
	errno = 0;

	if (1 == precedence_lut[(int)operator] && '(' == *(*expression + 1))
	{
		num = (('-' == **expression) ? -1 : 1);
		operator= '*';

		StackPush(calc->stack[OPERAND], (const void *)&num);
		StackPush(calc->stack[OPERATOR], (const void *)&operator);
		++*expression;
		*status = SUCCESS;

		return EXPECTING_NUM;
	}

	num = strtod(*expression, expression);
	
	if (errno == 0)
	{
		StackPush(calc->stack[OPERAND], (const void *)&num);
		*status = SUCCESS;
		state = EXPECTING_OP;
	}

	else
	{
		*status = SYNTAX_ERROR;
		*result = 0;
		state = ERROR;
	}

	return state;
}

static state_t PushOp(calc_t *calc, char **expression, calc_status_t *status, double *result)
{
	char operator= ** expression;
	char prev_operator = 0;
	state_t state = 0;

	while ((!StackIsEmpty(calc->stack[OPERATOR])) &&
	 	  (precedence_lut[(int)operator] < precedence_lut[(int)*(char *)StackPeek(calc->stack[OPERATOR])]) &&
	      ('(' != *(char *)StackPeek(calc->stack[OPERATOR])))
	{
		prev_operator = *(char *)StackPeek(calc->stack[OPERATOR]);
		StackPop(calc->stack[OPERATOR]);
		state = op_lut[(int)prev_operator](calc->stack[OPERAND], status, result);
	}

	StackPush(calc->stack[OPERATOR], (const void *)&operator);

	*status = SUCCESS;
	++*expression;

	return state;
}

static double PeekAndPop(stack_t *stack)
{
	double peek = *(double *)StackPeek(stack);
	StackPop(stack);

	return peek;
}

static state_t Add(stack_t *stack, calc_status_t *status, double *result)
{
	double b = PeekAndPop(stack);
	double a = PeekAndPop(stack);

	*result = a + b;

	StackPush(stack, (void *)result);
	*status = SUCCESS;

	return CALC;
}

static state_t Sub(stack_t *stack, calc_status_t *status, double *result)
{
	double b = PeekAndPop(stack);
	double a = PeekAndPop(stack);

	*result = a - b;

	StackPush(stack, (void *)result);
	*status = SUCCESS;

	return CALC;
}

static state_t Mul(stack_t *stack, calc_status_t *status, double *result)
{
	double b = PeekAndPop(stack);
	double a = PeekAndPop(stack);

	*result = a * b;

	StackPush(stack, (void *)result);
	*status = SUCCESS;

	return CALC;
}

static state_t Div(stack_t *stack, calc_status_t *status, double *result)
{
	double b = PeekAndPop(stack);
	double a = PeekAndPop(stack);
	*result = 0;

	if (0 == b)
	{
		*status = DIVISION_BY_ZERO;
		return ERROR;
	}

	*result = a / b;

	StackPush(stack, (void *)result);

	*status = SUCCESS;

	return CALC;
}

static state_t Pow(stack_t *stack, calc_status_t *status, double *result)
{
	double power = PeekAndPop(stack);
	double base = PeekAndPop(stack);
	*result = pow(base, power);

	if (errno != 0)
	{
		*result = 0;

		*status = RANGE_EXCEEDED;
		StackPush(stack, (void *)result);
		return ERROR;
	}

	StackPush(stack, (void *)result);
	*status = SUCCESS;

	return CALC;
}

static state_t DiscardPar(stack_t *stack, calc_status_t *status, double *result)
{
	*status = SUCCESS;
	(void)stack;
	(void)result;

	return EXPECTING_OP;
}

static state_t ParError(stack_t *stack, calc_status_t *status, double *result)
{
	*status = UNBALANCED_PARANTHESIS;
	(void)stack;
	*result = 0;

	return ERROR;
}

static state_t ErrorState(calc_t *calc, char **expression, calc_status_t *status, double *result)
{
	*status = SYNTAX_ERROR;
	(void)calc;
	(void)*expression;
	*result = 0;

	return ERROR;
}

static state_t ErrorOp(stack_t *stack, calc_status_t *status, double *result)
{
	*status = SYNTAX_ERROR;
	(void)stack;
	*result = 0;

	return ERROR;
}

static state_t SkipSpace(calc_t *calc, char **expression, calc_status_t *status, double *result)
{
	*status = SUCCESS;
	(void)calc;
	(void)result;
	++*expression;

	return calc->current_state;
}

static state_t CalcFunc(calc_t *calc, char **expression, calc_status_t *status, double *result)
{
	int paren_stat = !!(**expression);
	char operator= 0;
	state_t state = CALC;
	size_t i = 0;
	size_t j = 0;
	operator_handler_t op_lut[NUM_OF_CALC_STATES][NUM_OF_CHARS] = {{0}};

	for (i = 0; i < NUM_OF_CHARS; ++i)
	{
		for (j = 0; j < NUM_OF_CALC_STATES; ++j)
		{
			op_lut[j][i] = ErrorOp;
		}
	}

	op_lut[NULL_TERM]['+'] = Add;
	op_lut[NULL_TERM]['-'] = Sub;
	op_lut[NULL_TERM]['*'] = Mul;
	op_lut[NULL_TERM]['/'] = Div;
	op_lut[NULL_TERM]['^'] = Pow;
	op_lut[NULL_TERM]['('] = ParError;
	op_lut[NULL_TERM]['\0'] = ErrorOp;

	op_lut[PAREN_TERM]['+'] = Add;
	op_lut[PAREN_TERM]['-'] = Sub;
	op_lut[PAREN_TERM]['*'] = Mul;
	op_lut[PAREN_TERM]['/'] = Div;
	op_lut[PAREN_TERM]['^'] = Pow;
	op_lut[PAREN_TERM]['('] = DiscardPar;
	op_lut[PAREN_TERM][')'] = ParError;

	while ('(' != operator && (!StackIsEmpty(calc->stack[OPERATOR])) && CALC == state)
	{
		*result = 0;

		operator = *(char *) StackPeek(calc->stack[OPERATOR]);
		StackPop(calc->stack[OPERATOR]);
		state = op_lut[paren_stat][(int)operator](calc->stack[OPERAND], status, result);
	}

	if (1 == paren_stat && '(' != operator && (StackIsEmpty(calc->stack[OPERATOR])))
	{
		state = op_lut[NULL_TERM]['('](calc->stack[OPERAND], status, result); /*if ')' and no '('*/
	}

	++*expression;

	return state;
}

static void CalcClean(calc_t *calc)
{
	size_t i = 0;

	assert(NULL != calc);

	for (i = 0; i < NUM_OF_STACKS; ++i)
	{
		while (!StackIsEmpty(calc->stack[i]))
		{
			StackPop(calc->stack[i]);
		}
	}
}
