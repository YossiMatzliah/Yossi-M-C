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

#include "../../ds/include/c_buffer.h"

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
	c_buffer_t *buffer = (c_buffer_t *)malloc(capacity + sizeof(c_buffer_t));
	
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
	return (0 == buffer->read);
}

size_t CBufferFreeSpace(const c_buffer_t *buffer)
{
	size_t size = 0;
	
	assert(NULL != buffer);
	
	if (CBufferIsEmpty(buffer))
	{
		size = buffer->capacity - 1;
	}
	
	else if (buffer->read > buffer->write)
	{
		size = buffer->read - buffer->write;
	}
	
	else if (buffer->read < buffer->write)
	{
		size = buffer->capacity - buffer->write + buffer->read - 1;
	}
	
	return size;
}

size_t CBufferSize(const c_buffer_t *buffer)
{
	site_t free_space = 0;
	
	assert(NULL != buffer);
	
	if (1 == CBufferIsEmpty(buffer))
	{
		free_space = buffer->read;
	}
	else
	{
		free_space = buffer->capacity - CBufferFreeSpace(buffer) -1;
	}
	return free_space;
}

ssize_t CBufferWrite(c_buffer_t *buffer,const void *src, size_t data_size)
{
	unsigned char *src_runner = NULL;
	size_t bytes_wrote = 0;
	
	assert (NULL != buffer);
	
	if (0 == CBufferFreeSpace(buffer))
	{ 
		return -1;
	}
	
	src_runner = (unsigned char *)src;
	
	if (0 == buffer->read)
	{
		++(buffer->write);
		memcpy((void *)(buffer->data + buffer->write), src_runner, 1);
		++(buffer->read);
		++(buffer->write);
		++src_runner;
		++bytes_wrote;
	}
		
	while (bytes_wrote != data_size && (buffer->read != buffer->write))
	{
		memcpy((void *)(buffer->data + buffer->write), src_runner, 1);
		++(buffer->write);
		++src_runner;
		++bytes_wrote;
		
		if (buffer->write == buffer->capacity)
		{
			buffer->write = 1;
		}
		
		if (buffer->write == buffer->read)
		{
			errno = ENOSPC;
		}
	}
	
	return bytes_wrote;
}

ssize_t CBufferRead(c_buffer_t *buffer,void *dest, size_t data_size)
{
	unsigned char *dest_runner = NULL;
	size_t bytes_read = 0;
	
	assert (NULL != buffer);
	
	if (CBufferIsEmpty(buffer))
	{
		return -1;
	}
	
	dest_runner = (unsigned char *)dest;
	
	if (data_size >= CBufferSize(buffer))
	{
		data_size = CBufferSize(buffer);
		while (bytes_read != data_size) 
		{
			memcpy(dest_runner, (void *)(buffer->data + buffer->read), 1);
			++(buffer->read);
			++dest_runner;
			++bytes_read;
			
			if (buffer->read == buffer->capacity)
			{
				buffer->read = 1;
			}
		}
			
		buffer->read = 0;
		buffer->write = 0;	
	}
	 
	else
	{
		while (bytes_read != data_size) 
		{
			memcpy(dest_runner, (void *)(buffer->data + buffer->read), 1);
			++(buffer->read);
			++dest_runner;
			++bytes_read;
		
			if (buffer->read == buffer->capacity)
			{
				buffer->read = 1;
			}
		}
	}
	
	return data_size;
}

void PrintCB(const c_buffer_t *buffer)
{
	size_t i = 1;
	size_t read_ind = buffer->read;
	
	if (buffer->read == buffer->write)
	{
		for (i = 1; i < buffer->capacity; ++i)
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
				read_ind = 1;
			}
			printf("%x, ", buffer->data[read_ind++]);
		}
		printf("\n");
	}
	printf("Read index: %ld, Write index: %ld\n", buffer->read, buffer->write);
}

