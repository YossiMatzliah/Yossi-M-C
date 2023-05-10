#include <stdio.h>   /* printf */
#include <stddef.h>  /* size_t */
#include <omp.h>    /* MP */


#define NUMBER_TO_CALCULATE_DIVISORS (5915587277)


int main()
{
    size_t i = 0;
    size_t low_range = 1;
    size_t high_range = NUMBER_TO_CALCULATE_DIVISORS;
    size_t sum_of_divisors = 0;

    #pragma omp parallel for 
    for (i = 1; i <= NUMBER_TO_CALCULATE_DIVISORS; ++i)
    {
        if (0 == NUMBER_TO_CALCULATE_DIVISORS % i)
        {
            sum_of_divisors += i;
        }
    }

    printf("sum_of_divisors = %ld\n", sum_of_divisors);

    return 0;
}
