/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Avri				*
*	Date      : ??/06/2023			*
************************************/

#define _POSIX_C_SOURCE 200112L
#include <stdio.h>	    /* printf, perror */
#include <stdlib.h>     /* malloc, free, qsort */
#include <string.h>	    /* memcpy */
#include <time.h>	    /* time */
#include <pthread.h>    /* threads */

#define THREADS (8)
#define CHARS (985084)
#define DICT_WORDS (104334)
#define COPIES (3)  
#define CHARS_IN_DICT (COPIES * CHARS)
#define WORDS_IN_DICT (COPIES * DICT_WORDS)
#define ONE_DICT_SIZE ((CHARS - DICT_WORDS))
#define FULL_DICT_SIZE (COPIES * (CHARS - DICT_WORDS))

#define TO_NANO (1000000000)
#define WORD_SIZE (8)
#define BUNCH_SIZE (WORDS_IN_DICT / THREADS)

char *dictionary = {0};

/********************** Help Functions **********************/

int RandCompare(const void *lhd, const void *rhd);
int CompareFunc(const void *lhd, const void *rhd);

/********************** Static Functions **********************/

static void CreateDictionary();
static void *ShuffleQsort(void *dictionary);

/********************** Main Functions **********************/

int main()
{
	CreateDictionary();

	return 0;
}

/********************** Static Functions **********************/

static void CreateDictionary()
{
    size_t i = 0;
    FILE *fp = NULL;
    char *path_to_file = "/usr/share/dict/american-english";
    char *memory_buffer = (char *)calloc(CHARS, sizeof(char));
    char *temp_buffer = (char *)calloc(CHARS, sizeof(char));

    char *runner = NULL;

    int curr_word = 0;
    struct timespec start_time = {0};
    struct timespec stop_time = {0};
    double time_to_finish = 0.0;
    pthread_t threads[THREADS];

    dictionary = (char *)calloc(CHARS_IN_DICT, sizeof(char));
    if (NULL == dictionary || NULL == memory_buffer)
    {
        perror("Allocation Error\n");
        free(dictionary);
        free(memory_buffer);
        return;
    }
    
    fp = fopen(path_to_file, "r");
    if (NULL == fp)
    {
        printf("Error opening file");
        return;
    }
    
    fread(memory_buffer, sizeof(char), CHARS, fp);

    runner = memory_buffer;
    temp_buffer = memory_buffer;

    for (i = 0; i < CHARS; ++i)
	{
		if ('\n' != *runner)
        {
            *temp_buffer = *runner;
            ++temp_buffer;
        }

		++runner; 
	}

    for (i = 0; i < COPIES; ++i)
    {
        memcpy(dictionary + (i * ONE_DICT_SIZE), memory_buffer, ONE_DICT_SIZE);
    }

    /* for (i = 0; i < (ONE_DICT_SIZE); ++i)
    {
        printf("%c", *(dictionary + i));
    } */

    /* for (i = 0; i < 10; ++i)
    {
        printf("%c", *(dictionary + i));
    }
    printf("\n");
    */

    /* printf("\n");
    for (i = (ONE_DICT_SIZE); i < ((ONE_DICT_SIZE)) + 10; ++i)
    {
        printf("%c", *(dictionary + i));
    } */ 

    srand(time(NULL));
    ShuffleQsort(dictionary);

    /* for (i = 0; i < (ONE_DICT_SIZE); ++i)
    {
        printf("%c", *(dictionary + i));
    } */

    /* for (i = 0; i < (FULL_DICT_SIZE); ++i)
    {
        printf("%c", *(dictionary + i));
    } */  

    /* if (-1 == clock_gettime(CLOCK_REALTIME, &start_time))
    {
        perror("Error: clock gettime\n");
        return;
    }
    
    for (i = 0; i < THREADS; ++i)
    {
        if (0 != pthread_create(&threads[i], NULL, ThQSort, (void *)i))
        {
            perror("Failed to create thread");
            exit(1);
        }
    } */

    /* for (i = 0; i < BUNCH_SIZE; ++i)
    {
        printf("%s\n", *(dictionary + i + BUNCH_SIZE));
    } */

    /* qsort(&dictionary[0], WORDS_IN_DICT, sizeof(char *), CompareFunc);   */ 

    /* for (i = 0; i < WORDS_IN_DICT; ++i)
    {
        printf("%s\n", *(dictionary + i));
    } */

    /* if (-1 == clock_gettime(CLOCK_REALTIME, &stop_time))
    {
        perror("Error: clock gettime\n");
        return;
    }

    time_to_finish = (stop_time.tv_sec - start_time.tv_sec);
    time_to_finish += (((double)stop_time.tv_nsec / TO_NANO) - ((double)start_time.tv_nsec / TO_NANO)); 
    printf("QSort: time with %d threads is: %f\n", THREADS, time_to_finish);

    for(i = 0; i < THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    } */

    free(dictionary);
    free(memory_buffer);
    fclose(fp);
}

/********************** Help Functions **********************/

int RandCompare(const void *lhd, const void *rhd)
{
    (void)lhd;
    (void)rhd;

    return (rand() % 10000 - rand() % 10000);
}

/* int CompareFunc(const void *lhd, const void *rhd)
{
    return strcmp(*(char **)lhd, *(char **)rhd);
} */

/********************** static Functions **********************/

static void *ShuffleQsort(void *dictionary)
{
    qsort(dictionary, ((CHARS - DICT_WORDS) * COPIES), sizeof(char), RandCompare);
    return NULL;
}



