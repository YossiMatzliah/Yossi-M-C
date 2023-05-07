/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Noam				*
*	Date      : 03/05/2023			*
************************************/

#include <stdio.h>		/* perror */
#include <sys/types.h>	/* pid_t */
#include <unistd.h>		/* execvp */
#include <string.h>		/* strcmp */
#include <sys/wait.h>	/* wait */

#define MAX_INPUT (64)

/******************* Main Function **********************/

int main(int argc, char *argv[])
{
	pid_t child_pid;
	char *fork_input = "fork";
	char *system_input = "system";
	(void)argc;

	child_pid = fork();
	
	if (-1 == child_pid)
	{
		perror("Failure!\n");
		return 1;
	}

	if (0 == child_pid)
	{
		if (0 == strcmp(argv[1], fork_input))
		{
			execvp("./fork.out", argv);
		}
		else if (0 == strcmp(argv[1], system_input))
		{
			execvp("./sys.out", argv);
		}
	}
	else
	{
		wait(NULL);
	}

	return 0;
}
