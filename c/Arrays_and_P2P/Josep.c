#include <stdio.h> /* for printf */

#define SIZE 5

void JosephusTest ();
size_t IsX (size_t i, int arr[], size_t size, int x);
size_t Josephus (int soldier[], size_t size)

int main ()
{
	JosephusTest ();
	
	return 0;
}

void JosephusTest ()
{
	int soldiers[SIZE] = {1};
	size_t size = SIZE - 1;
	size_t i = 0;
	
	for (i = 0; i <= size; i++) 
	{   
    	soldiers[i] = 1;
	}
	
	printf ("The last man standing is: %ld \n ", Josephus (soldiers, size));
}


size_t IsX (size_t i, int arr[], size_t size, int x)
{
	size_t holder = i;
	size_t flag = 0;
	
	while (++i <= size) 
	{
		if (i == holder && 1 == flag)
    	{
    		return i;
    	}
		
		if (x == arr[i] && i != holder)
		{
    		printf ("entered IsX and i =  %ld \n", i);
    		return i;
    	}
    
    	else if (i >= size && 0 == flag) 
    	{
    		i = 0;
    		flag = 1;
    	}
	}
	return i;
}


size_t Josephus (int soldier[], size_t size)
{
	size_t i, holder = 0;

	do
	{
		holder = i;
		if (holder != IsX (i, soldier, size, 1))
		{
			soldier[i] = 0;
			printf ("entered IsX and now soldier [%ld] = %d \n", i, soldier[i]);
			i = IsX (i, soldier, size, 1);
		}
	} while (i != holder);
		
	return i;	
}
