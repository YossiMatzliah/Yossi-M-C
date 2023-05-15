#include <stdio.h>      /* perror */
#include <pthread.h>    /* pthread */
#include <fcntl.h>      /* O_CREAT */
#include <semaphore.h>  /* semaphore */

#include "dll.h"

#define NUM_OF_PRODUCTS (10)
#define NUM_OF_THEADS (10)
#define SUCCESS (0)
#define TRUE (1)

int arr[NUM_OF_THEADS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int sema_value;
dll_t *d_list;
pthread_mutex_t mutex;
sem_t *sema;

/**********************************************************************************
*								static Functions								  *
***********************************************************************************/

static void *Producers(void *thread_id);
static void *Consumers(void *thread_id);
static void PrintDLL(dll_t *dll);

/**********************************************************************************
*								Main Function								 	  *
***********************************************************************************/

int main()
{
    pthread_t producers_th[NUM_OF_THEADS];
    pthread_t consumers_th[NUM_OF_THEADS];
    int producers_id[NUM_OF_THEADS] = {0};
    int consumers_id[NUM_OF_THEADS] = {0};
    unsigned int init_value = 0;
    char *name = "semaly";
    int i = 0;

    pthread_mutex_init(&mutex, NULL);
    
    sema = sem_open(name, O_CREAT, 0666, init_value);
    if (0 != sem_init(sema, 1, init_value))
    {
        printf("Creating the Semaphore Failed\n");
        return 0;
    }

    d_list = DLLCreate();
    if (NULL == d_list)
    {
        perror("Failed to create doubly linked list\n");
        return 1;
    }

    for (i = 0; i < NUM_OF_THEADS; ++i)
    {
        if (0 != pthread_create(&producers_th[i], NULL, Producers, &producers_id[i]))
        {
            perror("Failed in pthread_create - producer\n");
            return 1;
        }
    }

    for (i = 0; i < NUM_OF_THEADS; ++i)
    {
        if (0 != pthread_create(&consumers_th[i], NULL, Consumers, &consumers_id[i]))
        {
            perror("Failed in pthread_create - consumer\n");
            return 1;
        }
    }

    for (i = 0; i < NUM_OF_THEADS; ++i)
    {
        if (0 != pthread_join(producers_th[i], NULL))
        {
            perror("Failed in pthread_join - producer\n");
            return 1;
        }
    }

    for (i = 0; i < NUM_OF_THEADS; ++i)
    {
        if (0 != pthread_join(consumers_th[i], NULL))
        {
            perror("Failed in pthread_join - consumer\n");
            return 1;
        }
    }
    
    if (SUCCESS != pthread_mutex_destroy(&mutex))   /* Destroy mutex */
    {
        perror("pthread_mutex_destroy Failed\n");
        return 1;
    }
    
    sem_getvalue(sema, &sema_value);
    printf("\nLast semaphore value = %d\n", sema_value);

    sem_close(sema);
    sem_unlink(name);
    DLLDestroy(d_list);

    return 0;
}

/**********************************************************************************
*								static Functions								  *
***********************************************************************************/

static void *Producers(void *thread_id)
{
    int i = 0;

    for (i = 0; i < NUM_OF_PRODUCTS; ++i)
    {        
        pthread_mutex_lock(&mutex);
        DLLPushBack(d_list, &arr[i]);
        sem_post(sema);
        sem_getvalue(sema, &sema_value);
        printf("\nProducer semaphore value = %d\n", sema_value);
        printf("\nProducer id %d.\n", *(int *)thread_id);
        PrintDLL(d_list);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

static void *Consumers(void *thread_id)
{
    int i = 0;
    
    for (i = 0; i < NUM_OF_PRODUCTS; ++i)
    {
        sem_wait(sema);
        pthread_mutex_lock(&mutex);

        DLLPopBack(d_list);
        sem_getvalue(sema, &sema_value);
        printf("\nConsumer semaphore value = %d\n", sema_value);
        printf("\nConsumer id %d.\n", *(int *)thread_id);
        PrintDLL(d_list);

        pthread_mutex_unlock(&mutex);
    }
    
    return NULL;
}

static void PrintDLL(dll_t *dll)
{
	iterator_t iter = DLLBeginIter(dll);
	
	printf("DLL IS:\n");
	
	while (NULL != DLLNextIter(iter))
	{
		printf("(%d)<---->", *(int *)DLLGetData(iter));
		iter = DLLNextIter(iter);
	}
	
	printf("NULL\n\n");
}
