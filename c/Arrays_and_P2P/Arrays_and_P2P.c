



/*
print all data types sizes
*/
void PrintDataType ()
{
	printf("Data type of unsigned char %ld\n", sizeof(unsigned char));
	printf("Data type of char %ld\n", sizeof(char));
	printf("Data type of unsigned int %ld\n", sizeof(unsigned int));
	printf("Data type of int %ld\n", sizeof(int));
	printf("Data type of unsigned short int  %ld\n", sizeof(unsigned short int));
	printf("Data type of short int %ld\n", sizeof(short int));
	printf("Data type of unsigned long int %ld\n", sizeof(unsigned long int));
	printf("Data type of long double %ld\n", sizeof(long double));
	printf("Data type of double %ld\n", sizeof(double));
	printf("Data type of float %ld\n", sizeof(float));
}


void SumOfEachRow (size_t r, size_t c, int arr[][3], int *result)
{
	size_t i,j = 0;
	
	for (i = 0; i <= r; i++)
	{
		
		for (j = 0; j <= c; j++)
		{
			result [i] += arr[i][j];	
		}
		
	}
}

size_t Josephus (size_t soldier[])
{
	size_t i = 0;
	while (soldier[i] != i)
	{ 
		soldier[i] = soldier[soldier[i]];
		i = soldier[i];	
	}	
	return i;	
}

void AllocNew(char **dest, char **envp, size_t count)
{
	size_t i = 0;
	
	for (i = 0; i < count; i++)
	{
		*dest = (char*)malloc((strlen(*envp) + 1) * sizeof(char));
		if (NULL == dest)
		{
			return;
		}
		
		*dest = strcpy(*dest, *envp);
		++envp;
		++dest;
	}
}

void ToLower(char *dest, char *src)
{
	size_t i = 0;
	size_t size = strlen(src);
	
	for (i = 0; i < size; ++i)
	{
		dest[i] = tolower(src[i]);
	}
}

char **StrCpyLow (char **dest, char **src, size_t count)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	while (count)
	{
		ToLower(*dest, *src);
		++dest;
		++src;
		--count;
	}
	
	return dest;
}

void PrintLowCaseEnv (char **dest, size_t count)
{
	size_t i = 0;
	
	for (i = 0; i < count; i++)
	{
		printf("%s\n", *dest);
		++dest;
	}
}

void CleanUp (char **dest, size_t count)
{
	size_t i = 0;
	
	free(*(dest + i));
	
	for (i = 1; i < count; i++)
	{
		free(*(dest + i));
	}
	free(dest);
}

void EnvVariableToLowerCopy (char **envp)
{
	size_t count = 0;
	char **low_case_env = NULL;
	char **buffer = envp;
	
	while (0 != *buffer)
	{
		++count;
		++buffer;
	}
	
	low_case_env = (char**)malloc(count * sizeof(char**) + 1);
	
	if (NULL == low_case_env)
	{
		return;
	}
	
	AllocNew (low_case_env, envp, count);
	
	StrCpyLow (low_case_env, envp, count);
	
	PrintLowCaseEnv (low_case_env, count);
	
	CleanUp (low_case_env, count);
}






