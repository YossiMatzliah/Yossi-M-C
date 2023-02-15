/**************************************
*	Developer :	Yossi Matzliah        *
*	Date      : 15/02/2023			  *
*	Reviewer  :	Oran				  *
**************************************/

#include <stdio.h>	/* printf */

#include "../../ds/include/c_buffer.h"

#define U_LINE 	"\033[1m\033[4m"
#define RED   	"\033[1m\033[41m\x1B[30m"
#define GRN   	"\033[1m\033[42m\x1B[30m"
#define RESET 	"\033[0m"
#define PRINTSUCCESS	printf(GRN"SUCCESS!"RESET"\n\n")
#define PRINTFAILURE	printf(RED"FAILURE!"RESET"\n\n")
#define TRUE (1)
#define FALSE (0)

static void TestCBuffer();
static void TestCBufferIsEmpty(c_buffer_t *buffer);

/**************************************************/

int main()
{
	TestCBuffer();
	
	return 0;
}

static void TestCBuffer()
{
	size_t capacity = 8;
	char buff1[] = {1, 2, 3, 4, 5};
	char buff2[] = {6, 7};
	size_t size = 0;
	ssize_t writed_size = 0; 
	c_buffer_t *test_buffer = NULL;
	char dest[8] = {0}; 
	ssize_t bytes_to_read = 4;	
	
	test_buffer = CBufferCreate(capacity);
	
	TestCBufferIsEmpty(test_buffer);
	
	printf("The capacity of the buffer is %ld\n",capacity - 1);
	
	size = sizeof(buff1);
	printf("writing %ld bytes:\n", size);
	writed_size = CBufferWrite(test_buffer, buff1, size); 
	
	printf("You wrote %ld bytes to the string.\n", writed_size);
	PrintCB(test_buffer);
	printf("After write the size is: %ld and the free space is: %ld\n", CBufferSize(test_buffer), CBufferFreeSpace(test_buffer)); 
	PRINTSUCCESS;
	
	size = sizeof(buff2);
	
	printf("Trying to write %ld bytes:\n", size);
	writed_size = CBufferWrite(test_buffer, buff2, size); 
	
	printf("You wrote %ld bytes to the string.\n", writed_size);
	PrintCB(test_buffer); 
    printf("After write the size is: %ld and the free space is: %ld\n", CBufferSize(test_buffer), CBufferFreeSpace(test_buffer));
    PRINTSUCCESS;
                                                                                                   
	printf("Trying to write %ld bytes:\n", size);
	writed_size = CBufferWrite(test_buffer, buff2, size); 
	
	if (-1 == writed_size)
	{
		printf("Full capacity, can't write more.\n");
		PRINTSUCCESS;
	}
	else
	{
		PRINTFAILURE;
	}
	
	printf("Trying to read %ld bytes.\n", bytes_to_read);
	bytes_to_read = CBufferRead(test_buffer, dest, bytes_to_read);
	printf("After read the size is: %ld and the free space is: %ld\n", CBufferSize(test_buffer), CBufferFreeSpace(test_buffer));
	PRINTSUCCESS;
	
	printf("Trying to read %ld bytes.\n", bytes_to_read);
	bytes_to_read = CBufferRead(test_buffer, dest, bytes_to_read);
	
	if (3 == bytes_to_read)
	{
		printf("succeeded to read %ld bytes. Buffer is now empty, can't read more.\n", bytes_to_read);
		PRINTSUCCESS;
	}
	else
	{
		PRINTFAILURE;
	}
	
	printf("Trying to read %ld bytes.\n", bytes_to_read);
	bytes_to_read = CBufferRead(test_buffer, dest, bytes_to_read);
	
	if (-1 == bytes_to_read)
	{
		printf("The buffer is empty, can't read more.\n");
		PRINTSUCCESS;
	}
	else
	{
		PRINTFAILURE;
	} 
	
	size = sizeof(buff1);
	printf("Trying to write %ld bytes:\n", size);
	writed_size = CBufferWrite(test_buffer, buff1, size); 
	
	printf("You wrote %ld bytes to the string.\n", writed_size);
	PrintCB(test_buffer);
	printf("After write the size is: %ld and the free space is: %ld\n", CBufferSize(test_buffer), CBufferFreeSpace(test_buffer));
	PRINTSUCCESS;
	
	bytes_to_read = 4;
	printf("Trying to read %ld bytes.\n", bytes_to_read);
	bytes_to_read = CBufferRead(test_buffer, dest, bytes_to_read);
	printf("After read the size is: %ld and the free space is: %ld\n", CBufferSize(test_buffer), CBufferFreeSpace(test_buffer));
	PrintCB(test_buffer);
	PRINTSUCCESS;
	
	printf("Trying to write %ld bytes:\n", size);
	writed_size = CBufferWrite(test_buffer, buff2, size);
	
	printf("You wrote %ld bytes to the string.\n", writed_size);
	PrintCB(test_buffer);
	printf("After write the size is: %ld and the free space is: %ld\n", CBufferSize(test_buffer), CBufferFreeSpace(test_buffer));
	PRINTSUCCESS;
	
	CBufferDestroy(test_buffer);
}

static void TestCBufferIsEmpty(c_buffer_t *buffer)
{
	printf(U_LINE"Test Queue IsEmpty:\n"RESET);
	
	if (TRUE == CBufferIsEmpty(buffer))
	{
		PRINTSUCCESS;
	}
	
	else
	{
		PRINTFAILURE;
	}
}

