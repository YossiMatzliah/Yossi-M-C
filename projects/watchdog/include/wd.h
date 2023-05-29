/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Neviu   			*
*	Date      : 29/05/2023			*
************************************/

#ifndef __ILRD_OL139_40_WD_H__
#define __ILRD_OL139_40_WD_H__

#include <stddef.h> /* size_t */

/*****************************************/

/*
    wd.out can not be changed. changing would cause an undefined behaviour!.
*/

/*****************************************/

/*
* MakeMeImmortal Description:
*	Creates a "Watchdog" process. Makes a part of code "immortal", checks in intervals if the process is a live, 
*	if doesn't gets a signal of life, terminated and starts over.
*				 											
* @params:
*   argc - argc passed to calling process.
*   argv - array of argv[] passed to calling process.
*	threshold - How many times is allowed not to get a signal before termination and reset. (max of 11 digits)
*   interval - The interval between two signals. (max of 11 digits)
*
* @returns:
*	0 on success, in case of allocc failure returns a non-zero value.
*
* @Complexity
*	Time: O(n)
*   Space O(1)
*/
int MakeMeImmortal(int argc, char **argv, size_t threshold, time_t interval);

/*
* DoNotResuscitate Description:
*   Terminates the "Watchdog" process in an orderly manner (cleanup is done at the end).
*       NOTE: After calling this function use wait for cleanup.
*
* @params:
*   none
*
* @returns:
*	none.
*
* @Complexity
*    Time: O(n)
*    Space O(1)
*/
void DoNotResuscitate();

#endif