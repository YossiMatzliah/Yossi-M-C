#include <stdio.h>

/* 1 */
void XCrosTwoPowY (unsigned int x, unsigned int y)
{
	printf("Res is: %d\n", x << y);
}

/* 2a */
unsigned int IsPowOfTwoWLoop (unsigned int n)
{
	if (0 == n) 
	{
		return 0;
	}
	while (!(1 & n))
	{
		n = n >> 1;
	}
	return n == 1;
}
	
/* 2b */
unsigned int IsPowOfTwo (unsigned int n)
{
	return n && (!(n & (n - 1))); /* if power of 2 than the (expresion)
	 equal. 1 the first n is for elimanate if we enter 0 (0 && 1 = 0) */
}

/* 3 */
unsigned int AddOne (int n)
{ 
	return -~n; /*  mask = 1 
					while (num & mask)
					{
						num ^= mask;
						musk <<= 1;	
					}
					num ^= mask;
					return num;
				*/
}

/* 4 */
void PrintThreeBitsOn (unsigned int arr[], size_t size)
{
	int m = 1, i = 0;
	int counter = 0;
		
	for (i = 0; i < (int)size ; i++)
	{
		m = 1;
		while (m != '\0')
		{
			if (arr[i] & m)
			{
				counter = AddOne (counter);
			}
			m <<= 1;
		} 

		if(counter == 3)
		{
			printf ("%d  ", arr[i]);
		}
		counter = 0;
	}
	printf ("\n");
}

/* 5.a */
int ByteMirrorLoop (int A)
{
	int i = 1;
	int j = 1;
	int Am = 0;
	
	while ((i > 0)/* && (0 < A)*/)
	{
		Am = (A&1) + (Am<<1);
		A >>= 1;
		i <<= 1;
	}
	
	while (j < i)
	{
		Am <<= 1;
		i >>= 1;
	}
	return Am;
}

/* 5.b */
unsigned char ByteMirror (unsigned char n)
{
	return ( ((n & 0x80) >> 7) | ((n & 0x40) >> 5) | ((n & 0x20) >> 3) | ((n & 0x10) >> 1) |
			 ((n & 0x08) << 1) | ((n & 0x04) << 3) | ((n & 0x02) << 5) | ((n & 0x01) << 7) );
}

/* 6.a */
int CharBoth (unsigned char A)
{	
	return ((A&2)&&(A&32));
}

/* 6.b */
int CharAtLeastOne (unsigned char A)
{	
	return ((A&2)||(A&32));
}

/* 6.c */
unsigned char ThreeAnd5On (unsigned char n)
{
	return ( ((n & 0x80)) | ((n & 0x40)     ) | ((n & 0x20)) | ((n & 0x10) >> 2) |
			 ((n & 0x08)) | ((n & 0x04) << 2) | ((n & 0x02)) | ((n & 0x01))    );
}

/* 7 */
unsigned int Dived16 (unsigned int n)
{
	n = n>>4;
	n = n<<4;
	return n; 
}

/* 8 */
void Swap (int *x, int *y)
{
	if (*x != *y)
	{
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
	}
	
	return ;
}

/* 9.a */
unsigned int BitCountLoop (unsigned int n)
{
	int count = 0;
	
	while (n > 0) 
	{
		n = n&(n - 1);
		count++;
	}
	
	return count;
}

/* 9.b */
unsigned int BitCount (unsigned int x)
{
		x = (x & (0x55555555)) + ((x>>1)  & (0x55555555));
		x = (x & (0x33333333)) + ((x>>2)  & (0x33333333));
		x = (x & (0x0f0f0f0f)) + ((x>>4)  & (0x0f0f0f0f));
		x = (x & (0x00ff00ff)) + ((x>>8)  & (0x00ff00ff));
		x = (x & (0xffffffff)) + ((x>>16) & (0xffffffff));
	return x;
}


int main()
{
	unsigned int x = 5;
	unsigned int y = 2;
	unsigned int n = 64;
	unsigned int arr[] = {3,7,11,15};
	size_t size = 4;
	
	
	/* 1 */
	XCrosTwoPowY(x, y);
	
	/* 2a */
	printf ("%d\n", IsPowOfTwo(n));
	
	/* 2b */
	printf ("%d\n", IsPowOfTwoWLoop (n));
	
	/* 3 */
	
	printf ("%d\n", AddOne (n));

	/* 4 */
	PrintThreeBitsOn (arr, size);
	/* 5a */
	printf ("%d\n", ByteMirrorLoop(805306368));  /* 805306368 is mirror of 6*/ 
	/* 5b */
	printf ("%d\n", ByteMirror(96));  /* 96 and 6 are mirror one to eachother */
	/* 6.a */
	printf ("%d\n", CharBoth(33));
	/* 6.b */
	printf ("%d\n", CharAtLeastOne(33)); 
	/* 6.c */
	printf ("%d\n", ThreeAnd5On('A'));
	/* 7 */
	printf ("%d\n", Dived16(165)); 
	/* 8 */
	{
	int x=3, y=5;
	printf ("%d\n%d\n", x, y);
	Swap (&x ,&y);
	printf ("%d\n%d\n", x, y);  
	}
	/* 9.a */
	printf ("%d\n", BitCountLoop(31)); 
	/* 9.b */
	printf ("%d\n", BitCount(31)); 
	
	return 0;
}
