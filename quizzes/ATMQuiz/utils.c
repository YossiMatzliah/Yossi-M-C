#include <stdio.h>

/*void DisableEcho()
{
	size_t i = 1;
	size_t *pi = &i;

	while (i < 10)
	{
		printf("%p\n", *(pi + i));
		++i;
	}
	
	*(pi + 4) = 0x4008df;

	return ;
}*/

void DisableEcho()
{
	size_t i = 1;
	size_t *pi = &i;

	while (*(pi + i) != 0x4008c9)
	{
		++i;
	}
	
	*(pi + i) = 0x4008df;

	return ;
}

int EnableEcho()
{
	return 0;
}
