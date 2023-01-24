/********************************
*	Developper: Yossi Matzliah	*
*	Date: 		23/01/2023		*
*	Reviewer:	Omri			*
********************************/
#include <string.h>
#include "word_boundary.h"
#define BYTE_WORD_SIZE   (__WORDSIZE/8)
#define COPY_INT_TO_WORD(a)   (0x0101010101010101*a)

size_t CopyOneByte(char *runner, int c, size_t n);
/*size_t CopyOneByteToTwoRunners(char *runner1, char *runner2, size_t n);*/

size_t CopyOneByte(char *runner, int c, size_t n)
{
	while (n > 0)
	{
		*runner = c;
		++runner;
		--n;
	}
	
	return n;
}
/*
size_t CopyOneByteToTwoRunners(char *runner1, char *runner2, size_t n)
{
	while (n > 0)
	{
		*runner1 = *runner2;
		++runner1;
		++runner2;
		--n;	
	}
	
	return n;
}
*/
void *MemSet (void *str, int c, size_t n)
{
	char *runner = (char *)str;

	while (n && 0 != ((size_t) runner) % BYTE_WORD_SIZE ) /* while not aligned */
	{
		CopyOneByte (runner, c, n);													
	}
	
	while (BYTE_WORD_SIZE < n) 
	{
		*((size_t *)(runner)) = COPY_INT_TO_WORD(c);
		runner += BYTE_WORD_SIZE;
		n -= BYTE_WORD_SIZE;												
	}
	n = CopyOneByte (runner, c, n);

	return str;													
}

void *MemCpy (void *dest, const void * src, size_t n)
{
	size_t *src_eight_bytes = (size_t *) src;
	size_t *dest_eight_bytes = (size_t *)dest;
	unsigned char* src_char = NULL;
	unsigned char* dest_char = NULL;
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
	
	dest_char = (unsigned char *)dest_eight_bytes;	
	src_char = (unsigned char *)src_eight_bytes;

	while (n > 0)
	{
		*dest_char = *src_char;
		++dest_char;
		++src_char;
		--n;	
	}
	return dest;											
}

void *MemMove (void *dest, const void *src, size_t n)
{
	char *p_dest = NULL;
	char *p_src = NULL;
	size_t i = 0;
	
	if (dest <= src || (char *)dest >= ((char *)src + n)) 
	{
		return MemCpy (dest, src, n);
	} 
    
	else 
	{
		p_dest = (char *)dest + n - 1;
		p_src = (char *)src + n - 1;

		for (i = 0; i < n; ++i) 
		{
			*p_dest = *p_src;
			--p_dest;
			--p_src;
		}
	}
	return dest;
}

void WordBounderyTest ()
{
	char text1[] = "1234567890";
	char text2[] = "lmnopqrstuvwxyz98765432";
	printf ("Before changes:\n%s \n",text1);
	printf ("%s \n",text2);
	MemSet ((void *)text1, 'B', 9);
	MemSet ((void *)text2, 'A', 10);
	printf ("after MemSet: %s \n",text1);
	printf ("%s \n",text2);
	printf ("__________ \n");
	
	MemCpy ((text1),(text1 + 2), 3);
	printf ("After MemCpy:  %s \n",text1);
	
	MemMove ((text1+2),(text1), 3);
	printf ("After MemMove: %s \n",text1);
}

