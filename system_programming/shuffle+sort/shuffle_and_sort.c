/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :					*
*	Date      : 20/05/2023			*
************************************/

#define _POSIX_C_SOURCE 200112L
#include <stdio.h>	    /* printf, perror */
#include <stdlib.h>     /* malloc, free, qsort */
#include <string.h>	    /* memcpy */
#include <time.h>	    /* time */
#include <pthread.h>    /* threads */

#define THREADS (8)
#define DICT_BYTE_SIZE (985084)
#define DICT_WORDS (104334)
#define COPIES (50)  
#define WORDS_IN_DICT (COPIES * DICT_WORDS)
#define TO_NANO (1000000000)
#define WORD_SIZE (8)
#define BUNCH_SIZE (WORDS_IN_DICT / THREADS)

char **dictionary = {0};

/********************** Help Functions **********************/

int RandCompare(const void *lhd, const void *rhd);
int CompareFunc(const void *lhd, const void *rhd);

/********************** Static Functions **********************/

static void CreateDictionary();
static void *ShuffleQsort(void *dictionary);
static void *ThQSort(void *thread_id);
static void *ThMergeSort(void *arg);
static int MergeSort(char **dictionary, size_t num_elements, int (*comp)(const void *, const void *));
static int MergeSortRec(char **arr, size_t left, size_t right, int (*comp)(const void *, const void *));
static int MergeTwoArr(char **arr, size_t left, size_t mid, size_t right, int (*comp)(const void *, const void *));

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
    char *memory_buffer = (char *)calloc(DICT_BYTE_SIZE, sizeof(char));
    int curr_word = 0;
    struct timespec start_time = {0};
    struct timespec stop_time = {0};
    double time_to_finish = 0.0;
    pthread_t threads[THREADS];

    dictionary = (char **)calloc(COPIES * DICT_WORDS, sizeof(char *));
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

    fread(memory_buffer, sizeof(char), DICT_BYTE_SIZE, fp);
    dictionary[curr_word] = memory_buffer;
    ++curr_word;

    for (i = 0; i < DICT_BYTE_SIZE; ++i)
    {   
        if ('\n' == memory_buffer[i])
        {
            memory_buffer[i] = '\0';

            if (i != (DICT_BYTE_SIZE - 1))
            {
                dictionary[curr_word] = &(memory_buffer[i + 1]);
                ++curr_word;
            }
        }
    }

    for (i = 1; i < COPIES; ++i)
    {
        memcpy(&dictionary[DICT_WORDS * i], dictionary, DICT_WORDS * sizeof(char *));
    }

    
    srand(time(NULL));
    ShuffleQsort(dictionary);

    /* for (i = 0; i < BUNCH_SIZE; ++i)
    {
        printf("%s\n", *(dictionary + i + BUNCH_SIZE));
    } */

    if (-1 == clock_gettime(CLOCK_REALTIME, &start_time))
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
    }

    /* for (i = 0; i < BUNCH_SIZE; ++i)
    {
        printf("%s\n", *(dictionary + i + BUNCH_SIZE));
    } */

    qsort(&dictionary[0], WORDS_IN_DICT, sizeof(char *), CompareFunc);   

    /* for (i = 0; i < WORDS_IN_DICT; ++i)
    {
        printf("%s\n", *(dictionary + i));
    } */

    if (-1 == clock_gettime(CLOCK_REALTIME, &stop_time))
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
    }

    ShuffleQsort(dictionary);

    if (-1 == clock_gettime(CLOCK_REALTIME, &start_time))
    {
        perror("Error: clock gettime\n");
        return;
    }

    for (i = 0; i < THREADS; ++i)
    {
        if (0 != pthread_create(&threads[i], NULL, ThMergeSort, (void *)i))
        {
            perror("Failed to create thread");
            exit(1);
        }
    }
    
    /* for (i = 0; i < BUNCH_SIZE; ++i)
    {
        printf("%s\n", *(dictionary + i + BUNCH_SIZE));
    } */

    /* qsort(&dictionary[0], WORDS_IN_DICT, sizeof(char *), CompareFunc); */   
    MergeSort(&dictionary[0], WORDS_IN_DICT, CompareFunc);

    /* for (i = 0; i < WORDS_IN_DICT; ++i)
    {
        printf("%s\n", *(dictionary + i));
    } */

    if (-1 == clock_gettime(CLOCK_REALTIME, &stop_time))
    {
        perror("Error: clock gettime\n");
        return;
    }

    time_to_finish = (stop_time.tv_sec - start_time.tv_sec);
    time_to_finish += (((double)stop_time.tv_nsec / TO_NANO) - ((double)start_time.tv_nsec / TO_NANO)); 
    printf("MergeSort: time with %d threads is: %f\n", THREADS, time_to_finish);

    for(i = 0; i < THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    /* for (i = 0; i < BUNCH_SIZE; ++i)
    {
        printf("%s\n", *(dictionary + i + BUNCH_SIZE));
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

int CompareFunc(const void *lhd, const void *rhd)
{
    return strcmp(*(char **)lhd, *(char **)rhd);
}

/********************** static Functions **********************/

static void *ShuffleQsort(void *dictionary)
{
    qsort(dictionary, (size_t)WORDS_IN_DICT, sizeof(char *), RandCompare);
    return NULL;
}

static void *ThQSort(void *thread_id)
{
    qsort(&dictionary[(size_t)thread_id * BUNCH_SIZE], (size_t)BUNCH_SIZE, sizeof(char *), CompareFunc);
    return NULL;
}

static void *ThMergeSort(void *arg)
{
    MergeSort(&dictionary[(size_t)arg * BUNCH_SIZE], (size_t)BUNCH_SIZE, CompareFunc);
    return NULL;
}

static int MergeSort(char **dictionary, size_t num_elements, int (*comp)(const void *, const void *))
{
	return MergeSortRec(dictionary, 0, num_elements - 1, comp);
}

static int MergeSortRec(char **arr, size_t left, size_t right, int (*comp)(const void *, const void *))
{
	int mid = left + ((right - left) / 2);
	
	if (left >= right)
	{
		return 0;
	}
	
	if (1 == MergeSortRec(arr, left, mid, comp))
	{
		return 1;
	}
	
	if (1 == MergeSortRec(arr, mid + 1, right, comp))
	{
		return 1;
	}
	
	if (1 == MergeTwoArr(arr, left, mid, right, comp))
	{
		return 1;
	}
	
	return 0;
}

static int MergeTwoArr(char **arr, size_t left, size_t mid, size_t right, int (*comp)(const void *, const void *))
{
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	size_t left_length = mid - left + 1;
	size_t right_length = right - mid;
	

	char **left_arr = NULL;
	char **right_arr = NULL;
	
	left_arr = (char **)malloc(sizeof(char *) * left_length);
	if (NULL == left_arr)
	{
		perror("merge malloc err");
		return 1;
	}
	
	right_arr = (char **)malloc(sizeof(char *) * right_length);
	if (NULL == right_arr)
	{
		perror("merge malloc err");
        free(left_arr);
		return 1;
	}
	
	for (i = 0; i < left_length; ++i)
	{
		left_arr[i] = arr[left + i];
	}
	
	for (i = 0; i < right_length; ++i)
	{
		right_arr[i] = arr[mid + 1 + i];
	}
	
	for (i = 0, j = 0, k = left; k <= right; ++k)
	{
		if (i < left_length)
		{
			if (j >= right_length || 0 > comp(&left_arr[i], &right_arr[j]))
			{
				arr[k] = left_arr[i];
				++i;
			}
			else
			{
				arr[k] = right_arr[j];
				++j;
			}
		}
		else
		{
			arr[k] = right_arr[j];
			++j;
		}
	}
	
	free(left_arr);
	free(right_arr);
	
	return 0;
}

