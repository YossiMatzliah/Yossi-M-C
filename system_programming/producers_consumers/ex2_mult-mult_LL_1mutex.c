
/* #define _XOPEN_SOURCE 700
#define _POSIX_C_SOURCE 200112L  */
/* #define _DEFAULT_SOURCE */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "linked_list.h"

#define MAX_ITEMS (10)
#define CONSUMERS (10)
#define PRODUCERS (10)

pthread_mutex_t mutex;
sll_t *list;

void *producer(void *arg)
{
    int id = *(int *)arg;
    int input = id;
    
    pthread_mutex_lock(&mutex);
    SLLInsertBefore(SLLBeginIter(list), &input);
    printf("Producer %d produces item %d\n", id, input);
    pthread_mutex_unlock(&mutex);
  
    return NULL;
}

void *consumer(void *arg)
{
    int id = *(int *)arg;
    int item = 0;

    if (!SLLIsEmpty(list))
    {
        pthread_mutex_lock(&mutex);
        item = *(int *)(SLLGetData(SLLBeginIter(list)));
        SLLRemove(SLLBeginIter(list));
        printf("Consumer %d consumed item %d\n", id, item);
        pthread_mutex_unlock(&mutex);
    }
   
    return NULL;
}

int main(void)
{
    pthread_t prodecers[PRODUCERS];
    pthread_t consumers[CONSUMERS];
    int prod_id[PRODUCERS];
    int cons_id[CONSUMERS];
    int i = 0;

    pthread_mutex_init(&mutex, NULL);
    list = SLLCreate();

    for (i = 0; i < PRODUCERS; ++i)
    {
        prod_id[i] = i;
        if (0 != pthread_create(&prodecers[i], NULL, producer, &prod_id[i]))
        {
            perror("Failed to create producer thread\n");
            exit(1);
        }

        cons_id[i] = i;
        if (0 != pthread_create(&consumers[i], NULL, consumer, &cons_id[i]))
        {
            perror("Failed to create consumer thread\n");
            exit(1);
        }
    }

    for (i = 0; i < PRODUCERS; ++i)
    {
        if (0 != pthread_join(prodecers[i], NULL))
        {
            perror("Failed to join producer thread\n");
            exit(1);
        }
    }

    for (i = 0; i < CONSUMERS; ++i)
    {
        if (0 != pthread_join(consumers[i], NULL))
        {
            perror("Failed to join consumer thread\n");
            exit(1);
        }
    }

    SLLDestroy(list);
    pthread_mutex_destroy(&mutex);

    return 0;
}
