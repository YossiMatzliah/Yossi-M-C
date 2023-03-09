#include <stdio.h>	/* printf */

#define PRINT printf("\033[1;32msuccess\n\033[0m") : printf("\033[1;31mfail\n\033[0m")

size_t NumRotations(int a[], size_t len)
{
	size_t count = 0;
	int i = 0;
	
	if (a[0] > a[len - 1])
	{
		++count;
		
		while (a[i] < a[i + 1])
		{
			++i;
			++count;
		}
	}
	
	return (len - count) % len;
}

int main()
{
	int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int b[5]  = {1, 2, 3, 4, 5};
	int c[7]  = {7, 1, 2, 3, 4, 5, 6};
	int d[3]  = {3, 1, 2};
	int e[5]  = {3, 4, 5, 1, 2};
	int f[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 1};
	
	0 == NumRotations(a, 10) ? PRINT;
	0 == NumRotations(b, 5)  ? PRINT;
	6 == NumRotations(c, 7)  ? PRINT;
	2 == NumRotations(d, 3)  ? PRINT;
	2 == NumRotations(e, 5)  ? PRINT;
	1 == NumRotations(f, 10) ? PRINT;
	
	return 0;
}	

