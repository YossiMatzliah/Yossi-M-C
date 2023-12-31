/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Neviu   			*
*	Date      : 29/05/2023			*
************************************/

#define _POSIX_C_SOURCE 200112L /* remove problems, might be removed later */
#include <sys/types.h>	/* pid_t */
#include <unistd.h>		/* fork, exec */
#include <signal.h>		/* signals */
#include <pthread.h>    /* threads */
#include <semaphore.h>  /* semaphore */ 
#include <fcntl.h>      /* O_CREAT */
#include <stdatomic.h>  /* atomic */
#include <stdio.h>      /* printf */
#include <sys/wait.h>   /* wait */
#include <stdlib.h>     /* setenv, exit */
#include <string.h>     /* strcmp */
#include <assert.h>     /* assert */

#include "wd.h"

#define FAILURE (-1)
#define SUCCESS (0)

#define THRESHOLD_ENV ("THRESHOLD")
#define INTERVAL_ENV ("INTERVAL")
#define WD_PID_ENV ("WD_PID")
#define USER_EXECUTABLE_ENV ("USER_EXECUTABLE")

#define MAX_BUF_SIZE (11)

#ifndef NDEBUG
#define PRINT_DEBUG(...) (printf(__VA_ARGS__))
#else
#define PRINT_DEBUG(...)
#endif

/*****************************************************/

pid_t worker_pid = 0;

pthread_t client_thread = 0;
pthread_t wd_thread = 0;

sem_t *sema;
char *sem_name = "sem1";

atomic_size_t atomic_counter = 0;
atomic_size_t atomic_stop = 0;

sch_t *sched;

size_t threshold_g = 0;
time_t interval_g = 0;

/*****************************************************/

void Sig1Handler(int signum, siginfo_t *info, void *context);
void Sig2Handler(int signum, siginfo_t *info, void *context);

static void *CreateSchedNdTasks(void *args);
static int SendSignalTask(void *th_pid);
static int CheckSigCounterTask(void *args);

static void *WDRunSched(void *arguments);
static void *WorkerRunSched(void *arguments);
static int ResuscitateWD(void *arguments);

static void CleanUp();

/*****************************************************/

int MakeMeImmortal(int argc, char **argv, size_t threshold, time_t interval)
{
    unsigned int init_value = 0;

    struct sigaction sa1 = {0};
    struct sigaction sa2 = {0};
    
    char threshold_buffer[MAX_BUF_SIZE] = {0};
    char interval_buffer[MAX_BUF_SIZE] = {0};
    char wd_pid_buffer[MAX_BUF_SIZE] = {0};

    assert(NULL != argv);
    assert(0 < argc);

    (void)argc;

    sprintf(threshold_buffer, "%ld", threshold);
    sprintf(interval_buffer, "%ld", interval);
    if(0 != setenv(THRESHOLD_ENV, threshold_buffer, 1) ||
           0 != setenv(INTERVAL_ENV ,interval_buffer, 1)) 
    {
        perror("setenv err\n");
        return FAILURE;
    }

    threshold_g = threshold;
    interval_g = interval;

    sa1.sa_sigaction = Sig1Handler;
	sa2.sa_sigaction = Sig2Handler;

    if (FAILURE == sigaction(SIGUSR1, &sa1, NULL))
	{
		perror("sigaction error\n");
		return FAILURE;
	}

    if (FAILURE == sigaction(SIGUSR2, &sa2, NULL))
	{
		perror("sigaction error\n");
		return FAILURE;
	}

    sema = sem_open(sem_name, O_CREAT, 0666, init_value);
    if(SEM_FAILED == sema)
    {
        perror("sem: ");
        return FAILURE; 
    }

    atomic_stop = 0;

    sched = (sch_t *)CreateSchedNdTasks(argv);
    PRINT_DEBUG("\n%s\n", argv[0]);
    if (0 != strcmp("./wd.out", argv[0]))  /* first time, enters, afterward only if not WD */
    {
        if(0 != setenv("USER_EXECUTABLE", argv[0], 1))
        {
            perror("setenv err\n");
            return FAILURE;        
        }
        PRINT_DEBUG("\n%s\n", argv[0]);
        worker_pid = fork();
        
        if (FAILURE == worker_pid)
        {
            perror("fork FAILURE!\n");
            return FAILURE;
        }

        else if (0 == worker_pid)	/* WD */
        {	  
            sprintf(wd_pid_buffer, "%d", getpid());
            if(0 != setenv("WD_PID", wd_pid_buffer, 1))
            {
                perror("setenv err\n");
                return FAILURE;        
            }

            PRINT_DEBUG("wd_pid = %d\n exec wd.out!\n", getpid());
            execvp("./bin/wd.out", argv);
            PRINT_DEBUG("\n%s\n\n", argv[0]);

            return SUCCESS;
        }
        else	/* client */
        {
            sprintf(wd_pid_buffer, "%d", worker_pid);
            if(0 != setenv("WD_PID", wd_pid_buffer, 1))
            {
                perror("setenv err\n");
                return FAILURE;        
            }

            PRINT_DEBUG("arg[0] = %s\n", argv[0]);
            PRINT_DEBUG("In USER - PID is: %d\n", getpid());

            PRINT_DEBUG("Start client thread worker\n");
            if (0 != pthread_create(&client_thread, NULL, WorkerRunSched, argv))
            {
                perror("pthread_create FAILURE!\n");
                DoNotResuscitate();

                return FAILURE;
            }
        }
    }
    else /* WD */
    {
        sem_post(sema);
        PRINT_DEBUG("run WD sched\n");
        WDRunSched(argv);

        PRINT_DEBUG("sched destroy\n");
        SchDestroy(sched);
    }
    
    return SUCCESS;
}

