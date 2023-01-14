#include <stdio.h> /* for printf */
#include<assert.h> /* for assert */
#include <ctype.h> /* for tolower */
#include <string.h> /* for strlen , strcpy */
#include <stdlib.h> /* for malloc */
#include "Arrays_and_P2P.c"
#define SIZE 100


void SumOfEachRowTest ();
void JosephusTest ();
void EnvVariableToLowerCopy(char **envp);
char **StrCpyLow (char **dest, char **src, size_t count);
void PrintStr (char **dest, size_t count);
void ToLower (char *dest, char *src);
void CleanUp (char **dest, size_t count);

int main (int argc, char **argv, char **envp)
{
	SumOfEachRowTest (); 
	PrintDataType();
	JosephusTest ();
	EnvVariableToLowerCopy(envp);
	
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
	size_t soldiers[SIZE] = {0};
	size_t size = SIZE;
	size_t i = 0;
	
	for (i = 0; i < size; i++) 
	{   
    	soldiers[i] = i + 1;
	}
	soldiers[size - 1] = 0;
	
	printf ("The last man standing index is: %ld \n" 
	"Congrats!\n ", Josephus (soldiers));
}




