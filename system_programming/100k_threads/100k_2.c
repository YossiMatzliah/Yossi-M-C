#include <pthread.h>	/* pthread_t */
#include <stdio.h>      /* printf */
#include <unistd.h>     /* sleep */
#include <stddef.h>     /* size_t */

#define ARR_SIZE (100000)

int arr[ARR_SIZE] = {0};

/**********************************************************************************
*								static Functions								  *
***********************************************************************************/

static void *FillArr(void *idx);
static void PrintArr(void);
static void CountFaults(void);

/**********************************************************************************
*								Main Function								 	  *
***********************************************************************************/

int main()
{
    size_t i = 0;
    pthread_t threads[ARR_SIZE] = {0};

    for (i = 0; i < ARR_SIZE; ++i)
    {  
        while (0 != pthread_create(&threads[i], NULL, FillArr, (void *)i));
    }

    sleep(10);
    PrintArr();
    CountFaults();
    perror(" ");

    return 0;
}

/**********************************************************************************
*								static Functions								  *
***********************************************************************************/

static void *FillArr(void *idx)
{
    int i = (int)idx;

    arr[i] = i;

    return NULL;
}

static void PrintArr(void)
{
    size_t i = 0;

    for (i = 0; i < ARR_SIZE; ++i)
    {
        printf("arr[%ld] = %d\n", i, arr[i]);
    }
}

static void CountFaults(void)
{
    size_t i = 0;
    size_t count = 0;

    for (i = 0; i < ARR_SIZE; ++i)
    {
        if (0 == arr[i])
        {
            ++count;
        }
    }

    printf("Error count = %lu\n", count);
}