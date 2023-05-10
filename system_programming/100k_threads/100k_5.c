#include <stdio.h>   /* printf */
#include <stddef.h>  /* size_t */
#include <stdlib.h>  /* exit */

#define NUMBER_TO_CALCULATE_DIVISORS (5915587277)

int main()
{
    size_t i = 0;
    size_t low_range = 1;
    size_t high_range = NUMBER_TO_CALCULATE_DIVISORS;
    size_t sum_of_divisors = 0;

    for (i = low_range; i <= high_range; ++i)
    {
        if (0 == NUMBER_TO_CALCULATE_DIVISORS % i)
        {
            sum_of_divisors += i;
            printf("%ld\t", i);
        }
    }

    printf("sum_of_divisors = %ld\n", sum_of_divisors);

    return 0;
}
