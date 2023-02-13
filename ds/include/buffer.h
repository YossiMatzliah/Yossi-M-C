***********ADT - Circular Buffer Implementation***********


typedef struct c_buffer
{
	size_t capacity;
	size_t read;
	size_t write;
	char data[1];
}c_buffer_t;

NO OVERWRITE!

c_buffer_t *CBufferCreate(size_t capacity);									/*Create buffer set to given capacity*/			O(1)
void CBufferDestroy(c_buffer_t *buffer);									/*Destroy buffer*/								O(1)
ssize_t CBufferWrite(c_buffer_t *buffer,const void *src, size_t data_size); /*Write element to end of buffer*/				O(n)
ssize_t CBufferRead(c_buffer_t *buffer,void *dest, size_t size);			/*Read first element from buffer*/ 				O(1)
size_t CBufferSize(const c_buffer_t *buffer); 								/*Returns the current size of buffer*/			O(1)
size_t CBufferFreeSpace(const c_buffer_t *buffer);							/*Returns the current capacity of the buffer*/	O(1)
int CBufferIsEmpty(const c_buffer_t *buffer); 								/*Return 1 if buffer is empty, 0 if not*/		O(1)

**Advanced**
c_buffer_t *CBufferResize(c_buffer_t *buffer, size_t new_capacity);																	O(n)
ssize_t CBufferOverwrite(c_buffer_t *buffer,const void *src, size_t data_size); /*Write element to end of buffer*/			O(n)
