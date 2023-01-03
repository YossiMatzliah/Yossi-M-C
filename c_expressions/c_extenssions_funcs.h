
double TenExpN (int n)
{
	static int i;	
	double x=10, func_result=1;
	if (n<0)
	{
		n=-n;
		x=0.1;
	} 
	for (i=0; i<n; i++)
	{
		func_result *= x;
	}
	return func_result;
}


void swap_2_variables (int *num1, int *num2)
{
	static int temp;
	temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}
