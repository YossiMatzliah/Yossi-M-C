#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/*  ex_1 swap two ints (values)	*/
void Swap2Variables (int *num1, int *num2)
{
	int temp;
	if (NULL == num1 && NULL == num2)
		exit (-1);
	temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

/* ex_2 creates a copy of the array of the given length on the heap */
int *ArrayCopy (int *array, int length)
{
	int i;
	/* creates space in memory to store the copy */
	int *c = (int *)malloc(length * sizeof(int));
	if (NULL == array)
		exit (-1);

	/* copy the values of the original array into the copy */
	for (i = 0; i < length; i++)
    {	
    	c[i] = array[i];
	}
	/* returns the pointer to the copy */
	return c;
}

/* ex_3 print array's addresses */

void PrintArrayAddresses (void *array)
{
	if (NULL == array)
		exit (-1);
	printf ("The address of this array is: %p \n", array); 
}



/* ex_4aa swap two size_t */
void SwapTwoSizeTVariables (size_t *num1, size_t *num2)
{
	size_t temp = 0;
	if (NULL == num1 || NULL == num2)
		exit (-1);
	temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}


/* ex_4ab swap two size_t pointers */

void SwapTwoSizeTPointers (size_t **num1, size_t **num2)
{
	size_t *temp;
	temp = *num1;
	*num1 = *num2;
	*num2 = temp;

}


