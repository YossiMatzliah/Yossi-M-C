

/*
print all data types sizes
*/
void PrintDataType()
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


size_t SumOfOneRow (int arr[], size_t c)
{
	size_t i, result = 0;
	
	for (i = 0; i <= c; i++)
	{
		result += arr[i];	
		printf ("array [%ld] = %d and the result is: %ld\n", i, arr[i], result);
	}
	
	return result;
}

size_t IsX (size_t i, int arr[], size_t size, int x)
{
	size_t holder = i;
	size_t flag = 0;
	
	for (i = holder + 1; i < size; i++) 
	{
		if (i == holder && 1 == flag)
    	{
    		return i;
    	}
		
		if (x == arr[i] && i != holder)
		{
    		printf ("entered IsX and i =  %ld \n", i);
    		return i;
    	}
    
    	else if (i >= size && 0 == flag) 
    	{
    		i = 0;
    		flag = 1;
    	}
	}
	return i;
}

size_t Josephus (int soldier[], size_t size)
{
	size_t i, holder = 0;

	do
	{
		holder = i;
		if (holder != IsX (i, soldier, size, 1))
		{
			soldier[i] = 0;
			printf ("entered IsX and now soldier [%ld] = %d \n", i, soldier[i]);
			i = IsX (i, soldier, size, 1);
		}
	} while (i != holder);
		
	return i;	
}
