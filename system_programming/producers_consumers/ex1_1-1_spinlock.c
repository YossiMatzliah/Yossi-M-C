
#define _XOPEN_SOURCE 700
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define BUFFER_SIZE (1)

int buffer[BUFFER_SIZE];
int buffer_index;

pthread_spinlock_t lock;

void *producer()
{
    int i = 0;

    for(i = 0; i < 10; ++i)
    {
        while (buffer_index == BUFFER_SIZE);
        pthread_spin_lock(&lock);
        buffer[buffer_index++] = i;
        printf("Produce %d\n", i);
        pthread_spin_unlock(&lock);
    }
}

void *consumer()
{
    int i = 0; 
	int consumed = 0;

    for (i = 0; i < 10; i++) 
    {
        while (buffer_index == 0); 
        pthread_spin_lock(&lock);
        consumed = buffer[--buffer_index];
        printf("Consumed %d\n", consumed);
        pthread_spin_unlock(&lock);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t producer_thread;
    pthread_t consumer_thread;
	buffer_index = 0;
	
    pthread_spin_init(&lock, 0);
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    pthread_spin_destroy(&lock);

    return 0;
}
