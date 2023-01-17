#include "string_funcs.h"

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
	
	char s1[] = "Hello";
	char s2[] = "Helghnj";
	size_t n = 5;
	int res = 0;
	
	res = StrNCmp(s1, s2, n);
	if (res > 0)
	{	
	printf ("The first string within the first n bytes of the strings " 
	"lexicographically-wise greater \n");
	}
	else if (res < 0)
	{	
	printf ("The first string within the first n bytes of the strings " 
	"lexicographically-wise less \n");
	}
	else
	{	
	printf ("The first string within the first n bytes of the strings " 
	"lexicographically-wise equal \n");
	}
					
					/* StrCaseCmp */
	/*
	char s1[] = "aaa";
	char s2[] = "abb";
	printf ("The diff of the strings lexicographically-wise"
	" without key-sensetive is: %d \n",StrCaseCmp(s1, s2));
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
	
	/* StrDup */
	/*
	char s[] = "abcd";
	char *duplicated;
	printf ("The source address is %p and the string is %s \n", s, s);
	duplicated = StrDup (s);
	printf ("The duplicated address is %p and the copied string is %s \n", duplicated, duplicated);
	free (dup);
	*/
	
	/* StrCat */
	/*
	char s[] = "abcd";
	char dest[100]= "dest is ";
	
	printf ("The source address is: %p and the string is: %s \n", s, s);
	printf ("The dest address before was: %p and the string was: %s \n", dest, dest);
	printf ("The new dest string is: %s \n", StrCat (dest, s));
	*/
	
		/* StrNCat */
	/*
	char s[] = "abcd";
	char dest[100]= "dest is ";
	size_t n = 3;
	
	printf ("The source address is: %p and the string is: %s \n", s, s);
	printf ("The dest address before was: %p and the string was: %s \n", dest, dest);
	printf ("The new dest string is: %s \n", StrNCat (dest, s, n));
	*/
	
	/* StrStr */
	/*
	char haystack[] = "aadabuhku";
	char needle[] = "ab";
	
	printf("The address of haystack pointer is: %p \n", haystack);
	printf("The address of haystack pointer is: %p \n", StrStr (haystack, needle));
	*/
	
	
	/* StrSpn */
	/*
	char *source = "dammn, this!";
    char *accept = "damnn,";
    
    size_t length = StrSpn(source, accept);
    
    printf("The length segment of s which consiststing" 
    " the characters in accept = %ld \n", length);
	*/
	
	return 0;
}
