#include <stdio.h>

int main ()
{
	double d = 5; float f = 8/6; int i = 12; unsigned int ui = 2;
	
	i = d / f + i * (ui - i);
	printf ("%d\n", i);

	return 1;
}
