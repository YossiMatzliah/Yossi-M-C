#include <stdio.h>

int MaxSubArray(int a[], size_t len, int *ptr_left, int *ptr_right)
{
	size_t i = 0;
	int left = 0;
	int right = 0;
	int best_sum = a[0];
	int delta_left = a[0];
	int delta_right = 0;
	
	for (i = 1; i < len; ++i)
	{
		
		delta_right += a[i];
		
		if (delta_right > 0)
		{
			right = i;
			best_sum += delta_right;
			delta_right = 0;
		}
		if (delta_left < 0)
		{
			left = i;
			best_sum = best_sum - delta_left;
			delta_left = 0;
		}
		
		delta_left += a[i];
		printf("(%d, %d), sum = %d\n", left, right, best_sum);
	}

	*ptr_left = left;
	*ptr_right = right;
	return best_sum;
}

int main()
{
	int right = 0;
	int left = 0;
	int i = 0;
	int arr[9] = {10, 1, -3, 4, -1, 2, 3, -4, 4};
	int max_sum = MaxSubArray(arr, 9, &left, &right);
	
	printf ("\nThe arr is: \n");
	
	for (i = 0; i < 9; ++i)
	{
		printf("%d, ", arr[i]);
	}
	
	printf("\nstart: %d, finish: %d, sum = %d\n", left, right, max_sum);
	
	return 0;
}

