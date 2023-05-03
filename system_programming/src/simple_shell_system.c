/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	????				*
*	Date      : ?/05/2023			*
************************************/

#include <stdio.h>		/* printf */
#include <stdlib.h>		/* malloc */
#include <sys/types.h>	/* pid_t */
#include <unistd.h>    	/* execvp */
#include <string.h>    	/* strncmp */
#include <sys/wait.h>	/* wait */

#define MAX_INPUT (64)

/***************************** Static Functions ***********************************/

static void GetLine(char *prompt, char *input);

/***************************** Main Function ***********************************/

int main()
{
	char *prompt = "sys@shell: $ ";
   
    char input[MAX_INPUT] = {0};
    
    GetLine(prompt, input);

    while (0 != strncmp(input, "exit", 4))
    {
        if (-1 == system(input))
        {
              perror("Failure - Could not create process\n");
              break;
        }

        GetLine(prompt, input);
    }
    
    return 0;
}

/****************** Static Functions *****************/

void GetLine(char *prompt, char *input)
{
    printf("\t%s ", prompt);
    fgets(input, MAX_INPUT, stdin);
}
