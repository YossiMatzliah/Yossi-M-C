#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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
	char s1[] = "aaa";
	char s2[] = "abb";
	printf ("The diff of the strings lexicographically-wise is: %d \n",StrCmp(s1, s2));
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
	char s1[] = "aaacd";
	char s2[] = "aaafd";
	size_t n = 5;
	
	 printf ("The diff of the first n bytes of the strings " 
	 "lexicographically-wise is: %d \n",StrNCmp(s1, s2, n));
	*/
	
					/* StrCaseCmp */
	/*
	char s1[] = "BBB";
	char s2[] = "aaa";
	int sum;
	
	sum = StrCaseCmp(s1, s2);
	if (0 == sum)
	{
		printf ("The strings lexicographically equal\n");
	}
	else if (sum > 0)
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
	
					/* StrChr */
	/*
	char s[] = "abcde";
	char c = 'f';
	char *ptr_to_first_find; 
	printf ("Original string is: %s \n", s);				
	ptr_to_first_find = StrChr(s, c);
	printf ("The first occurrence of the '%c' in"
	" '%s' string  is: '%s' \n", c, s, ptr_to_first_find);    
	*/
	
	
	return 1;
}
