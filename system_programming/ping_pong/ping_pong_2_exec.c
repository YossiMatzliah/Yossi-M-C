/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Yotam S.			*
*	Date      : 07/05/2023			*
************************************/

#define _POSIX_SOURCE
#include <stdio.h>		/* printf */
#include <stdlib.h>		/* malloc */
#include <sys/types.h>	/* pid_t */
#include <unistd.h>    	/* execvp */
#include <string.h>    	/* strcmp */
#include <sys/wait.h>	/* wait */
#include <signal.h>		/* signals */

#include "handler.c"


/***************************** Static Functions ***********************************/


/***************************** Main Function ***********************************/

int main()
{
    signal(SIGUSR2, SigHandler); 
    signal(SIGUSR1, SigHandler);

    while (1)
    {
        pid_t ppid = getppid();
        
        sleep(1);
        kill(ppid, SIGUSR2);  
        signal(SIGUSR1, SigHandler);
        pause();
    }
    
    return 0;
}



