/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Lilach 	  			*
*	Date      : 05/03/2023			*
************************************/
#ifndef __ILRD_139_40__TASK_H__
#define __ILRD_139_40__TASK_H__

#include "uid.h"			/* ilrd_uid_t */

typedef struct task task_t;
typedef int (*op_func_t)(void *);

/******************************************************************/

/*
* TaskCreate Description:
*	Creates a new task structure and adds Unique ID.	
*
* @params:
*	op_func - Pointer to a operation function.
*	param - User's parameter to be executed with op_func.
*	exec_time - Time of execution in time_t format.
*	interval - In seconds, when to repeat task.
*			Note - interval 0, will execute the task only ones.    	
*
* @returns:
*	Pointer to task. If error occured - returns null. 
*
* @Complexity
*	O(1)
*/
task_t *TaskCreate(int (*op_func)(void *), void *params, time_t exec_time , time_t interval);

/*
* TaksDestroy Description:
* 	Deallocates a given task from memory.
* 
* @params:
*	task - Pointer to task to be freed from memory.
*		If the pointer is invalid - behavior is undefined.
*
* @returns:
*	None
*
* @Complexity
*	O(1)
*/
void TaskDestroy(task_t *task);

/*
* TaksRunTask Description:
* 	Execute the proccess of the task.
* 
* @params:
*	task - Pointer to the task containing operation func to execute.
*		If the pointer is invalid - behavior is undefined.
*
* @returns:
*	Returns task's operation function status.
*		0 - Success, Any other integer means Failure.
*
* @Complexity
*	O(1)
*/
int TaskRunTask(task_t *task);

/*
* TaskGetExecTime Description:
* 	Get the time to execute in time_t format.
* 
* @params:
*	task - Pointer to the task containing time to execute.
* 		If the pointer is invalid - behavior is undefined.
*
* @returns:
*	Returns the time to execute the task in time_t format.
*
* @Complexity
*	O(1)
*/
time_t TaskGetExecTime(task_t *task);

/*
* TaskGetInterval Description:
* 	Get the time interval to the next execute in time_t format.
* 
* @params:
*	task - Pointer to the task containing interval time to execute.
*		If the pointer is invalid - behavior is undefined.
*
* @returns:
*	Returns task's interval time to execute in time_t format.
*
* @Complexity
*	O(1)
*/
time_t TaskGetInterval(task_t *task);

/*
* TaskGetUID Description:
*	Get the task's uid.
* 
* @params:
*	task - Pointer to the task containing uid.
*		If the pointer is invalid - behavior is undefined.
*
* @returns:
*	Returns task's uis int ilrd_uid_t format.
*
* @Complexity
*	O(1)
*/
ilrd_uid_t TaskGetUID(task_t *task);

/*
* TaskGetFunc Description:
* 	Get the task's pointer to function.
* 
* @params:
*	task - Pointer to the task containing pointer to function.
* 		If the pointer is invalid - behavior is undefined.
*
* @returns:
*	Returns task's function pointer in int (*op_func)(void *) format.
*
* @Complexity
*	O(1)
*/
op_func_t TaskGetFunc(task_t *task);

/*
* TaskGetParams Description:
* 	Get the task's pointer to function's parameters.
* 
* @params:
*	task - Pointer to the task containing parameters.
* 		If the pointer is invalid - behavior is undefined.
*
* @returns:
*	Returns task's function parameters in 'void *' format.
*
* @Complexity
*	O(1)
*/
void *TaskGetParams(task_t *task);

/*
* TaskSetExecTime Description:
* 	Change the execution time of a given task.
* 
* @params:
*	task - Pointer to the wanted task to change. 
* 		If the pointer is invalid - behavior is undefined.
*	exec_time - New execution value for the task in time_t format
*
* @returns:
*	NONE
*
* @Complexity
*	O(1)
*/
void TaskSetExecTime(task_t *task, time_t exec_time);


/*
* TaskSetInterval Description:
* 	Change the interval time of a given task.
* 
* @params:
*	task - Pointer to the wanted task to change 
* 		If the pointer is invalid - behavior is undefined.
*	interval - New interval value for the task in time_t format
*
* @returns:
*	NONE
*
* @Complexity
*	O(1)
*/
void TaskSetInterval(task_t *task, time_t interval);

/*
* TaskSetFunc Description:
* 	Change the function pointer of a given task.
* 
* @params:
*	task - Pointer to the wanted task to change 
* 		If the pointer is invalid - behavior is undefined.
*	op_func - Pointer to a new operation function for the task.
*
* @returns:
*	NONE
*
* @Complexity
*	O(1)
*/
void TaskSetFunc(task_t *task, int (*op_func)(void *));

/*
* TaskSetParams Description:
* 	Change the parameters to function of a given task.
* 
* @params:
*	task - Pointer to the wanted task to change. 
* 		If the pointer is invalid - behavior is undefined.
*	params - New parameters for the task operation function in 'void *' format.
*
* @returns:
*	NONE
*
* @Complexity
*	O(1)
*/
void TaskSetParams(task_t *task, void *params);

#endif
