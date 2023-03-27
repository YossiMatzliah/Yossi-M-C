/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Oran  				*
*	Date      : 14/03/2023			*
************************************/

#include <stdio.h>	/* printf */
#include <time.h>	/* clock_t, CLOCKS_PER_SEC */
#include <stdlib.h>	/* rand(), qsort */

#include "sort.h"

#define ARRAY_SIZE 		(5000)
#define RANGE_SIZE 		(100)
#define SEVEN_DIGIT_MAX	(9999999)
#define ONE_MIL			(1000000)

#define U_LINE 	"\033[1m\033[4m"
#define RED   	"\033[1m\033[41m\x1B[30m"
#define GRN   	"\033[1m\033[42m\x1B[30m"
#define RESET 	"\033[0m"

#define TRUE 	(1)
#define FALSE 	(0)
#define FAILURE (1)
#define SUCCESS (0)

#define PRINT_TEST(x) ((TRUE == (x)) ? printf(GRN"SUCCESS!"RESET"\n\n") : printf(RED"FAILURE!, line %d"RESET"\n\n", __LINE__))

/*****************************************************************/

static void TestBubbleSort();
static void TestInsertionSort();
static void TestSelectionSort();
static void TestCountingSort();
static void TestRadixSort();
static void TestBinarySearch();

static int IsSameArr(int arr1[], int arr2[], size_t size);
int CmpFuncAscending(const int lhs, const int rhs);
int cmpfuncForQsort(const void * lhs, const void * rhs);

/*****************************************************************/

int main()
{
	srand(time(NULL));
	
	TestBubbleSort();
	TestInsertionSort();
	TestSelectionSort();
	TestCountingSort();
	TestRadixSort();
	TestBinarySearch();
	
	return 0;
}

static void TestBubbleSort()
{
	clock_t start = 0;
	clock_t end = 0;
	double time[10] = {0};
	double q_time[10] = {0};
	int array[ARRAY_SIZE] = {0};
	int q_array[ARRAY_SIZE] = {0};
	size_t i = 0;
	size_t j = 0;
	int sort_check = SUCCESS;
	double avg_time = 0;
	double q_avg_time = 0;
	
	printf(U_LINE"BubbleSort Test:\n"RESET);
	
	for (i = 0 ; i < 10; ++i)
	{
		for (j = 0 ; j < ARRAY_SIZE ; ++j)
		{
			array[j] = rand() % ARRAY_SIZE;
			q_array[j] = array[j];
		}
		
		start = clock();
		BubbleSort(array, ARRAY_SIZE, CmpFuncAscending);
		end = clock();
	
		time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		avg_time += time[i];
		
		start = clock(); 
		qsort(q_array, ARRAY_SIZE, sizeof(int), cmpfuncForQsort);
		end = clock();
		
		q_time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		q_avg_time += q_time[i];
		
	} 
	avg_time /= 10;
	q_avg_time /= 10;
	
	for (i = 0 ; i < ARRAY_SIZE - 1; ++i)
	{
		if (array[i] > array[i + 1])
		{
			sort_check = FAILURE;
		}
	}
	
	PRINT_TEST(SUCCESS == sort_check);
	PRINT_TEST(TRUE == IsSameArr(array, q_array, ARRAY_SIZE));
	
	printf("Avarage time for my bubble sort(random order): %f\n", avg_time);
	printf("Avarage time for built-in qsort(random order): %f\n", q_avg_time);
	
	avg_time = 0;
	q_avg_time = 0;		
	
	for (j = 0; j < ARRAY_SIZE ; ++j)
	{
		array[j] = ARRAY_SIZE - j;
		q_array[j] = array[j];
	}
	
	for (i = 0 ; i < 10 ; ++i)
	{
		start = clock();
		BubbleSort(array, ARRAY_SIZE, CmpFuncAscending);
		end = clock();
	
		time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		avg_time += time[i];
		
		start = clock(); 
		qsort(q_array, ARRAY_SIZE, sizeof(int), cmpfuncForQsort);
		end = clock();
		
		q_time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		q_avg_time += q_time[i];
		
	} 
	
	PRINT_TEST(TRUE == IsSameArr(array, q_array, ARRAY_SIZE));
	
	avg_time /= 10;
	q_avg_time /= 10;
	printf("Avarage time for my bubble sort(descend order): %f\n", avg_time);
	printf("Avarage time for built-in qsort(descend order): %f\n", q_avg_time);
	
	avg_time = 0;
	for (j = 0; j < ARRAY_SIZE ; ++j)
	{
		array[j] = j;
		q_array[j] = array[j];
	}
	for (i = 0 ; i < 10 ; ++i)
	{
		start = clock();
		BubbleSort(array, ARRAY_SIZE, CmpFuncAscending);
		end = clock();
	
		time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		avg_time += time[i];
		
		start = clock(); 
		qsort(q_array, ARRAY_SIZE, sizeof(int), cmpfuncForQsort);
		end = clock();
		
		q_time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		q_avg_time += q_time[i];
	} 
	
	PRINT_TEST(TRUE == IsSameArr(array, q_array, ARRAY_SIZE));

	avg_time /= 10;
	q_avg_time /= 10;
	printf("Avarage time for my bubble sort(ascend order): %f\n", avg_time);
	printf("Avarage time for built-in qsort(ascend order): %f\n", q_avg_time);
}

