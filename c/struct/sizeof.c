#include <stdio.h>

int main()
{
	struct x 
	{
		int i;
		char c;
		double d;
		short s;
	} struct_x;
	
	printf("The size of qu b is: %ld\n", sizeof(struct_x));
	return 0;
}
