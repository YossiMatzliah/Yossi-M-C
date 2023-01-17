#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>


/* StrLen: return the length of a pointer */
size_t StrLen (const char *s)
{
	const char *ptr = s;
	
	if (NULL == s)
	{
		exit (-1);
	}
	
	while ('\0' != *s)
	{
		s++;
	}
	return s - ptr;
}

/* StrCmp: function compares two strings s1 and s2 lexicographically-wise. 
   		Returns for each iteration:
   • 0, if the s1 and s2 are equal;
   • a negative value if s1 is less than s2;
   • a positive value if s1 is greater than s2.
*/
int StrCmp(const char *s1, const char *s2)
{
	if (NULL == s1 || NULL == s2)
	{
		exit (-1);
	}	 
	
	while ('\0' != *s1 && '\0' != *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}	
	
	return *s1 - *s2;
}

/* StrCpy: function coppies string source to destination. */

char *StrCpy (char *dest, const char *src)
{
	char *dest_holder = dest; 
	
	/* user responsabilty? do I need it? */ 
	if (NULL == dest || NULL == src)
	{
		exit (-1);
	}
	
	while ('\0' != *src)
	{
		*dest = *src;
		++dest;
		++src;
	}
	
	*dest = '\0';
	return dest_holder;
	
}
 
/* StrNCpy: function coppies n bytes (amount) of characters from 
string source to destination. */

char *StrNCpy(char *dest, const char *src, size_t n)
{
	char *dest_holder = dest;
	size_t i;
	
	if (NULL == dest || NULL == src)
	{
		exit (-1);
	}
	
	for (i = 1; i <= n; i++)
	{
		
		if ('\0' != *src)
		{
			*dest = *src;
			dest++;
			src++;
		}
		
		else
		{
			*dest = *src;
			dest++;
		}
	}
	
	/*not programmer problem, but want to make code work in extreme cases*/
	if ('\0' != *(dest-1))
	{
		printf ("WARNING: dest is ended without null-terminator\n");
	}
	
	return dest_holder;
}


/* StrNCmp: function compares the first n bytes (amount)of 
two strings s1 and s2 lexicographically-wise. 
   		Returns for each iteration:
   • 0, if the s1 and s2 are equal;
   • a negative value if s1 is less than s2;
   • a positive value if s1 is greater than s2.
*/
int StrNCmp(const char *s1, const char *s2, size_t n)
{
	size_t i;
	
	if (NULL == s1 || NULL == s2)
	{
		exit (-1);
	}
	
	for (i=1; i<=n; i++)
	{
		
		if (*s1 == *s2)
		{ 
			s1++;
			s2++;
		}
	}	
	if (0 == (*s1 - *s2))
	{	
		return 0;
	}
	else if ((*s1 - *s2) > 0)
	{	
		return 1;
	}
	else
	{	
		return -1;
	}
} 

/* StrCaseCmp: function compares two strings s1 and s2 lexicographically-wise
   while upper-case are lowered to low-case
   		Returns for each iteration:
   • 0, if the s1 and s2 are equal;
   • a negative value if s1 is less than s2;
   • a positive value if s1 is greater than s2.
*/
int StrCaseCmp(const char *s1, const char *s2)
{
	
	if (NULL == s1 || NULL == s2)
	{
		exit (-1);
	}

	while ('\0' != *s1 && '\0' != *s2 && *s1 == *s2)
	{
		if (tolower(*s1) == tolower(*s2)) 
		{
			s1++;
			s2++;
		}
	}	
	
	return tolower(*s1) - tolower(*s2);
}

/* StrChr: function that search for the first incaunter with a specific char.
	returns:
	• if finds: pointer to the first incaunter;
    • if don't: NULL;
*/
char *StrChr (const char *s, int c)
{
	if (NULL == s)
	{
		exit (-1);
	}
	while (*s != (char) c) 
	{
		if ('\0' == *s)
		{
			printf ("The char wasn't found");
			return NULL;
		}
		++s;
	}
	return (char *)s;
}  

/* StrDup: function that duplicate a string to new allocated memory address.
	returns:
	pointer to the new allocated copy  
*/
char *StrDup(const char *s)
{
	size_t len = 0;
	char *dup;
	
	len = 1 + StrLen (s); /* +1 for null-terminator */
	dup = (char *)(malloc (len));

	if (NULL == dup)
	{
		exit (-1);
	}
	 
	return StrCpy (dup, s); 
}

/*  StrCat: function that appends a string from source to dest, 
	overwrite null-terminator.
	returns:
	pointer to the resulting string dest
*/
char *StrCat(char *dest, const char *src)
{	
	char *dest_holder = dest;
	
	while ('\0' != *dest)
	{
		dest++;
	}
	
	StrCpy (dest, src);
	
	return dest_holder;
}

/*  StrNCat: function that appends the first n bytes from a string 
	of source to dest, overwrite null-terminator.
	returns:
	pointer to the resulting string dest
*/
char *StrNCat(char *dest, const char *src, size_t n)
{	
	char *dest_holder = dest;
	
	while ('\0' != *dest)
	{
		dest++;
	}
	
	StrNCpy (dest, src, n);
	
	return dest_holder;
}


/*  StrStr: function finds the first occurrence of the substring needle
	in the string haystack.  The terminating null bytes ('\0')
    are not compared.
    return a pointer to the beginning of the located substring, 
    or NULL if the substring is not found  
*/       
char *StrStr(const char *haystack, const char *needle)
{
	size_t needle_len = 0;
	
	needle_len = StrLen (needle); 
	 
	while ('\0' != *haystack)
	{
		while (*needle == *haystack)
		{
			++haystack;
			++needle;
			if('\0' == *needle)
			{
				return (char *)haystack - needle_len; 
				/* -needle_len cause we want the address of the
				   beginning of the located substring */
			}
		}
		++haystack;
	}
	printf ("The substring wasn't found on the haystack \n");
	return NULL;

}

/*  The function calculates the length (in bytes) of the initial 
	segment of s which consists entirely of bytes in accept.
	returns the number of bytes in the initial segment
	of s which consist only of bytes from accept
*/
size_t StrSpn(const char *s, const char *accept)
{
	const char *runner = s;
	
	while( '\0' != *runner && StrChr (accept, *runner) )
    {
    	++runner;
    }
  
    return runner - s;
}