static void TestInsertionSort()
{
	clock_t start = 0;
	clock_t end = 0;
	double time[10] = {0};
	double q_time[10] = {0};
	int array[ARRAY_SIZE] = {0};
	int q_array[ARRAY_SIZE] = {0};
	size_t i = 0;
	size_t j = 0;
	int sort_check = SUCCESS;
	double avg_time = 0;
	double q_avg_time = 0;
	
	printf(U_LINE"\nInsertionSort Test:\n"RESET);
	
	for (i = 0 ; i < 10; ++i)
	{
		for (j = 0 ; j < ARRAY_SIZE ; ++j)
		{
			array[j] = rand() % ARRAY_SIZE;
			q_array[j] = array[j];
		}
		
		start = clock();
		InsertionSort(array, ARRAY_SIZE, CmpFuncAscending);
		end = clock();
	
		time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		avg_time += time[i];
		
		start = clock(); 
		qsort(q_array, ARRAY_SIZE, sizeof(int), cmpfuncForQsort);
		end = clock();
		
		q_time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		q_avg_time += q_time[i];
		
	} 
	avg_time /= 10;
	q_avg_time /= 10;
	
	for (i = 0 ; i < ARRAY_SIZE - 1; ++i)
	{
		if (array[i] > array[i + 1])
		{
			sort_check = FAILURE;
		}
	}
	
	PRINT_TEST(SUCCESS == sort_check);
	PRINT_TEST(TRUE == IsSameArr(array, q_array, ARRAY_SIZE));
	
	printf("Avarage time for my Insertion sort(random order): %f\n", avg_time);
	printf("Avarage time for built-in qsort(random order): %f\n", q_avg_time);
	
	avg_time = 0;
	q_avg_time = 0;		
	
	for (j = 0; j < ARRAY_SIZE ; ++j)
	{
		array[j] = ARRAY_SIZE - j;
		q_array[j] = array[j];
	}
	
	for (i = 0 ; i < 10 ; ++i)
	{
		start = clock();
		InsertionSort(array, ARRAY_SIZE, CmpFuncAscending);
		end = clock();
	
		time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		avg_time += time[i];
		
		start = clock(); 
		qsort(q_array, ARRAY_SIZE, sizeof(int), cmpfuncForQsort);
		end = clock();
		
		q_time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		q_avg_time += q_time[i];
		
	} 
	
	PRINT_TEST(TRUE == IsSameArr(array, q_array, ARRAY_SIZE));
	
	avg_time /= 10;
	q_avg_time /= 10;
	printf("Avarage time for my Insertion sort(descend order): %f\n", avg_time);
	printf("Avarage time for built-in qsort(descend order): %f\n", q_avg_time);
	
	avg_time = 0;
	for (j = 0; j < ARRAY_SIZE ; ++j)
	{
		array[j] = j;
		q_array[j] = array[j];
	}
	for (i = 0 ; i < 10 ; ++i)
	{
		start = clock();
		InsertionSort(array, ARRAY_SIZE, CmpFuncAscending);
		end = clock();
	
		time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		avg_time += time[i];
		
		start = clock(); 
		qsort(q_array, ARRAY_SIZE, sizeof(int), cmpfuncForQsort);
		end = clock();
		
		q_time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		q_avg_time += q_time[i];
	} 
	
	PRINT_TEST(TRUE == IsSameArr(array, q_array, ARRAY_SIZE));
	
	avg_time /= 10;
	q_avg_time /= 10;
	printf("Avarage time for my Insertion sort(ascend order): %f\n", avg_time);
	printf("Avarage time for built-in qsort(ascend order): %f\n", q_avg_time);
}

