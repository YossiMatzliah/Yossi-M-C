#ifndef __ILRD_OL139_40_WD_H__
#define __ILRD_OL139_40_WD_H__

#include <stddef.h> /* size_t */


/*****************************************/

/*
* MakeMeImmortal Description:
*	
*	
*		
*				 											
* @params:
*	threshold - How many times is allowed not to get a signal before termination and reset.
*   interval - The interval between two signal to be sent.
*
* @returns:
*	allocc failure
*
* @Complexity
*	O()
*/
int MakeMeImmortal(int argc, char **argv, size_t threshold, time_t interval);

/*
* DoNotResuscitate Description:
*	
*	
*		
*				 											
* @params:
*	
*
* @returns:
*	
*
* @Complexity
*	O()
*/
void DoNotResuscitate();

#endif