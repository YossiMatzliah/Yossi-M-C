/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Yotam S.			*
*	Date      : 07/05/2023			*
************************************/
#define _XOPEN_SOURCE 700
#define _POSIX_SOURCE
#include <stdio.h>		/* printf */
#include <unistd.h>		/* sleep */
#include <signal.h>		/* signals */
	
#include "handler.c"

/* compile with flag: -D_POSIX_C_SOURCE=199309L */

/******************* Static Functions **********************/

void PingHandler(int signum, siginfo_t *info, void *context);

/******************* Main Function **********************/

int main()
{
	struct sigaction sa = {0};
	sa.sa_sigaction = PingHandler;
    sa.sa_flags = SA_SIGINFO;

	if (-1 == sigaction(SIGUSR1, &sa, NULL))
	{
		perror("Failure!\n");
		return 1;
	}

	while(1)
	{
		sleep(1);
		pause();
	}

	return 0;
}

void PingHandler(int signum, siginfo_t *info, void *context)
{
	(void)context;

	if (SIGUSR1 == signum)
	{
		printf("Ping -> \n");
		kill(info->si_pid, SIGUSR2);
	}
}

