
#include <sys/types.h>	/* pid_t */
#include <unistd.h>		/* fork, exec */
#include <signal.h>		/* signals */
#include <pthread.h>    /* threads */

#include "wd.h"


/*****************************************************/



/*****************************************************/

int MakeMeImmortal(int argc, char **argv, size_t threshold, time_t interval)
{
    pid_t wd_pid;
    pthread_t wd_thread = 0;

    (void)argc;

    /*signal handler init*/

    wd_pid = fork();
	
	if (-1 == wd_pid)
	{
		perror("Failure!\n");
		return 1;
	}

	if (0 == wd_pid)	/* wd */
	{	  
        execvp("./wd.out", argv);
	}
	else	/* user */
	{
		pthread_create(&wd_thread, NULL, MakeMeImmortal, NULL);
	}

    pthread_join(wd_thread, NULL);
}

void DoNotResuscitate()
{

}


