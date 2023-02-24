/**************************************
*	Developer :	Yossi Matzliah        *
*	Date      : 15/02/2023			  *
*	Reviewer  :	Oran				  *
**************************************/

#include <stdlib.h> /*malloc*/
#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/
#include <string.h> /*memcpy*/
#include <errno.h> /*errno*/
#include <stddef.h> /*offsetof*/

#include "../include/c_buffer.h"

#define TRUE (1)
#define FALSE (0)

struct c_buffer
{
	size_t capacity;
	size_t read;
	size_t write;
	char data[1];
};

/**********************************************************/

c_buffer_t *CBufferCreate(size_t capacity)
{
	c_buffer_t *buffer = (c_buffer_t *)malloc(1+ capacity + offsetof(c_buffer_t, data)); 
	
	if (NULL == buffer)
	{
		printf("Memory allocation for the buffer failed \n");
		return NULL;
	}
	
	buffer->capacity = capacity;
	buffer->read = 0;
	buffer->write = 0;
	
	return buffer;
}

void CBufferDestroy(c_buffer_t *buffer)
{
	assert(NULL != buffer);

	free(buffer);
}

int CBufferIsEmpty(const c_buffer_t *buffer)
{
	return (buffer->write == buffer->read);
}

size_t CBufferFreeSpace(const c_buffer_t *buffer)
{
	assert(NULL != buffer);
	
	return (buffer->capacity - CBufferSize(buffer));
}

size_t CBufferSize(const c_buffer_t *buffer)
{
	assert(NULL != buffer);
	if (buffer->write >= buffer->read)
	{
		return (buffer->write - buffer->read);
	}
	else
	{
		return (buffer->read - buffer->write);
	}
}

ssize_t CBufferWrite(c_buffer_t *buffer,const void *src, size_t data_size)
{
	size_t write_pos = 0;
	size_t bytes_to_write = 0;
	size_t buffer_free_space = CBufferFreeSpace(buffer);
	
	assert (NULL != buffer);
	assert(NULL != src);
	assert(0 != data_size);

	if (0 == buffer_free_space)
	{ 
		errno = EOVERFLOW;
		return -1;
	}
	
	if (data_size > buffer_free_space)
	{
		data_size = buffer_free_space;
	}
	
	write_pos = buffer->write % buffer->capacity;
	
	if (write_pos + data_size > buffer->capacity)
	{
		bytes_to_write = buffer->capacity - write_pos;
		memcpy(buffer->data + write_pos, (char *)src, bytes_to_write);
		buffer->write = 0;
	}
   	
	memcpy(buffer->data + (buffer->write % buffer->capacity), (char *)src + bytes_to_write, data_size - bytes_to_write);
	buffer->write += data_size - bytes_to_write;
	
    return (ssize_t)data_size;
}

ssize_t CBufferRead(c_buffer_t *buffer,void *dest, size_t data_size)
{
	size_t bytes_to_read = 0;
	size_t buffer_size = CBufferSize(buffer);
	
	assert (NULL != buffer);
	assert(NULL != dest);
	assert(0 != data_size);

	if (TRUE == CBufferIsEmpty(buffer))
	{
		errno = ENOBUFS;
		buffer->read = 0;
		buffer->write = 0;
		return -1;
	}
	
	if (data_size >= buffer_size)
	{
		data_size = buffer_size;
	}
	if (buffer->read + data_size > buffer->capacity)
	{
		bytes_to_read = buffer->capacity - buffer->read;
	memcpy((char *)dest, buffer->data + buffer->read, bytes_to_read);
	
	buffer->read = 0;
	buffer->write -=  buffer->capacity;
	}
	
	memcpy((char *)dest + bytes_to_read, buffer->data + buffer->read, data_size - bytes_to_read);
	buffer->read += data_size - bytes_to_read;
	
    return (ssize_t)data_size;
}

void PrintCB(const c_buffer_t *buffer)
{
	size_t i = 0;
	size_t read_ind = buffer->read;
	
	if (buffer->read == buffer->write)
	{
		for (i = 0; i < buffer->capacity; ++i)
		{
			printf("%x, ", buffer->data[i]);
		}
	}
	
	else if (buffer->read < buffer->write)
	{
		while (read_ind != buffer->write)
		{
			printf("%x, ", buffer->data[read_ind++]);
		}
		printf("\n");
	}
	
	else if (buffer->read > buffer->write)
	{
		while (read_ind != buffer->write)
		{
			if (read_ind == buffer->capacity)
			{
				read_ind = 0;
			}
			printf("%x, ", buffer->data[read_ind++]);
		}
		printf("\n");
	}
	printf("Read index: %ld, Write index: %ld\n", buffer->read, buffer->write);
}