static void TestSelectionSort()
{
	clock_t start = 0;
	clock_t end = 0;
	double time[10] = {0};
	double q_time[10] = {0};
	int array[ARRAY_SIZE] = {0};
	int q_array[ARRAY_SIZE] = {0};
	size_t i = 0;
	size_t j = 0;
	int sort_check = SUCCESS;
	double avg_time = 0;
	double q_avg_time = 0;
	
	printf(U_LINE"\nSelectionSort Test:\n"RESET);
	
	for (i = 0 ; i < 10; ++i)
	{
		for (j = 0 ; j < ARRAY_SIZE ; ++j)
		{
			array[j] = rand() % ARRAY_SIZE;
			q_array[j] = array[j];
		}
		
		start = clock();
		SelectionSort(array, ARRAY_SIZE, CmpFuncAscending);
		end = clock();
	
		time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		avg_time += time[i];
		
		start = clock(); 
		qsort(q_array, ARRAY_SIZE, sizeof(int), cmpfuncForQsort);
		end = clock();
		
		q_time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		q_avg_time += q_time[i];
		
	} 
	avg_time /= 10;
	q_avg_time /= 10;
	
	for (i = 0 ; i < ARRAY_SIZE - 1; ++i)
	{
		if (array[i] > array[i + 1])
		{
			sort_check = FAILURE;
		}
	}
	
	PRINT_TEST(SUCCESS == sort_check);
	PRINT_TEST(TRUE == IsSameArr(array, q_array, ARRAY_SIZE));
	
	printf("Avarage time for my Selection sort(random order): %f\n", avg_time);
	printf("Avarage time for built-in qsort(random order): %f\n", q_avg_time);
	
	avg_time = 0;
	q_avg_time = 0;		
	
	for (j = 0; j < ARRAY_SIZE ; ++j)
	{
		array[j] = ARRAY_SIZE - j;
		q_array[j] = array[j];
	}
	
	for (i = 0 ; i < 10 ; ++i)
	{
		start = clock();
		SelectionSort(array, ARRAY_SIZE, CmpFuncAscending);
		end = clock();
	
		time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		avg_time += time[i];
		
		start = clock(); 
		qsort(q_array, ARRAY_SIZE, sizeof(int), cmpfuncForQsort);
		end = clock();
		
		q_time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		q_avg_time += q_time[i];
	} 
	
	PRINT_TEST(TRUE == IsSameArr(array, q_array, ARRAY_SIZE));
	
	avg_time /= 10;
	q_avg_time /= 10;
	printf("Avarage time for my Selection sort(descend order): %f\n", avg_time);
	printf("Avarage time for built-in qsort(descend order): %f\n", q_avg_time);
	
	avg_time = 0;
	for (j = 0; j < ARRAY_SIZE ; ++j)
	{
		array[j] = j;
		q_array[j] = array[j];
	}
	for (i = 0 ; i < 10 ; ++i)
	{
		start = clock();
		SelectionSort(array, ARRAY_SIZE, CmpFuncAscending);
		end = clock();
	
		time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		avg_time += time[i];
		
		start = clock(); 
		qsort(q_array, ARRAY_SIZE, sizeof(int), cmpfuncForQsort);
		end = clock();
		
		q_time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		q_avg_time += q_time[i];
	} 
	
	PRINT_TEST(TRUE == IsSameArr(array, q_array, ARRAY_SIZE));
	
	avg_time /= 10;
	q_avg_time /= 10;
	printf("Avarage time for my Selection sort(ascend order): %f\n", avg_time);
	printf("Avarage time for built-in qsort(ascend order): %f\n", q_avg_time);
}

