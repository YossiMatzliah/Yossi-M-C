/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Oran  				*
*	Date      : 28/03/2023			*
************************************/

#include <assert.h> 	/* asserts */
#include <limits.h> 	/* INT_MIN, INT_MAX */ 
#include <stdlib.h> 	/* calloc, free */
#include <string.h>		/* mmove */

#include "sort.h"

#define FAILURE 	(1)
#define SUCCESS 	(0)
#define TEN_BASE 	(10)
#define WORD_SIZE 	(sizeof(size_t))
#define NOT_FOUND	(-1)

/************** static func *****************/

static int CountingSortForRadix(int array[], size_t size, int base);
static int MergeSortRec(int arr[], size_t low, size_t high);
static int Merge(int arr[], size_t low, size_t mid, size_t high);
static void SwapVoid(void *data1, void *data2, size_t elem_size);
static void QsortRec(void *base, size_t size, int low, int high, int (*compar)(const void *, const void *));
static size_t Partition(void *base, size_t size, int low, int high, int (*compar)(const void *, const void *));

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
	int *middle = NULL;
	int *left = NULL;
	int *right = NULL;
	
	assert(NULL != arr);
	
	left = arr;
	right = arr + size - 1;	 
	
	while (left <= right)
	{
		middle = left + ((right - left) / 2);
		 
		if (*middle == num)
		{
			return (int)(middle - arr);
		}
		
		else if (*middle < num)
		{
			left = middle + 1;
		}
		
		else
		{
			right = middle - 1;
		} 
	}
	
	return NOT_FOUND;
}

ssize_t BinarySearchRecursive(int *arr, size_t size, int num)
{
	size_t middle = size / 2;
	ssize_t res = 0;
	
	assert(NULL != arr);
	
	if (size == 0)
	{
		return NOT_FOUND;
	}
	
	if (arr[middle] == num)
	{
		return middle;
	}
	
	else if (arr[middle] < num)
	{
		res = BinarySearchRecursive(arr + middle + 1, middle, num);
		
		if (-1 == res)
		{
			return NOT_FOUND;
		}
		else
		{
			return middle + res + 1;
		}
	}
	
	else
	{
		return BinarySearchRecursive(arr, middle, num);
	}
	
	return NOT_FOUND;
}

int MergeSort(int *arr_to_sort, size_t num_elements)
{
	assert(NULL != arr_to_sort);
	
	return MergeSortRec(arr_to_sort, 0, num_elements - 1);
}

void Qsort(void *base, size_t num_elements, size_t size, int (*compar)(const void *, const void *))
{
	QsortRec(base, size, 0, (int)num_elements - 1, compar);
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

static int MergeSortRec(int arr[], size_t low, size_t high)
{
	size_t mid = 0;
	
	if (low < high)
	{
		mid = low + (high - low) / 2;
		
		MergeSortRec(arr, low, mid);
		
		MergeSortRec(arr, mid + 1, high);
		
		return (Merge(arr, low, mid, high));
	}
	return SUCCESS;
}

static int Merge(int arr[], size_t low, size_t mid, size_t high)
{
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	size_t left_len = mid - low + 1;
	size_t right_len = high - mid;
	
	int *temp_left = malloc(left_len * sizeof(int));
	int *temp_right = malloc(right_len * sizeof(int));

	if (NULL == temp_right || NULL == temp_left)
	{
		free(temp_left);
		free(temp_right);
		return FAILURE;
	}
	
	for (i = 0; i < left_len; i++)
	{
		temp_left[i] = arr[low + i];
	}

	for (i = 0; i < right_len; i++)
	{
		temp_right[i] = arr[mid + 1 + i];
	}
	
	/*merge arrays*/
	for (i = 0, j = 0, k = low; k <= high; ++k)
	{
		if ((i < left_len) && (j < right_len))
		{
			if (temp_left[i] <= temp_right[j])
			{
				arr[k] = temp_left[i];
				i++;
			}
			else
			{
				arr[k] = temp_right[j];
				j++;
			}
		}
		else if (i < left_len)
		{
			arr[k] = temp_left[i];
			++i;
		}
		else if (j < right_len)
		{
			arr[k] = temp_right[j];
			++j;
		}
	}
  
	free(temp_left);
	free(temp_right);
  
	return SUCCESS;   
}

static void QsortRec(void *base, size_t size, int low, int high, int (*compar)(const void *, const void *))
{	
	int pivot = 0;

	if (low < high)
	{
		pivot = Partition(base, size, low, high, compar);

		QsortRec(base, size, low, pivot - 1, compar);
		QsortRec(base, size, pivot + 1, high, compar);
	}
}

static size_t Partition(void *base, size_t size, int low, int high, int (*compar)(const void *, const void *))
{
	int pivot = high;
	int i = low;
	int j = low;
	char *base_ptr = (char*)base;

	for (i = low; i < high; ++i)
	{
		if (0 >= compar((base_ptr + (i * size)), (base_ptr + (pivot*size))))
		{
			SwapVoid((base_ptr + (i * size)), (base_ptr + (j * size)), size);		
			++j;
		}
	}
	SwapVoid((base_ptr + ((j) * size)), (base_ptr + (high * size)), size);
	
	return j;
}

static void SwapVoid(void *data1, void *data2, size_t elem_size)
{
	char temp_buffer[WORD_SIZE] = {0};
		
	memmove(temp_buffer, data1, elem_size);
	memmove(data1, data2, elem_size);
	memmove(data2, temp_buffer, elem_size);
}

