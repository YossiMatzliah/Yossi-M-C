#define N 256
typedef unsigned char u_ch;
typedef int num;
typedef unsigned int u_num;
typedef char ch;
typedef void (*func_pointer)(char);  /* the data type func_pointer is 
a pointer to a function which accepts char as an argument 
and does not return a value */
typedef size_t (*arrayOfNPointers(void))[N];
#define ESC 27

/*	When the A or T keys are pressed the key that was pressed
    will be displyed in the terminal. ESC for termination	 */

void KeyboardPressedSC() /* by switch-case */
{
	ch key = '0';
	
	printf("Press a key\n");
	system("stty -icanon -echo");
	
	while (ESC != (key = getchar())) 
	{
		switch (key)
		{
			case 'A':
			printf ("A-pressed\n");
			break;
			
			case 'T':
			printf ("T-pressed\n");
			break;
		}
	
	}
	
	system("stty icanon echo");
	printf ("You exit the program \n");
}


void KeyboardPressedIE() /* by if-else */
{
	ch key = '0';
	
	printf("Press a key\n");
	system("stty -icanon -echo");
	
	while (ESC != (key = getchar())) 
	{
		if ('A' == key)
		{
			printf ("A-pressed\n");
		}
		
		else if ('T' == key)
		{
			printf ("T-pressed\n");
		}	
	}
	
	system("stty icanon echo");
	printf ("You exit the program \n");
}


void PrintLetter(ch key)
{
	printf("%c -pressed \n", key);
}

void NothingFunc(ch key) /* to fill the lut with nothing */ 
{
}

void KeyboardPressedLUT() /* by lookup table */
{
	func_pointer lut_arr[N];
	ch key = '0';
	size_t i = 0;
	
	printf("Press a key\n");
	system("stty -icanon -echo");
	
	for (i = 0; i < N; i++)
	{
		lut_arr[i] = NothingFunc; 
	}
	
	lut_arr['T'] = PrintLetter;
	lut_arr['A'] = PrintLetter; 
	
	do
    {
   		key = getchar();
    	lut_arr[(int)key](key);
    }while (ESC != key);
	
	system("stty icanon echo");
	printf ("You exit the program \n");
}
