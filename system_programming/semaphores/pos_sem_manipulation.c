

#include <fcntl.h>          /* For O_* constants */
#include <semaphore.h>      /* semaphore */     
#include <stdio.h>          /* printf, perror */
#include <errno.h>          /* errno */
#include <stdlib.h>         /* atoi, exit */
#include <string.h>         /* strtok */

#define MAX_INPUT (100)

int main()
{
	sem_t *sem = NULL;
	char size[MAX_INPUT] = {0};
	int init_val = 0;
	const char *name = "/sem1";
	int real_value = 0;
    int undo_value = 0;
	
	printf("enter init val:\n");
	fgets(size, MAX_INPUT, stdin);

	init_val = atoi(size);
	
	sem = sem_open(name, O_CREAT, 0777, 1);
	
	if (sem != SEM_FAILED && errno != EEXIST)
	{
		if (-1 == sem_init(sem, 0, init_val))
		{
			perror("");
			exit(1);
		}
	}
	
	while(1)
	{
		char command[MAX_INPUT] = {0};
		char *cmd_token[MAX_INPUT] = {0};
		char *token = NULL;
		size_t i = 0;
		int number = 0;
		int sem_val = 0;
				
		printf("enter command:\n");
		fgets(command, MAX_INPUT, stdin);
		
		token = strtok(command, " ");
		
		while(NULL != token)
		{
			cmd_token[i] = token;
			token = strtok(NULL, " ");
			++i;
		}
        
		switch (cmd_token[0][0])
		{
			case 'D':
			{
				number = atoi(cmd_token[1]);

                if (NULL != cmd_token[2] && (0 == strcmp(cmd_token[2], "undo\n")))
                {
                    real_value -= number;
                }	

				while (number)
				{
					sem_wait(sem);
					--number;
				}
				break;
			}
			
			case 'I':
			{
				number = atoi(cmd_token[1]);

                if (NULL != cmd_token[2] && (0 == strcmp(cmd_token[2], "undo\n")))
                {
                    real_value += number;
                }	

				while (number)
				{
					sem_post(sem);
					--number;
				}
				break;
			}
			
			case 'V':
			{
				sem_val = 0;
				sem_getvalue(sem, &sem_val);
				printf("current val is %d\n", sem_val);
				break;
			}
			
			case 'X':
			{
				sem_getvalue(sem, &sem_val);
                undo_value = real_value;

				if (0 != real_value)
				{
					while (0 > real_value)
					{
						sem_post(sem);
						++real_value;
					}
					while (0 < real_value)
					{
						sem_wait(sem);
						--real_value;
					}
				}
				sem_getvalue(sem, &sem_val);
				printf("undo value is %d, sem_val is %d\n", undo_value, sem_val);
				sem_unlink(name);
				return 0;
			}
			
			default:
			{
				printf("invalid command\n");
				break;
			}
		}	
	}
	
	return 0;
}


