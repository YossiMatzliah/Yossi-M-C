/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	*****				*
*	Date      : 29/03/2023			*
************************************/

#ifndef __FSM_H__
#define __FSM_H__

typedef enum machine_state
{
	INITIALE_STATE = 0,
	MIDDLE = 1,
	ACCEPTED = 2,
	ERROR = 3,
	MAX_STATES = 4
}state_t;

/************************************/

state_t InputReader(char *input_str);

#endif
