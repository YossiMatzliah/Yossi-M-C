#include <stdio.h>
#include "c_extenssions_funcs.h"

int num, num_2;

int main ()
{
	printf ("Please enter an intiger: ");
	scanf ("%d", &num);
	printf ("Please enter another intiger: ");
	scanf ("%d", &num_2);
	swap_2_variables (&num, &num_2);
	printf("Num1 is now : %d \nNum2 is now : %d \n", num, num_2);
	return 1;
}


