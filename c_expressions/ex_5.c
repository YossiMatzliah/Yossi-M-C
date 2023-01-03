#include <stdio.h>
#include "c_extenssions_funcs.h"

int *p_num;
int num;
void FlipNum (int *num)
{
	size_t num_of_digits = 0;
	size_t i;
	size_t ch_num_dig;
	int result = 0;
	ch_num_dig = *num;
	while (!ch_num_dig)
	{
		ch_num_dig /= 10;
		num_of_digits++;	
	}
	for (i = 1; i <= num_of_digits; i++)
	{
		result += (*num/TenExpN(num_of_digits-i))*TenExpN(i-1);
		*num -= ((*num/TenExpN(num_of_digits-i))*TenExpN(num_of_digits-i));
	}
	printf ("The flipped number is: %d \n", result);
}



int main ()
{
	p_num = &num;
	printf ("Please enter an intiger: ");
	scanf ("%d", &num);
	FlipNum (&num);
	return 1;
}