static void TestCountingSort()
{
	clock_t start = 0;
	clock_t end = 0;
	double time[10] = {0};
	double q_time[10] = {0};
	int array[ARRAY_SIZE] = {0};
	int q_array[ARRAY_SIZE] = {0};
	size_t i = 0;
	size_t j = 0;
	int sort_check = SUCCESS;
	double avg_time = 0;
	double q_avg_time = 0;
	
	printf(U_LINE"\nCountingSort Test:\n"RESET);
	
	for (i = 0 ; i < 10; ++i)
	{
		for (j = 0 ; j < ARRAY_SIZE ; ++j)
		{
			array[j] = rand() % RANGE_SIZE + 1;
			q_array[j] = array[j];
		}
	
		start = clock();
		CountingSort(array, ARRAY_SIZE);
		end = clock();
	
		time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		avg_time += time[i];
		
		start = clock(); 
		qsort(q_array, ARRAY_SIZE, sizeof(int), cmpfuncForQsort);
		end = clock();
		
		q_time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		q_avg_time += q_time[i];
	} 
	avg_time /= 10;
	q_avg_time /= 10;
	/*
	printf("after sorting:\n");
	for (i = 0 ; i < ARRAY_SIZE; ++i)
	{
		printf("array[%ld] = %d\n", i, array[i]);
	}
	printf("q_arr after sorting:\n");
	for (i = 0 ; i < ARRAY_SIZE; ++i)
	{
		printf("array[%ld] = %d\n", i, q_array[i]);
	}
	*/
	for (i = 0 ; i < ARRAY_SIZE - 1; ++i)
	{
		if (array[i] > array[i + 1])
		{
			sort_check = FAILURE;
		}
	}
	
	PRINT_TEST(SUCCESS == sort_check);
	PRINT_TEST(TRUE == IsSameArr(array, q_array, ARRAY_SIZE));
		
	printf("Avarage time for my Counting sort(random order): %f\n", avg_time);
	printf("Avarage time for built-in qsort(random order): %f\n", q_avg_time);
	
	avg_time = 0;
	q_avg_time = 0;		
	
	for (j = 0; j < ARRAY_SIZE ; ++j)
	{
		array[j] = ARRAY_SIZE - j;
		q_array[j] = array[j];
	}

	for (i = 0 ; i < 10 ; ++i)
	{
		start = clock();
		CountingSort(array, ARRAY_SIZE);
		end = clock();
	
		time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		avg_time += time[i];
		
		start = clock(); 
		qsort(q_array, ARRAY_SIZE, sizeof(int), cmpfuncForQsort);
		end = clock();
		
		q_time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		q_avg_time += q_time[i];
	} 
	/*
		printf("Ten first indexes after sorting:\n");
	for (i = 0 ; i < 10; ++i)
	{
		printf("array[%ld] = %d\n", i, array[i]);
	}
	for (i = 0 ; i < 10; ++i)
	{
		printf("q_array[%ld] = %d\n", i, q_array[i]);
	}*/
	PRINT_TEST(TRUE == IsSameArr(array, q_array, ARRAY_SIZE));
		
	avg_time /= 10;
	q_avg_time /= 10;
	printf("Avarage time for my Counting sort(descend order): %f\n", avg_time);
	printf("Avarage time for built-in qsort(descend order): %f\n", q_avg_time);
	
	avg_time = 0;
	for (j = 0; j < ARRAY_SIZE ; ++j)
	{
		array[j] = j;
		q_array[j] = array[j];
	}
	for (i = 0 ; i < 10 ; ++i)
	{
		start = clock();
		CountingSort(array, ARRAY_SIZE);
		end = clock();
	
		time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		avg_time += time[i];
		
		start = clock(); 
		qsort(q_array, ARRAY_SIZE, sizeof(int), cmpfuncForQsort);
		end = clock();
		
		q_time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		q_avg_time += q_time[i];
		
	} 
	
	PRINT_TEST(TRUE == IsSameArr(array, q_array, ARRAY_SIZE));
	avg_time /= 10;
	q_avg_time /= 10;
	printf("Avarage time for my Counting sort(ascend order): %f\n", avg_time);
	printf("Avarage time for built-in qsort(ascend order): %f\n", q_avg_time);
}

