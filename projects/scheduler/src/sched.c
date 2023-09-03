/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Lilach 	  			*
*	Date      : 05/03/2023			*
************************************/

#include <stdlib.h>		/* malloc, free */
#include <assert.h>		/* assert 		*/
#include <stdio.h>		/* perror 		*/
#include <unistd.h>		/* sleep 		*/

#include "../include/pq.h"	
#include "../include/uid.h"				
#include "../include/task.h"			
#include "../include/sched.h"

#define FAILURE (1)
#define SUCCESS (0)
#define RUN 	(0)
#define STOP	(1)

struct scheduler
{
	pq_t *tasks;
	int stop;
};

/****************** static functions *******************/

static int PriorityFunc(const void *data1, const void *data2);

static int MatchFunc(const void *data1, const void *data2);

/****************** sched functions *****************/

sch_t *SchCreate(void)
{
	sch_t *new_sch = (sch_t *)malloc(sizeof(sch_t));
	
	if (NULL == new_sch)
	{
		perror("Allocation failed\n");
		
		return NULL;
	}
	
	new_sch->tasks = PQCreate(PriorityFunc);
	
	if(NULL == new_sch->tasks)
	{
		free(new_sch);
		
		return NULL;
	}
	
	new_sch->stop = RUN;
	
	return new_sch;
}

void SchDestroy(sch_t *scheduler)
{
	assert(NULL != scheduler);
	assert(NULL != scheduler->tasks);
	
	SchClear(scheduler);
	
	PQDestroy(scheduler->tasks);
	
	free(scheduler);
}

uid_t SchAddTask(sch_t *scheduler ,int (*op_func)(void *), void *params, time_t exec_time , time_t interval)
{
	task_t *new_task = NULL;
	
	assert(NULL != scheduler);
	assert(NULL != scheduler->tasks);
	assert(NULL != op_func);
	
	new_task = TaskCreate(op_func, params, exec_time, interval);
	
	if (NULL == new_task)
	{
		return UIDGetBad();
	}
	
	if (PQEnqueue(scheduler->tasks, (void *)new_task))
	{
		return UIDGetBad();
	}
	
	return TaskGetUID(new_task);
}

void SchRemoveTask(sch_t *scheduler ,uid_t task_uid)
{
	task_t *to_destroy = NULL;
	
	assert(NULL != scheduler);
	assert(NULL != scheduler->tasks);
	
	to_destroy = (task_t *)PQErase(scheduler->tasks, MatchFunc, &task_uid);
	
	if (NULL != to_destroy)
	{
		TaskDestroy(to_destroy);
	}
}

int SchIsEmpty(const sch_t *scheduler)
{
	assert(NULL != scheduler);
	assert(NULL != scheduler->tasks);
	
	return PQIsEmpty(scheduler->tasks);
}
	
size_t SchSize(const sch_t *scheduler)
{
	assert(NULL != scheduler);
	assert(NULL != scheduler->tasks);
	
	return PQSize(scheduler->tasks);
}
	
int SchRun(sch_t *scheduler)
{
	int status = SUCCESS;
	int time_to_sleep = 0;
	
	task_t *task = NULL;
	time_t curr_interval = 0;
	
	assert(NULL != scheduler);
	assert(NULL != scheduler->tasks);
	
	scheduler->stop = RUN;
	
	while (RUN == scheduler->stop && SUCCESS == status && !SchIsEmpty(scheduler))
	{
		task = (task_t *)PQPeek(scheduler->tasks);
		time_to_sleep = TaskGetExecTime(task) - time(NULL);
		
		if (0 < time_to_sleep)
		{
			sleep(time_to_sleep);
		}
		
		status = TaskRunTask(task);
		
		PQDequeue(scheduler->tasks);
		
		curr_interval = TaskGetInterval(task);
		if (0 != curr_interval)
		{
			TaskSetExecTime(task, TaskGetExecTime(task) + curr_interval);
			
			if (PQEnqueue(scheduler->tasks, (void *)task))
			{
				status = FAILURE;
			}
		}
		else
		{
			TaskDestroy(task);
		}
	}
	
	return status;
}

void SchStop(sch_t *scheduler)
{
	assert(NULL != scheduler);
	assert(NULL != scheduler->tasks);
	
	scheduler->stop = STOP;
}

void SchClear(sch_t *scheduler)
{
	assert(NULL != scheduler);
	assert(NULL != scheduler->tasks);
	
	while (!PQIsEmpty(scheduler->tasks))
	{
		TaskDestroy(PQPeek(scheduler->tasks));
		PQDequeue(scheduler->tasks);
	}
}

/****************** static functions *******************/

static int PriorityFunc(const void *data1, const void *data2)
{
	return (int)difftime(TaskGetExecTime((task_t *)data1), TaskGetExecTime((task_t *)data2));
}

static int MatchFunc(const void *data1, const void *data2)
{
	return UIDIsSame(TaskGetUID((task_t *)data1), *(uid_t *)data2);
}

