
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
	
	if (NULL == dest || NULL == src)
	{
		exit (-1);
	}
	
	while ('\0' != *src)
	{
		*dest = *src;
		dest++;
		src++;
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
	
	for (i=1; i<=n; i++)
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
	
	return *s1 - *s2;
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
	int sum = 0;
	if (NULL == s1 || NULL == s2)
	{
		exit (-1);
	}

	while ('\0' != *s1 && '\0' != *s2)
	{
		sum += (((int)(tolower(*s1)))-((int)(tolower(*s2)))); 
		s1++;
		s2++;
	}	
	printf ("The sum lexicographically-wise is: %d \n", sum);
	return sum;
}

/* StrChr: function that search for the firs incaunter with a specific char.
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
		s++;
	}
	return (char *)s;
}  



