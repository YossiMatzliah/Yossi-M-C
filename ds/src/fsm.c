/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	*****				*
*	Date      : 29/03/2023			*
************************************/

#include <assert.h>	/* assert */
#include <stddef.h>	/* NULL */

#include "fsm.h"

typedef enum machine_events
{
	ZERO_INSERTED = 0,
	ONE_INSERTED = 1,
	MAX_EVENTS = 2
}event_t;

/************************************/

int states_lut[MAX_STATES][MAX_EVENTS] = {	{MIDDLE, ERROR},
											{ACCEPTED, MIDDLE},	
											{ACCEPTED, MIDDLE},
											{ERROR, ERROR}
					 					 };

state_t InputReader(char *input_str)
{
	state_t state = INITIALE_STATE;
	
	assert(NULL != input_str);
	
	while ('\0' != *input_str && ERROR != state)
	{
		state = states_lut[state][(int)(*input_str - '0')];
		++input_str;
	}
	
	return state;
}





