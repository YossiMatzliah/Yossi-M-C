#include <stdio.h>

/* 1 */
void XCrosTwoPowY(unsigned int x, unsigned int y)
{
	printf("Res is: %d\n", x << y);
}

/* 2a */
unsigned int IsPowOfTwoWLoop (unsigned int n)
{
	size_t i = 1;

	while(( 0 != (i ^ n)) && ( i <= n )) /* first expre if shifted 
	become 0 if pow of 2 second for loop till n */
	{
		i = i << 1;
	}

	return (0 == (i ^ n));
}

/* 2b */
unsigned int IsPowOfTwo (unsigned int n)
{
	return n && (!(n & (n - 1))); /* if power of 2 than the (expresion)
	 equal. 1 the first n is for elimanate if we enter 0 (0 && 1 = 0) */
}

/* 3 */
unsigned int AddOne(int n)
{ 
	return -~n;
}

/* 4 */
void PrintThreeBitsOn(unsigned int arr[], size_t size)
{
	int m = 1;
	int counter = 0;
	int i = 0;
	
	for(i = 0; i < (int)size ; i++)
	{
		m = 1;
		while(m != '\0')
		{
			if(arr[i] & m)
			{
				counter = AddOne(counter);
			}
			m <<= 1;
		} 

		if(counter == 3)
		{
			printf("%d  ", arr[i]);
		}
		counter = 0;
	}
	printf("\n");
}


unsigned int ByteMirrorLoop(unsigned int x)
{
	unsigned int m_num = 0;
	int i = 0;
	
	while (i < 0x20)
	{
		m_num ^= (x >> i & 1);
		m_num <<= 1;
		++i;
	}
	
	return m_num;

}


unsigned int ByteMirror(unsigned int x)
{
	  return ((x >> 24) & 0x000000ff) | ((x >> 8) & 0x0000ff00) |
          ((x << 8) & 0x00ff0000) | ((x << 24) & 0xff000000);
}




int main()
{
	unsigned int x = 5;
	unsigned int y = 2;
	unsigned int n = 3;
	unsigned int res = 0;
	unsigned int arr[] = {3,7,11,15};
	size_t size = 4;
	
	
	/* 1 */
	XCrosTwoPowY(x, y);
	
	/* 2a */
	res = IsPowOfTwo(n);
	printf ("%d\n", res);
	
	/* 2b */
	res = IsPowOfTwoWLoop (n);
	printf ("%d\n", res);
	
	/* 3 */
	res = AddOne (n);
	printf ("%d\n", res);

	/* 4 */
	PrintThreeBitsOn(arr, size);
	
	/* 5a */
	res = ByteMirrorLoop(33);
	printf("the res of bytemirror by loop: %d\n", res);

	/* 5b */
	res = ByteMirror(33);
	printf("the res of bytemirror: %d\n", res);
	
	return 0;
}