void DoNotResuscitate()
{
    pid_t wd_pid = atoi(getenv("WD_PID"));

    PRINT_DEBUG("Entered DoNotResuscitate\n");
    
    kill(wd_pid, SIGUSR2);
    raise(SIGUSR2);

    pthread_join(client_thread, NULL);
    wait(NULL);

    CleanUp();
}

/***************************************************************************/

void Sig1Handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
    (void)info;
    (void)signum;

    PRINT_DEBUG("entered sigusr1\n\n");
    PRINT_DEBUG("HandlerSIGUSR1\n   handler PID to signal is: %d\n", getpid());
	
    atomic_counter = 0;
}

void Sig2Handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
    (void)info;
    (void)signum;

    PRINT_DEBUG("\nHandlerSIGUSR2\n"); 

    ++atomic_stop;
}

static void *CreateSchedNdTasks(void *args)
{
    sch_t *sched = SchCreate();
    uid_t uid_task1 = {0};
    uid_t uid_task2 = {0};

    if (NULL == sched)
    {
        perror("SchdCreate Failed\n");
        return NULL;
    }

    PRINT_DEBUG("Sched created\n\n");

    uid_task1 = SchAddTask(sched, SendSignalTask, args, time(NULL), interval_g);
    uid_task2 = SchAddTask(sched, CheckSigCounterTask, args, time(NULL), interval_g);

    if(UIDIsSame(uid_task1, UIDGetBad()) || UIDIsSame(uid_task2, UIDGetBad()))
	{
        SchDestroy(sched);

		return NULL;
	}

    return sched;
}

static int SendSignalTask(void *th_pid)
{
    (void)th_pid;

    PRINT_DEBUG("   task PID to signal is: %d\n", getpid());
    PRINT_DEBUG("counter = %ld\n", atomic_counter);

        PRINT_DEBUG("atomic_stop = %ld\n", atomic_stop);
        if (0 == worker_pid)
        {
            PRINT_DEBUG("send SIGUSR1 to pid %d\n", getppid());
            kill(getppid(), SIGUSR1);
        }
        else
        {
            PRINT_DEBUG("send SIGUSR1 to pid %d\n", worker_pid);
            kill(worker_pid, SIGUSR1);
        }
        ++atomic_counter;
        PRINT_DEBUG("counter = %ld\n", atomic_counter);


    return SUCCESS;
}

static int CheckSigCounterTask(void *args)
{
    int wd_pid = atoi(getenv("WD_PID"));

    (void)args;

    if (0 != atomic_stop)
    {
        return FAILURE;
    }

    PRINT_DEBUG("counter = %ld", atomic_counter);
    if (atomic_counter >= threshold_g)
    {
        atomic_counter = 0;

        if (getpid() != wd_pid)
        {    
            if (FAILURE == ResuscitateWD(args))
            {
                return FAILURE;
            }
        }
        else
        {
            return FAILURE;
        }       
    }

    return SUCCESS;
}

static void *WDRunSched(void *arguments)
{
    char **args = (char **)arguments;

    PRINT_DEBUG("In RunSched\n");

    if (SUCCESS != SchRun(sched) && 0 == atomic_stop)
    {
        /* stop, and revive the dead/stucked process */
    
        /* Survivor is WD: */
        args[0] = getenv("USER_EXECUTABLE");

        SchDestroy(sched);
        PRINT_DEBUG("check \t%s\n", args[0]);

        if (-1 == sem_unlink(sem_name))
        {
            perror("Error unlinking named semaphore");
            return NULL;
        }

        if (-1 == execvp(args[0], args))
        {
            perror("execvp FAILURE!\n");
        }
    }

    return NULL;
}

static void *WorkerRunSched(void * arguments)   /* client_thread */
{
    (void)arguments;
    sem_wait(sema);
    SchRun(sched);

    return NULL;
}

static int ResuscitateWD(void * arguments)  /* client_thread */
{
    char wd_pid_buffer[MAX_BUF_SIZE];

    /* Survivor is USER: */
    wait(NULL);

    worker_pid = fork();
    if (-1 == worker_pid)
    { 
        perror("fork FAILURE!\n");
        return FAILURE;
    }
    else if (0 == worker_pid)    /* child */
    {
        sprintf(wd_pid_buffer, "%d", getpid());
        if(0 != setenv("WD_PID", wd_pid_buffer, 1))
        {
            perror("setenv err\n");
            return FAILURE;        
        }
        
        PRINT_DEBUG("INSIDE NEW WD, doing execvp\n");
        if (-1 == execvp("./bin/wd.out", arguments))
        {
            perror("execvp FAILURE!");
        }
    }
    else    /* Parent */
    {
        sprintf(wd_pid_buffer, "%d", worker_pid);
        if(0 != setenv("WD_PID", wd_pid_buffer, 1))
        {
            perror("setenv err\n");
            return FAILURE;        
        }
        PRINT_DEBUG("INSIDE Client sem_wait and run sched \n");
        
        sem_wait(sema);
    }

    return SUCCESS;
}
    
static void CleanUp()
{
    sem_close(sema);
    sem_unlink(sem_name);
    
    unsetenv("THRESHOLD");
    unsetenv("INTERVAL");
    unsetenv("WD_PID");
    unsetenv("USER_EXECUTABLE");

    SchDestroy(sched);
}
