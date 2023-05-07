/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	????				*
*	Date      : ?/05/2023			*
************************************/

/*#define _POSIX_SOURCE*/
#include <stdio.h>		/* printf */
#include <signal.h>		/* signals */

/******************* Static Functions **********************/

void SigHandler(int signum);

/******************* Main Function **********************/

void SigHandler(int signum)
{
	if (SIGUSR1 == signum)
    {
        printf("ping -> \n");
    }

	if (SIGUSR2 == signum)
    {
        printf("<- pong \n");
    }
}
