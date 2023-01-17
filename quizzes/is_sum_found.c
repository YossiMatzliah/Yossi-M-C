#include <stdio.h>
#include <stdlib.h>
#define SIZE 5


void *IsSumFound (int sorted_arr[], int sum, int size, int *result)
{
	int i = 0; int start_count = 0; int end_count = 0;
	int *begin = sorted_arr;
	int *end = (sorted_arr + (size - 1));
	result = malloc(12);
    
    if (result == NULL)
    {
		return NULL;
	}
	
	for (i = 0; i < size; ++i)
	{
		
		if (*begin + *end == sum)
		{
			*result = 1;
			*(result + 1) = start_count;
			*(result + 2) = size - end_count;
			return result;
		}
		
		else if (*begin + *end > sum)
		{
			--end;
			++end_count;
		}
		
		else
		{
			++begin;
			++start_count;
		}
	}
	
	printf ("sum not found\n");
	return result;
}


int main ()
{
	int size = SIZE;
	int arr[SIZE] = {2,4,7,12,14};
	int sum = 21;
	int *result = NULL;
	
	result = IsSumFound (arr, sum, size, result);
	
	printf ("The sum was found? %d\n Index 1" 
	"is: %d\n Index 2 is: %d\n", *result, *(result + 1), *(result + 2));
	
	free (result);
	return 0;
}
