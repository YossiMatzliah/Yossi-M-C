#include <stdio.h>
#include <stdlib.h>
#include "ex_functions.c"
#include "swapint.c"
#include "swap.c"


int main()
{
	
	/*	check ex_1 */
	/*
	int num, num_2;
	printf ("Please enter an intiger: ");
	scanf ("%d", &num);
	printf ("Please enter another intiger: ");
	scanf ("%d", &num_2);
	*/
	/*Swap2Variables (&num, &num_2);*/ 
	/*
	swap (&num, &num_2);
	printf("Num1 is now : %d \nNum2 is now : %d \n", num, num_2);
	*/
	
	
	
	/*	check ex_2  */
	/*
	int i;
	int arr[] = {6,24,3,14,65};
	int *arr_copy = ArrayCopy(arr, 5);
	for (i = 0; i < 5; i++)
	{
		printf("arr[%d]=%d\n", i, arr[i]);
    	printf("arr_copy[%d]=%d\n", i, arr_copy[i]);
	}
	*/
	/* free the dynamically allocated memory when we are done using it */
	/*
	free(arr_copy);
	*/
	
	
	/*	check ex_3  */
	/*
	int i_arr[] = {6,24,3,14,65}; 
	size_t t_arr[] = {1,3,3,1,4};
	unsigned int ui_arr[] = {4,4,3,4,5};
	char c_arr[] = {'c','o','d','e','\0'};
	PrintArrayAddresses (i_arr);
	PrintArrayAddresses (t_arr);
	PrintArrayAddresses (ui_arr);
	PrintArrayAddresses (c_arr);
*/
	
	
	/*	check ex_4aa  */
	/*
	size_t num, num_2;
	printf ("Please enter an intiger: ");
	scanf ("%lu", &num);
	printf ("Please enter another intiger: ");
	scanf ("%lu", &num_2);
	SwapTwoSizeTVariables (&num, &num_2); 
	printf("Num1 is now : %li \nNum2 is now : %li \n", num, num_2);
	*/
	
	/*	check ex_4ab  */
	/*
	size_t num, num_2, *p_num, *p_num_2;
	printf ("Please enter an intiger: ");
	scanf ("%lu", &num);
	printf ("Please enter another intiger: ");
	scanf ("%lu", &num_2);
	p_num = &num;
	p_num_2 = &num_2;
	SwapTwoSizeTPointers (&p_num, &p_num_2); 
	printf("Num1 is now : %p \nNum2 is now : %p \n", &p_num, &p_num_2); 
	*/
	
	return 0;
}
