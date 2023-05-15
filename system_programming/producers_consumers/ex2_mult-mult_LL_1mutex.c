
#define _XOPEN_SOURCE 700
#define _POSIX_C_SOURCE 200112L 
#define _DEFAULT_SOURCE
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
    int i = 0;
    size_t input = id * MAX_ITEMS;
    for (i = 0; i < MAX_ITEMS; ++i)
    {
        pthread_mutex_lock(&mutex);
        SLLInsertBefore(SLLBeginIter(list), &input);
        pthread_mutex_unlock(&mutex);
        printf("Producer %d produces item %ld\n", id, input);
        usleep(100000);
    }
    return NULL;
}

void *consumer(void *arg)
{
    int id = *(int *)arg;
    size_t item = 0;
    int i = 0;

    for (i = 0; i < MAX_ITEMS; ++i)
    {
        pthread_mutex_lock(&mutex);
        if (!SLLIsEmpty(list))
        {
            item = *(size_t *)(SLLGetData(SLLBeginIter(list)));
            SLLRemove(SLLBeginIter(list));
            pthread_mutex_unlock(&mutex);
            printf("Consumer %d consumed item %ld\n", id, item);
            usleep(100000);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            usleep(100000);
        }
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
    }

    for (i = 0; i < CONSUMERS; ++i)
    {
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
