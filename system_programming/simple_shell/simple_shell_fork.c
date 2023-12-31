/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Noam				*
*	Date      : 03/05/2023			*
************************************/

#include <stdio.h>		/* printf */
#include <stdlib.h>		/* malloc */
#include <sys/types.h>	/* pid_t */
#include <unistd.h>    	/* execvp */
#include <string.h>    	/* strcmp */
#include <sys/wait.h>	/* wait */

#define MAX_INPUT (64)
#define SUCCESS (0)
#define FAILURE (-1)

/***************************** Static Functions ***********************************/

static int SplitWords(char *input, char *args[]);
static void FreeArgs(char *args[]);

/***************************** Main Function ***********************************/

int main()
{
	char *prompt = "fork@shell: $ ";

    while (1)
    {
        pid_t child_pid = 0;
        char input[MAX_INPUT] = {0};
        char *args[MAX_INPUT] = {0};
        
        printf("\t%s ", prompt);
        fgets(input, MAX_INPUT, stdin);

        if (FAILURE == SplitWords(input, args))
        {
            return FAILURE;
        }
        
        if (0 == strcmp(args[0], "exit"))
        {
            break;
        }
        
        child_pid = fork();
        
        if (-1 == child_pid)
        {
              perror("Failure - Could not create process\n");
              break;
        }
        
        if (0 == child_pid)
        {
            execvp(args[0], (args));
        }
        else
        {
            wait(NULL);
        }

        FreeArgs(args);
    }
    
    return 0;
}

static int SplitWords(char *input, char *args[])
{
    size_t index = 0;
    char *token = strtok(input, " \n");
    size_t len = 0;
    
    while (NULL != token)
    {
        len = strlen(token) + 1;
        args[index] = malloc(len);
        if (NULL == args)
        {
            perror("Allocation err\n");
            return FAILURE;
        }
        strcpy(args[index], token);
        ++index; 
        token = strtok(NULL, " \n");
    }
    args[index] = NULL;

    return SUCCESS;
}

static void FreeArgs(char *args[])
{
    size_t i = 0;

    for (i = 0; i < MAX_INPUT; ++i)
    {
        free(args[i]);
    }
}