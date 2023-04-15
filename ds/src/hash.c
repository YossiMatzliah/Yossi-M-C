/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Daniel				*
*	Date      : 15/04/2023			*
************************************/

#include <stdio.h>	/* perror */
#include <assert.h>	/* assert */
#include <errno.h>	/* errno */
#include <stdlib.h>	/* calloc */
#include <math.h>	/* pow, sqrt */

#include "dll.h"
#include "hash.h"

#define SUCCESS (0)
#define FAILURE (1)

#define BUCKET(index) table->hash_table_array[index]

struct hash_table
{
    dll_t **hash_table_array;
    size_t capacity;
    size_t(*hash_func)(const void *value);
    int(*is_match_func)(const void *lhd, const void *rhd);
};

/********************** API Functions **********************/

hash_table_t *HashTableCreate(size_t capacity, size_t (*hash_func)(const void *value), int (*is_match_func)(const void *lhd, const void *rhd))
{
    hash_table_t *new_hash_table = NULL;
    
    assert(0 != capacity);
    assert(NULL != hash_func);
    assert(NULL != is_match_func);

    new_hash_table = malloc(sizeof(hash_table_t));
    if (NULL == new_hash_table)
    {
        perror("Allocation Error");
        return NULL;
    }

    new_hash_table->hash_table_array = calloc(capacity, sizeof(dll_t *));
    if (NULL == new_hash_table->hash_table_array)
    {
        perror("Allocation Error");
        free(new_hash_table);
        return NULL;
    }
    
    new_hash_table->capacity = capacity;
    new_hash_table->hash_func = hash_func;
    new_hash_table->is_match_func = is_match_func;
    
    return new_hash_table;
}

void HashTableDestroy(hash_table_t *table)
{
    size_t i = 0;

    assert(NULL != table);

    for (i = 0; i < table->capacity; ++i)
    {
        if (NULL != BUCKET(i))
        {
            DLLDestroy(BUCKET(i));
        }
    }
    
    free(table->hash_table_array);
    free(table);
}

int HashTableInsert(hash_table_t *table, void *data)
{
    size_t bucket_key = 0;
    dll_t *dll_bucket = NULL;
    iterator_t inserted_node = NULL;
    
    assert(NULL != table);
    
    bucket_key = table->hash_func(data) % table->capacity;
    
    if (NULL == BUCKET(bucket_key))
    {
        dll_bucket = DLLCreate();
        if (NULL == dll_bucket)
        {
            return FAILURE;
        }
    
        BUCKET(bucket_key) = dll_bucket;
    }
    
    inserted_node = DLLPushFront(BUCKET(bucket_key), data);

    if (DLLIsSameIter(DLLEndIter(BUCKET(bucket_key)), inserted_node))
    {
        return FAILURE;
    }
    
    return SUCCESS;
}

void HashTableRemove(hash_table_t *table, const void *data)
{
    size_t bucket_key = 0;
    dll_t *dll_bucket = NULL;
    iterator_t node_to_remove = NULL;
    
    assert(NULL != table);

    bucket_key = table->hash_func(data) % table->capacity;
    dll_bucket = BUCKET(bucket_key);
    
    if (NULL != dll_bucket)
    {
        node_to_remove = DLLFind(DLLBeginIter(dll_bucket), DLLEndIter(dll_bucket), table->is_match_func, (void *)data);
        
        if (!DLLIsSameIter(DLLEndIter(dll_bucket), node_to_remove))
        {
            DLLRemove(node_to_remove);
        }
    }
}

size_t HashTableSize(const hash_table_t *table)
{
    size_t i = 0;
    size_t counter = 0;
    
    assert(NULL != table);

    for (i = 0; i < table->capacity; ++i)
    {
        if (NULL != BUCKET(i))
        {
            counter += DLLCount(BUCKET(i));
        }
    }

    return counter;
}

int HashTableIsEmpty(const hash_table_t *table)
{
    return (0 == HashTableSize(table));
}

void *HashTableFind(const hash_table_t *table, const void *data)
{
    size_t bucket_key = 0;
    iterator_t found_data_node = NULL;
    void *to_return_data = NULL;

    assert(NULL != table);

    bucket_key = table->hash_func(data) % table->capacity;

    if (NULL != BUCKET(bucket_key))
    {
        found_data_node = DLLFind(DLLBeginIter(BUCKET(bucket_key)), DLLEndIter(BUCKET(bucket_key)), table->is_match_func, (void *)data);

        if (found_data_node == DLLEndIter(BUCKET(bucket_key)))
        {
            return NULL;
        }

        to_return_data = DLLGetData(found_data_node);   /* to increse priority*/
        DLLRemove(found_data_node);
        DLLPushFront(BUCKET(bucket_key), to_return_data);
    }

    return to_return_data;
}

int HashTableForEach(const hash_table_t *table, int (*action_func)(void *data, void *param), void *param)
{
    size_t i = 0;
    int return_val = SUCCESS;

    assert(NULL != table);

    for (i = 0; i < table->capacity && SUCCESS == return_val; ++i)
    {
        if (NULL != BUCKET(i))
        {
            return_val = DLLForEach(DLLBeginIter(BUCKET(i)), DLLEndIter(BUCKET(i)), action_func, param);
        }
    }

    return return_val;
}

double HashLoad(const hash_table_t *table)
{
    assert(NULL != table);

    return (double)HashTableSize(table) / table->capacity;
}

double HashSTDev(const hash_table_t *table)
{
    size_t i = 0;
    double mean = 0;
    double sd = 0;
    size_t nodes_in_dll = 0;
    
    assert(NULL != table);
    
    mean = HashLoad(table);
    
    for (i = 0; i < table->capacity; ++i) 
    {
        if (NULL != BUCKET(i))
        {
            nodes_in_dll = DLLCount(BUCKET(i));
            sd += pow(nodes_in_dll - mean, 2);
        }
    }
    
    return sqrt(sd / table->capacity);
}

