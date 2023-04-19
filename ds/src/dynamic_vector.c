/********************************
*	Developper: Yossi Matzliah	*
*	Date: 		04/02/2023		*
*	Reviewer:	Avri			*
********************************/

#include <stdlib.h> 	/* malloc, realloc, free */
#include <assert.h> 	/* assert */
#include <string.h>		/* memset, memcpy */


#include "/home/yossi/git/ds/include/dynamic_vector.h"

typedef enum {SUCCESS = 0, FAILURE = 1} realoc_flag_t;

struct vector
{
	void *data;
	size_t element_size;
	size_t capacity;
	size_t size;
};

vector_t *VectorCreate(size_t capacity, size_t element_size)
{
	vector_t *vector = NULL;
	
	assert(0 != capacity);
	assert(0 != element_size);
	
	vector = (vector_t *)malloc(sizeof(vector_t));
	if (NULL == vector)
	{
		perror("Memory allocation for the vector failed \n");
		return NULL;
	}
	
	vector->data = malloc(capacity * element_size);
	if (NULL == vector->data)
	{
		perror("Memory allocation for the data array failed \n");
		free(vector);
		return NULL;
	}
	
	vector->size = 0;
	vector->capacity = capacity;
	vector->element_size = element_size;
	
	return vector;
}

void VectorDestroy(vector_t *vector)
{
	assert(NULL != vector);
	
	vector->size = 0;
	vector->capacity = 0;
	vector->element_size = 0;
	memset(vector->data, 0, vector->capacity * vector->element_size);
	free(vector->data);
	free(vector);
}

int VectorPushBack(vector_t *vector, const void *element)
{
	realoc_flag_t realloc_flag = SUCCESS;
	void *new_data = NULL;

	assert(NULL != vector);
	assert(NULL != element);
	assert(vector->size < vector->capacity);
	
	memcpy((char *)vector->data + (vector->size * vector->element_size), element, vector->element_size);   
	if (vector->size == (vector->capacity - 1)) 
	{
		new_data = realloc(vector->data, GROWTH_FACTOR * vector->capacity * vector->element_size);
		if (NULL == new_data)
		{
			perror("Memory allocation for the vector data failed \n");
			realloc_flag = FAILURE;
		}
		
		else
		{
			vector->data = new_data;
			vector->capacity *= GROWTH_FACTOR;
		}
	}
	++vector->size;
	return realloc_flag;
}

void VectorPopBack(vector_t *vector)
{
	assert(NULL != vector);
	assert(vector->size > 0); 
	assert(!VectorIsEmpty(vector));

	--vector->size;
	if (vector->size <= (vector->capacity) / SHRINK_THRESHOLD) /* add minimal cap */
	{
		vector->data = realloc(vector->data, vector->element_size * (vector->capacity / GROWTH_FACTOR));

		vector->capacity /= GROWTH_FACTOR;	
	}
}

void *VectorGetAccessToElement(const vector_t *vector, size_t index)
{
	assert(NULL != vector);
	
	return ((char *)vector->data + (vector->element_size * index));
}

int VectorReserve(vector_t *vector, size_t reserve_size)
{
 	realoc_flag_t realloc_flag = SUCCESS;
	void *new_data = NULL;
	
	assert(reserve_size > vector->capacity);
	assert(NULL != vector);
		
	new_data = realloc(vector->data, vector->element_size * reserve_size);	
	if (NULL == new_data)
	{
		realloc_flag = FAILURE;
	}

	else
	{
		vector->data = new_data;
		vector->capacity = reserve_size;
	}

	return realloc_flag;
}

int VectorShrinkToSize(vector_t *vector)
{
	realoc_flag_t realloc_flag = SUCCESS;
	
	assert(NULL != vector);
	assert(!VectorIsEmpty(vector));
	
	vector->data = realloc(vector->data, (vector->size * vector->element_size) + 1);
	if (NULL == vector)
	{
		perror("Memory allocation for the vector data failed \n");
		realloc_flag = FAILURE;
	}
	
	else
	{
		vector->capacity = vector->size + 1;
	}

	return realloc_flag;	
}

int VectorIsEmpty(const vector_t *vector)
{
	assert(NULL != vector);

	return (0 == vector->size);
}

size_t VectorCapacity(const vector_t *vector)
{
	assert(NULL != vector);

	return vector->capacity;
}

size_t VectorSize(const vector_t *vector)
{
	assert(NULL != vector);

	return vector->size;
}

