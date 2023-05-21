

#include "wd.h"
#include "sched.h"

int main(int argc, char *argv[])
{
    size_t threshold = 3;
    time_t interval = 5;
    
    MakeMeImmortal(argc, argv, threshold, interval);

    DoNotResuscitate();

    return 0;
}