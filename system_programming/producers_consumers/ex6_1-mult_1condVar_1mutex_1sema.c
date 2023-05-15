/****************************************
*   Producers Consumers Implementation  * 
*	Developer : Lilach Rabinovich       *
*	Date      : .05.2023        	    *
****************************************/
#include <stdio.h>      /* perror */
#include <pthread.h>    /* pthread */
#include <fcntl.h>      /* O_CREAT */
#include <semaphore.h>  /* semaphore */

#define LEN (20)
#define NUM_OF_CONSUMERS (5)
#define SUCCESS (0)
#define TRUE (1)


pthread_cond_t cond_var;
pthread_mutex_t mutex;
sem_t sema;
int count_cons = 0;
int shared = 0;

/**********************************************************************************
*								static Functions								  *
***********************************************************************************/

static void *Producer(void *none);
static void *Consumers(void *none);

/**********************************************************************************
*								Main Function								 	  *
***********************************************************************************/

int main()
{
    pthread_t producer;
    pthread_t consumers_th[NUM_OF_CONSUMERS];
    int producer_id = {0};
    int consumers_id[NUM_OF_CONSUMERS] = {0};
    unsigned int init_value_sema = 0;
    int i = 0;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&sema, 0, init_value_sema);
    pthread_cond_init(&cond_var, NULL);

    if (0 != pthread_create(&producer, NULL, Producer, &producer_id))
    {
        perror("Failed in pthread_create - producer\n");
        return 1;
    }

    for (i = 0; i < NUM_OF_CONSUMERS; ++i)
    {
        if (0 != pthread_create(&consumers_th[i], NULL, Consumers, &consumers_id[i]))
        {
            perror("Failed in pthread_create - consumer\n");
            return 1;
        }
    }

    if (0 != pthread_join(producer, NULL))
    {
        perror("Failed in pthread_join - producer\n");
        return 1;
    }

    for (i = 0; i < NUM_OF_CONSUMERS; ++i)
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

    sem_destroy(&sema);
    pthread_cond_destroy(&cond_var);

    return 0;
}

/**********************************************************************************
*								static Functions								  *
***********************************************************************************/


static void *Producer(void *none)
{
    int i = NUM_OF_CONSUMERS;
    (void)none;

    while (i > 0)
    {
        pthread_mutex_lock(&mutex);
        ++shared;
        
        while (NUM_OF_CONSUMERS > count_cons)
        {
            sem_post(&sema); 
            pthread_cond_wait(&cond_var, &mutex);
        }

        printf("shared = %d\n", shared);    
        count_cons = 0;
        
        pthread_mutex_unlock(&mutex);
        --i; 
    }

    return NULL;
}

static void *Consumers(void *none)
{
    int i = NUM_OF_CONSUMERS;

    (void)none;

    while (i > 0)
    {
        sem_wait(&sema);
        pthread_mutex_lock(&mutex);
        count_cons++;
        
        printf("Consumer read massege %d\n", shared);
        
        pthread_cond_signal(&cond_var);
        pthread_mutex_unlock(&mutex);
        --i;
    }

    return NULL;
}
