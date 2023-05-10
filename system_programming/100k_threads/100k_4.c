#include <pthread.h> /* pthread */
#include <stdio.h>   /* printf */
#include <unistd.h>  /* sleep */
#include <stddef.h>  /* size_t */
#include <stdlib.h>  /* exit */

#define THREAD_LIMIT (16)
#define NUMBER_TO_CALCULATE_DIVISORS (5915587277)
#define RANGE ((NUMBER_TO_CALCULATE_DIVISORS / THREAD_LIMIT) + 1)

static void *SumOfDivisors(void *num);

int main()
{
    size_t i = 0;
    pthread_t threads[THREAD_LIMIT] = {0};
    size_t curr_low_range = 1;
    size_t *thread_result = NULL;
    size_t result = 0;

    for (i = 0; i < THREAD_LIMIT; ++i)
    {
        if (0 != pthread_create(&threads[i], NULL, SumOfDivisors, (void *)curr_low_range))
        {
            perror("Failed to create thread");
            exit(1);
        }

        curr_low_range += RANGE;
    }

    for (i = 0; i < THREAD_LIMIT; ++i)
    {
        if (0 == pthread_join(threads[i], (void **)&thread_result))
        {
            result += *(size_t *)thread_result;
            free(thread_result);
        }
    }
	
	printf("Num of Threads: %d.\n", THREAD_LIMIT);
    printf("Sum of divisors of number: %ld is %ld\n", NUMBER_TO_CALCULATE_DIVISORS, result);
    perror(" ");
    printf("\n");

    return 0;
}

static void *SumOfDivisors(void *low_range)
{
    size_t i = 0;
    size_t high_range = (size_t)low_range + RANGE;
    size_t *sum_of_divisors = malloc(sizeof(size_t));
    
    if (NUMBER_TO_CALCULATE_DIVISORS < high_range)
    {
        high_range = NUMBER_TO_CALCULATE_DIVISORS + 1;
    }

    for (i = (size_t)low_range; i < high_range; ++i)
    {
        if (0 == NUMBER_TO_CALCULATE_DIVISORS % i)
        {
            *sum_of_divisors += i;
            printf("%ld\t", i);
        }
    }

    return sum_of_divisors;
}