static void TestRadixSort()
{
	clock_t start = 0;
	clock_t end = 0;
	double time[10] = {0};
	double q_time[10] = {0};
	int array[ARRAY_SIZE] = {0};
	int q_array[ARRAY_SIZE] = {0};
	size_t i = 0;
	size_t j = 0;
	int sort_check = SUCCESS;
	double avg_time = 0;
	double q_avg_time = 0;
	
	printf(U_LINE"\nRadixSort Test:\n"RESET);
	
	for (i = 0 ; i < 10; ++i)
	{
		for (j = 0 ; j < ARRAY_SIZE ; ++j)
		{
			array[j] = rand() % SEVEN_DIGIT_MAX + ONE_MIL;
			q_array[j] = array[j];
		}
	
		start = clock();
		RadixSort(array, ARRAY_SIZE);
		end = clock();
	
		time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		avg_time += time[i];
		
		start = clock(); 
		qsort(q_array, ARRAY_SIZE, sizeof(int), cmpfuncForQsort);
		end = clock();
		
		q_time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		q_avg_time += q_time[i];
		
	} 
	avg_time /= 10;
	q_avg_time /= 10;
	/*
	printf("after sorting:\n");
	for (i = 0 ; i < ARRAY_SIZE; ++i)
	{
		printf("array[%ld] = %d\n", i, array[i]);
	}
	printf("q_arr after sorting:\n");
	for (i = 0 ; i < ARRAY_SIZE; ++i)
	{
		printf("array[%ld] = %d\n", i, q_array[i]);
	}
	*/
	for (i = 0 ; i < ARRAY_SIZE - 1; ++i)
	{
		if (array[i] > array[i + 1])
		{
			sort_check = FAILURE;
		}
	}
	
	PRINT_TEST(SUCCESS == sort_check);
	PRINT_TEST(TRUE == IsSameArr(array, q_array, ARRAY_SIZE));
		
	printf("Avarage time for my Counting sort(random order): %f\n", avg_time);
	printf("Avarage time for built-in qsort(random order): %f\n", q_avg_time);
	
	avg_time = 0;
	q_avg_time = 0;		
	
	for (j = 0; j < ARRAY_SIZE ; ++j)
	{
		array[j] = ARRAY_SIZE - j;
		q_array[j] = array[j];
	}

	for (i = 0 ; i < 10 ; ++i)
	{
		start = clock();
		RadixSort(array, ARRAY_SIZE);
		end = clock();
	
		time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		avg_time += time[i];
		
		start = clock(); 
		qsort(q_array, ARRAY_SIZE, sizeof(int), cmpfuncForQsort);
		end = clock();
		
		q_time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		q_avg_time += q_time[i];
		
	} 
	/*
	printf("Ten first indexes after sorting:\n");
	for (i = 0 ; i < 10; ++i)
	{
		printf("array[%ld] = %d\n", i, array[i]);
	}
	for (i = 0 ; i < 10; ++i)
	{
		printf("q_array[%ld] = %d\n", i, q_array[i]);
	}
	*/
	PRINT_TEST(TRUE == IsSameArr(array, q_array, ARRAY_SIZE));
		
	avg_time /= 10;
	q_avg_time /= 10;
	printf("Avarage time for my Radix sort(descend order): %f\n", avg_time);
	printf("Avarage time for built-in qsort(descend order): %f\n", q_avg_time);
	
	avg_time = 0;
	for (j = 0; j < ARRAY_SIZE ; ++j)
	{
		array[j] = j;
		q_array[j] = array[j];
	}
	for (i = 0 ; i < 10 ; ++i)
	{
		start = clock();
		RadixSort(array, ARRAY_SIZE);
		end = clock();
	
		time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		avg_time += time[i];
		
		start = clock(); 
		qsort(q_array, ARRAY_SIZE, sizeof(int), cmpfuncForQsort);
		end = clock();
		
		q_time[i] = ((double)end - (double)start) / CLOCKS_PER_SEC;
		q_avg_time += q_time[i];
	} 
	
	PRINT_TEST(TRUE == IsSameArr(array, q_array, ARRAY_SIZE));
	avg_time /= 10;
	q_avg_time /= 10;
	printf("Avarage time for my Radix sort(ascend order): %f\n", avg_time);
	printf("Avarage time for built-in qsort(ascend order): %f\n", q_avg_time);
}

static void TestBinarySearch()
{
	
}

/******************************************************/

int CmpFuncAscending(const int lhs, const int rhs)
{
	return (lhs - rhs);	
}

int cmpfuncForQsort(const void *lhs, const void *rhs)
{
   return (*(int*)lhs - *(int*)rhs);
}

static int IsSameArr(int arr1[], int arr2[], size_t size)
{
	int is_same = TRUE;
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		if (arr1[i] != arr2[i])
		{
			is_same = FALSE;
			break;
		}
	}
	
	return is_same;
}

