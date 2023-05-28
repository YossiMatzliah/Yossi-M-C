#ifndef __ILRD_OL139_40_WD_H__
#define __ILRD_OL139_40_WD_H__

#include <stddef.h> /* size_t */


/*****************************************/

/*
    wd.out can not be changed. changing would cause an undefined behaviour
*/


/*
* MakeMeImmortal Description:
*	Makes a part of code immortal, checks in intervals if the process is a live, 
*	if doesn't gets a signal of life, terminated and starts over.
*				 											
* @params:
*	threshold - How many times is allowed not to get a signal before termination and reset.
*   interval - The interval between two signals.
*
* @returns:
*	0 on success, in case of allocc failure returns a non-zero.
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