/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	????				*
*	Date      : ?/05/2023			*
************************************/

#define _POSIX_SOURCE
#include <stdio.h>		/* perror */
#include <sys/types.h>	/* pid_t */
#include <unistd.h>		/* fork, getppid */
#include <sys/wait.h>	/* wait */
#include <signal.h>		/* signals */
#include <string.h>    	/* strcmp */

#include "handler.c"

/******************* Static Functions **********************/


/******************* Main Function **********************/

int main(int argc, char *argv[])
{
	pid_t child_pid;
	char *exec_exe = "pong";
	(void)argc;
	
	signal(SIGUSR1, SigHandler);
	
	child_pid = fork();
	
	if (-1 == child_pid)
	{
		perror("Failure!\n");
		return 1;
	}

	if (0 == child_pid)	/* child */
	{	
		if (0 == strcmp(argv[1], exec_exe))
		{
			execvp("./pong.out", argv);
		}
	}
	else	/* parent */
	{
		while(1)
        {
			sleep(1);
            kill(child_pid, SIGUSR1);  
			signal(SIGUSR2, SigHandler);
            pause();
        }
	}

	return 0;
}



