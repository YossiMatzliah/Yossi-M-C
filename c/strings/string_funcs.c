
/* return the length of a pointer */
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


