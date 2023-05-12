

#include <semaphore.h>      /* semaphore */     
#include <stdio.h>          /* printf, perror */
#include <errno.h>          /* errno */
#include <stdlib.h>         /* atoi, exit */
#include <string.h>         /* strtok */
#include <sys/sem.h>        /* System V */
#include <sys/ipc.h>        /* IPC */

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
} ;

#define MAX_INPUT   (100)
/* #define SET_SIZE    (1) */

int main()
{
    /* union semun arguments = {0};
    unsigned short value[SET_SIZE] = {0}; */
    key_t key = 0;
	int sem_id = 0;
	int nsems = 1;
    struct sembuf operation = {0};
	

    key = ftok("/home/yossi/git/system_programming/semaphores/key.text", 'a');
    sem_id = semget(key, nsems, 0666 | IPC_CREAT);

	if (-1 == sem_id)
	{
		perror("");
		return 1;
	}
	
    semctl(sem_id, 0, GETVAL, 0);

	while(1)
	{
		char command[MAX_INPUT] = {0};
		char *cmd_token[MAX_INPUT] = {0};
		char *token;
		size_t i = 0;
		int number = 0;
		int sem_val = 0;
        /* int idx = 0; */
		operation.sem_flg = IPC_NOWAIT;

		printf("enter command:\n");
		fgets(command, MAX_INPUT, stdin);
		
		token = strtok(command, " ");
		while(NULL != token)
		{
			cmd_token[i] = token;
			token = strtok(NULL, " ");
			++i;
		}

        /* for (idx = 0; idx < SET_SIZE; ++idx)
        {
            value[idx] = 1;
        }

        arguments.array = value; */
		
		if (NULL != cmd_token[2] && 0 == strcmp(cmd_token[2], "undo\n"))
		{
			operation.sem_flg = SEM_UNDO;
		}
		
		switch (cmd_token[0][0])
		{
			case 'D':
			{
				number = atoi(cmd_token[1]);
				operation.sem_op = -number;
				semop(sem_id, &operation, 1);
				break;
			}
			
			case 'I':
			{
				number = atoi(cmd_token[1]);
				operation.sem_op = number;
				semop(sem_id, &operation, 1);
				break;
			}
			
			case 'V':
			{
				sem_val = semctl(sem_id, 0, GETVAL);
				printf("current val is %d\n", sem_val);
				break;
			}
			
			case 'X':
			{
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
