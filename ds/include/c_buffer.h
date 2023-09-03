/**************************************
*	Developer :	Yossi Matzliah        *
*	Date      : 15/02/2023			  *
*	Reviewer  :	Oran				  *
**************************************/

#ifndef __C_BUFFER_H__
#define __C_BUFFER_H__

#include <sys/types.h> /* ssize_t */
typedef struct c_buffer c_buffer_t;

/******************************************************************/

/*
* CBufferCreate Description:
*	Creates a circular buffer: both managerial struct and data buffer
*	The circular buffer uses write-fail behavior (i.e. When full and receives data, it doesn't
	overwrite)
*
* @Params:
*	capacity - capacity of the buffer
*		NOTE : sending 0 capacity will cause undefiend behaviour.
*
* @Returns:
*	returns pointer c_buffer_t to new circular buffer,
	if allocation fails return NULL
*
* @Complexity
*	Time : O(n)
*	Space: O(n)
*/
c_buffer_t *CBufferCreate(size_t capacity);	

/*
* CBufferDestroy Description:
*	Frees the circular buffer from the memory
*
* @Params:
*	buffer - pointer to buffer
*		NOTE : sending data_size > sizeof( dest ) will cause undefiend behaviour.
*
* @Returns:
*	No Return Value
*
* @Complexity
*	Time : O(1)
*	Space: O(1)
*/	
void CBufferDestroy(c_buffer_t *buffer);

/*
* CBufferWrite Description:
*	write data_size bytes from src to buffer
*
* @Params:
*	buffer 		- pointer to circular buffer
*	src   		- pointer to source from which to copy
*	data_size 	- number of bytes to read from src to buffer.
*		NOTE : sending data_size > sizeof( src ) will cause undefiend behaviour.
*		NOTE : sending data_size > Free space of buffer, will cause error, and bytes will not
*			   overwrite.
*
* @Returns:
*	On success, the number of bytes written is returned.  On error,
*	-1 is returned, and errno is set to indicate the error.
*
* @ERRORS
*	ENOMEM -  Out of memory.
*
* @Complexity
*	Time : O(n)
*	Space: O(1)
*/	
ssize_t CBufferWrite(c_buffer_t *buffer,const void *src, size_t data_size);

/*
* CBufferRead Description:
*	read data_size bytes from buffer to dest
*
* @Params:
*	buffer - pointer to circular buffer
*	dest   - pointer to value that will store data from the buffer
*	data_size - number of bytes to read from buffer to dest.
*		NOTE : sending an unspecified buffer will cause undefiend behaviour
*		NOTE : sending data_size > sizeof( dest ) will cause undefiend behaviour.
*		NOTE : if the data_size is greater than the amount of data in the buffer, only the data in the
*		 	   buffer will be coppied and there will be an error
* 
* @Returns:
*	On success, the number of bytes written is returned.  On error,
*	-1 is returned, and errno is set to indicate the error.
*		Note: a successful write may transfer fewer than data_size.
*           
* @ERRORS
*	ENOSPC - No space left on buffer
*	
*
* @Complexity
*	Time : O(n)
*	Space: O(1)
*/	
ssize_t CBufferRead(c_buffer_t *buffer,void *dest, size_t data_size);		

/*
* CBufferSize Description:
*	return the number of bytes in buffer currently in use
*
* @Params:
*	buffer - pointer to circular buffer
*		NOTE : sending an unspecified buffer will cause undefiend behaviour
*
* @Returns:
*	  return size_t numbmer used bytes in buffer
*
* @Complexity
*	Time: O(1)
*	Space: O(1)
*/	
size_t CBufferSize(const c_buffer_t *buffer); 						

/*
* CBufferFreeSpace Description:
*	returns the number of bytes which are free, i.e. not in use.
*
* @Params:
*	buffer - pointer to circular buffer
*		NOTE : sending da unspecified buffer will cause undefiend behaviour
*
* @Returns:
*	  return size_t number of free bytes in buffer
*
* @Complexity
*	Time : O(1)
*	Space: O(1)
*/	
size_t CBufferFreeSpace(const c_buffer_t *buffer);
							
/*
* CBufferIsEmpty Description:
*	Checks if the buffer is empty or not
*
* @Params:
*	buffer - pointer to circular buffer.
*	NOTE : sending da unspecified buffer will cause undefiend behaviour
*
* @Returns:
*	returns 1 if buffer is empty, or 0 otherwise
*
* @Complexity
*	Time : O(1)
*	Space: O(1)
*/
int CBufferIsEmpty(const c_buffer_t *buffer); 							

/* Prints the buffer */
void PrintCB(const c_buffer_t *buffer);

/*******************************************************************************
**Advanced**
*******************************************************************************/
/*c_buffer_t *CBufferResize(c_buffer_t *buffer, size_t new_capacity);	*/		/* O(n) */

/*ssize_t CBufferOverwrite(c_buffer_t *buffer,const void *src, size_t data_size);*//*Write element to end of buffer*/ /* O(n) */

#endif

