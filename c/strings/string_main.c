#include <stdio.h>
#include <stdlib.h>
#include "string_funcs.c"


int main ()
{
				/* StrLen */
	/*
	const char string[] = "Damn";	
	printf("The string length is: %li \n", StrLen(string) );	
	*/
	
				/* StrCmp */
	/*
	char s1[] = "damn";
	char s2[] = "right";
	int result;
	
	result = StrCmp(s1, s2);
	if (0 == result)
	{
		printf ("The strings lexicographically equal\n");
	}
	else if (result > 0)
	{
		printf ("The first string is lexicographically greater"
		" than the second\n"); 
	}	
	else
	{
		printf ("The first string is lexicographically less" 
		" than the second\n");
	}
	*/
	
				/* StrCpy */
	/*
	char src[] = "damn";
	char dest[] = "righ";
	printf ("The coppied string is: %s \n", StrCpy (dest, src));
	*/
	
				/* StrNCpy */
	/*
	char src[] = "damn ";
	char dest[] = "it's very hard";
	size_t n = 6;
	printf ("The coppied string is: %s \n", StrNCpy (dest, src, n));
	*/
	
	
				/* StrNCmp */
	/*
	char s1[] = "damn I'm so";
	char s2[] = "right";
	size_t n = 6;
	int result;
	result = StrNCmp(s1, s2, n);
	if (0 == result)
	{
		printf ("The first n bytes of the strings lexicographically equal\n");
	}
	else if (result > 0)
	{
		printf ("The first n bytes of the first string is "
		"lexicographically greater than the second\n"); 
	}	
	else
	{
		printf ("The first n bytes of the first string is "
		"lexicographically less than the second\n");
	}
	*/
	
	return 1;
}
