#include <stdio.h>      /* printf */
#include <time.h>       /* time.h */
#include <unistd.h>     /* sleep */
#include <sys/wait.h>   /* wait */

#include "wd.h"

#define TIME_TO_SLEEP (20)

int main(int argc, char *argv[])
{
    size_t threshold = 3;
    time_t interval = 3;
    size_t i = 0;
    
    MakeMeImmortal(argc, argv, threshold, interval);

    printf("user process still running\n");
    sleep(20);
    printf("user process still running\n");
    for (i = 0; i < TIME_TO_SLEEP; ++i)
    {
        printf("DoNotResuscitate in %ld secends\n", TIME_TO_SLEEP - i);
        sleep(1);
    }

    DoNotResuscitate();

    wait(NULL);

    return 0;
}