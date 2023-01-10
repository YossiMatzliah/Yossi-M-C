#include <stdio.h> /* for printf */
#include "Arrays_and_P2P.c"
#define SIZE 5


void SumOfEachRowTest ();

void JosephusTest ();



int main ()
{
	SumOfEachRowTest (); 
	PrintDataType();
	JosephusTest ();
	
	return 0;
}


void SumOfEachRowTest ()
{
	int two_d_arr[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
	int result[] = {0,0,0};
	size_t temp_i = 0, r = 2 , c = 2; 
	
	SumOfEachRow (r, c, two_d_arr, result);
	
	for (temp_i = 0; temp_i <= r; temp_i++)
	{
		printf ("The sum of each row is: row[%ld] = %d \n", temp_i, result[temp_i]);
	}
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

