/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Yotam S.			*
*	Date      : 07/05/2023			*
************************************/

#define _POSIX_SOURCE
#include <sys/types.h>	/* pid_t */
#include <unistd.h>		/* sleep */
#include <signal.h>		/* signals */
#include <stdlib.h>    	/* atoi */

#include "handler.c"

/******************* Static Functions **********************/


/******************* Main Function **********************/

int main(int argc, char *argv[])
{
	pid_t pid = atoi(argv[1]);

	(void)argc;

	signal(SIGUSR2, SigHandler);

	while(1)
	{
		sleep(1);
		kill(pid, SIGUSR1);
		signal(SIGUSR2, SigHandler);
		pause();
	}
	
	return 0;
}

