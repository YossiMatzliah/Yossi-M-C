/********************************
*	Developper: Yossi Matzliah	*
*	Date: 		23/01/2023		*
*	Reviewer:	Omri			*
********************************/
#include <string.h>
#include "word_boundary.h"
#define BYTE_WORD_SIZE   (__WORDSIZE/8)
#define COPY_INT_TO_WORD(a)   (0x0101010101010101*a)

static size_t CopyOneByte(char *runner, int c, size_t n);
static size_t CopyOneByteToTwoRunners(char *runner1, char *runner2, size_t n);

static size_t CopyOneByte(char *runner, int c, size_t n)
{
	if (n > 0)
	{
		*runner = c;
		++runner;
		--n;
	}
	
	return n;
}

static size_t CopyOneByteToTwoRunners(char *runner1, char *runner2, size_t n)
{
	if (n > 0)
	{
		*runner1 = *runner2;
		++runner1;
		++runner2;
		--n;	
	}
	
	return n;
}

void *MemSet (void *str, int c, size_t n)
{
	char *runner = (char *)str;

	while (n && 0 != ((size_t) runner) % BYTE_WORD_SIZE ) /* while not aligned */
	{
		CopyOneByte (runner, c, n);							
		printf ("%s \n", (char *)str);						
	}
	
	while (BYTE_WORD_SIZE < n) 
	{
		*((size_t *)(runner)) = COPY_INT_TO_WORD(c);
		runner += BYTE_WORD_SIZE;
		n -= BYTE_WORD_SIZE;
		printf ("%s \n", (char *)str);												
	}
	n = CopyOneByte (runner, c, n);

	return str;													
}

void *MemCpy (void *dest, const void * src, size_t n)
{
	char* src_char = NULL;
	char* dest_char = NULL;
	size_t *src_eight_bytes = (size_t *) src;
	size_t *dest_eight_bytes = (size_t *)dest;
	/*
	while (0 != *((unsigned int *)dest) % BYTE_WORD_SIZE &&
	  0 != *((unsigned int *)src) % BYTE_WORD_SIZE && 0 != n)
	{
		CopyOneByteToTwoRunners((char *)dest, (char *)src, n);													
	}
	*/
	while (BYTE_WORD_SIZE < n)
	{
		*dest_eight_bytes = *src_eight_bytes;
		++dest_eight_bytes;
		++src_eight_bytes;
		n -= BYTE_WORD_SIZE;									
	}
	
	dest_char = (char *)dest_eight_bytes;	
	src_char = (char *)src_eight_bytes;

	n = CopyOneByteToTwoRunners(dest_char, src_char, n);
	return dest;												
}

void *MemMove (void *dest, const void *src, size_t n)
{
	unsigned char *dest_runner = (unsigned char *)dest;
	unsigned char *src_runner = (unsigned char *)src;
	
	while ( BYTE_WORD_SIZE < n )
	{
		*((size_t *)(dest_runner)) = *((size_t *)(src_runner));
		dest_runner += BYTE_WORD_SIZE;
		src_runner += BYTE_WORD_SIZE;
		n -= BYTE_WORD_SIZE;												
	}
	
	n = CopyOneByteToTwoRunners((char *)dest_runner, (char *)src_runner, n);													
	
	return dest;
}

void WordBounderyTest ()
{
	char text1[] = "zxcvbnm1234567890";
	char text2[] = "qwertyuiopasdfghj";
	printf ("Before changes: %s \n",text1);
	printf ("%s \n",text2);
	/*MemSet ((void *)text1, 'B', 9);
	MemSet ((void *)text2, 'A', 10);
	printf ("after MemSet: %s \n",text1);
	printf ("%s \n",text2);*/
	printf ("__________ \n");
	
	memcpy ((void *)(text1 + 2),(const void *)(text1), 10);
	printf ("After MemCpy: %s \n",text1);
	/* MemCpy won't overlap cause used of functions with local pointers. should change it */

	MemMove ((void *)(text1),(const void *)text2, 10);
	printf ("After MemMove: %s \n",text1);
}

