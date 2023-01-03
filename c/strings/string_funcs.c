
/* StrLen: return the length of a pointer */
size_t StrLen (const char *s)
{
	size_t counter = 0;
	if (NULL == s)
	{
		exit (-1);
	}
	while ('\0' != *s)
	{
		s++;
		counter++;
	}
	return counter;
}

/* StrCmp: function compares the two strings s1 and s2. 
   		Returns:
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
	while ('\0' != *s1 && '\0' != *s2)
	{
		s1++;
		s2++;
	}	
	if ('\0' == *s1 && '\0' == *s2)
	{
		return 0;
	}
	else if ('\0' == *s1)
	{
		return -1;
	}
	else 
	{
		return 1;		
	}
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


/* StrNCmp: function compares the first n bytes (amount)of two strings s1 and s2. 
   		Returns:
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
		s1++;
		s2++;
		if ('\0' == *s1 && '\0' != *s2)
		{		
			return -1;
		}
		else if ('\0' != *s1 && '\0' == *s2)
		{		
			return 1;
		}
	}
	return 0;	
} 





