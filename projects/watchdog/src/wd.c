/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Neviu   			*
*	Date      : 29/05/2023			*
************************************/

#include <stdio.h>          /* printf */
#include <time.h>           /* time_t */
#include <stdlib.h>         /* getenv */
#include <unistd.h>         /* getpid() */

#include "wd.h"

/*****************************************************/

int main(int argc, char *argv[])
{
    size_t threshold = atoi(getenv("THRESHOLD"));
    time_t interval = atoi(getenv("INTERVAL"));
    
    argv[0] = "./wd.out";

    printf("In WD - PID is: %d\n", getpid());

    printf("\n%s\n\n", argv[0]);
    MakeMeImmortal(argc, argv, threshold, interval);

    printf("returned in WD\n");

    return 0;
}
