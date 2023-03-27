/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Oran  				*
*	Date      : 14/03/2023			*
************************************/

#include <assert.h> 	/* asserts */
#include <limits.h> 	/* INT_MIN, INT_MAX */ 
#include <stdlib.h> 	/* calloc, free */

#include "sort.h"

#define FAILURE (1)
#define SUCCESS (0)
#define TEN_BASE (10)

/************** static func *****************/

static int CountingSortForRadix(int array[], size_t size, int base);

/********************************************/

void BubbleSort(int array[], size_t size, int (*cmp_func)(const int lhs, const int rhs))
{
	size_t i = 0;
	int temp = 0;
	size_t j = 0;
	
	assert(NULL != array);
	
	--size;
	for (j = 0; j < size; ++j)
	{
		for (i = 0; i < size - j; ++i)
		{
			if (0 < cmp_func(array[i], array[i + 1]))
			{
				temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
			}
		}
	}
}

void InsertionSort(int array[], size_t size, int (*cmp_func)(const int lhs, const int rhs))
{
    size_t i = 0;
    int temp = 0;
    size_t j = 0;
    
	assert(NULL != array);

    for (i = 1 ; i < size ; ++i)
    {
        j = i;
        temp = array[i];
        while (j > 0 && cmp_func(temp, array[j - 1]) < 0)
        {
            array[j] = array[j - 1];
            --j;
        }
        array[j] = temp;
    }
}

void SelectionSort(int array[], size_t size, int (*cmp_func)(const int lhs, const int rhs))
{
	size_t i = 0;
	size_t j = 0;
	int temp = 0;
	
	assert(NULL != array);
	
	for (i = 0; i < size - 1; ++i)
	{
		for (j = i + 1; j < size; ++j)
		{
			if (0 < cmp_func(array[i], array[j]))
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
}

int CountingSort(int array[], size_t size)
{
	int *index_arr = NULL;
	int min_num = INT_MAX;
	int max_num = INT_MIN;
	size_t diff = 0;
	size_t i = 0;
	size_t count_ind = 0;
	
	assert(NULL != array);
	
	for (i = 0; i < size; ++i)
	{
		if (min_num > array[i])
		{
			min_num = array[i];
		}
		
		if (max_num < array[i])
		{
			max_num = array[i];
		}
	}
	
	diff = max_num - min_num;
	
	index_arr = (int *)calloc(diff, sizeof(int) * diff);
	if (NULL == index_arr)
	{
		return FAILURE;
	}
	
	for (i = 0; i < size; ++i)
	{
		++index_arr[array[i] - min_num];
	}
	
	i = 0;
	
	while (count_ind <= diff)
	{
		while (index_arr[count_ind] > 0)
		{
			array[i] = count_ind + min_num;
			--index_arr[count_ind];
			++i; 
		}
		
		++count_ind;
	}
	
	free(index_arr);
	
	return SUCCESS;
}

int RadixSort(int array[], size_t size)
{
	size_t num_of_bases = 0;
	size_t i = 0;
	size_t base = 1;
	int max_num = INT_MIN;
	int status = SUCCESS;
	
	assert(NULL != array);
	
	for (i = 0; i < size; ++i)
	{
		if (max_num < array[i])
		{
			max_num = array[i];
		}
	}
	
	do
	{
		++num_of_bases;
		max_num /= TEN_BASE;
	} while (0 != max_num);
	
	for (i = 0; i < num_of_bases && SUCCESS == status; --num_of_bases)
	{
		status = CountingSortForRadix(array, size, base);
		base *= TEN_BASE;
	}
	
	return status;
}

ssize_t BinarySearchIterative(int *arr, size_t size, int num)
{
	int middle = size;
	
	while (0 != middle)
	{
		if (*(arr + middle) == num)
		{
			return middle;
		}
		
		else if (*(arr + middle) > num)
		{
			
		} 
	}
}

/*********************************************************************/
	
static int CountingSortForRadix(int array[], size_t size, int base)
{
	size_t i = 0;
	int *sort_arr = NULL;
	int *cur_base_arr = NULL;
	size_t index = 0;
	
	cur_base_arr = (int *)calloc(TEN_BASE, sizeof(int) * TEN_BASE);
	sort_arr = (int *)calloc(size, sizeof(int) * size);
	
	if (NULL == sort_arr || NULL == cur_base_arr)
	{
		return FAILURE;
	} 
	
	for (i = 0; i < size; ++i)
	{
		++cur_base_arr[((array[i] / base) % TEN_BASE)];
	}
	
	for (i = 1; i < TEN_BASE; ++i)
	{
		cur_base_arr[i] += cur_base_arr[i - 1];
	}
	
	for (i = size - 1; i > 0 ; --i)
	{
		index = ((array[i] / base) % TEN_BASE);
		index = cur_base_arr[index] - 1;
		sort_arr[index] = array[i];
		--cur_base_arr[(array[i] / base) % TEN_BASE];
	}
	
	index = ((array[i] / base) % TEN_BASE);
	index = cur_base_arr[index] - 1;
	sort_arr[index] = array[i];
		
	for (i = 0; i < size; ++i)
	{
		array[i] = sort_arr[i];
	}
	
	free(cur_base_arr);
	free(sort_arr);

	return SUCCESS;
}
