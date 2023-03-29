/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	*****				*
*	Date      : 29/03/2023			*
************************************/

#ifndef __ILRD_139_40__FSM_H__
#define __ILRD_139_40__FSM_H__

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
