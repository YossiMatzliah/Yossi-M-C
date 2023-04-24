#include <stdio.h>  


int main() 
{ 
	int i;  
	int a[4] = {25, 16}; 
	
	printf("Part I:\n");
	
	for (i = 0; i < 5; i++)
	{ 
		int i = 10; 
		printf (" %d", i);       
		i++;  
	}  
	
	printf("\n\n\nPart II:\n");
	printf ("%d %d\n\n", a[0] & a[1], a[1] | a[2]); 
	
	return 0;  
} 

