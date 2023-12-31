/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Lilach 	  			*
*	Date      : 02/03/2023			*
************************************/

#ifndef __ILRD_OL139_40_UID_H__
#define __ILRD_OL139_40_UID_H__

#include <sys/types.h> 	/* getpid, size_t */
#include <time.h> 		/* time_t */

#define LINUX_IP_SIZE (14)

/* UID is a struct used for attaching a unique identifier to objects. struct uid stay in .h */
struct uid
{
    time_t time_stamp;
    size_t counter;
    pid_t pid;
    unsigned char ip[LINUX_IP_SIZE];
};

typedef struct uid uid_t;

/**************************************************/

/*
* UIDCreate Description:
*	Creates a new UID. 
*
* @params:
*   None
*
* @returns:
*	uid_t struct
*
* @Complexity
*	O(1)
*/
uid_t UIDCreate(void); 

/*
* UIDIsSame Description:
*	Checks if two UIDs are the same.
*
* @params:
*   lhs, rhs - UIDs
*
* @returns:
*	1 if two UIDs are the same, 0 if not.
*
* @Complexity
*	O(1)
*/
int UIDIsSame(uid_t lhs, uid_t rhs); 

/*
* UIDGetBad Description:
*	Returns a UID with invalid fields.
*   This UID is used to represent a state of error.
*
* @params:
*   None.
*
* @returns:
*	UID.
*
* @Complexity
*	O(1)
*/
uid_t UIDGetBad(void);

#endif

