#include <stdio.h>

int n;

static void TenExpN (int n)
{
	int i;	
	double x=10, result=1;
	if (n<0)
	{
		n=-n;
		x=0.1;
	} 
	for (i=0; i<n; i++)
	{
		result *= x;
	}
	printf("The answer is: %f \n", result);

}


int main ()
{
	
	printf("Please enter an exponent integer: ");
	scanf ("%d", &n);
	TenExpN (n);

	return 1;
}
