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

/******************* Static Functions **********************/

void SigHandler(int signum);

/******************* Main Function **********************/

int main(/*int argc, char *argv[]*/)
{
	pid_t child_pid;
	pid_t ppid;
	
	signal(SIGUSR1, SigHandler);
	signal(SIGUSR2, SigHandler);

	child_pid = fork();
	
	if (-1 == child_pid)
	{
		perror("Failure!\n");
		return 1;
	}

	if (0 == child_pid)	/* child */
	{	
		ppid = getppid();

		while(1)
        {
			sleep(1);
            kill(ppid, SIGUSR2);
			signal(SIGUSR1, SigHandler);
			pause();
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

		/*wait(NULL);*/
	}

	return 0;
}

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
