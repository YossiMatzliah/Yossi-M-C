/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Yotam S				*
*	Date      : 01/05/2023			*
************************************/

#include <stdio.h>  /* perror */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <limits.h> /* UINT_MAX */

#include "trie.h"

#define IS_FULL(left, right) (NULL != left && NULL != right && left->is_full == TRUE && right->is_full == TRUE)

typedef enum trie_status
{
    SUCCESS = 0,
    FAILURE = 1,
    FULL_TREE = 2,
    DOUBLE_FREE = 3,
    DS_FAILURE = 4,
    SEARCH_BIGGER = 5
} trie_status_t;

typedef enum boolean 
{
    FALSE = 0,
    TRUE = 1
} boolean_t;

typedef enum child_pos
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_CHILDREN = 2
} child_pos_t;

struct trie_node 
{
	trie_node_t *children[NUM_OF_CHILDREN];
	int is_full;
} ;

struct trie 
{
	trie_node_t *root;
    int counter;
	int height;
} ;

/****************************** Static Functions *********************************/

static void TrieDestroyRec(trie_node_t *node);
static int TrieInsertRec(trie_node_t *curr_node, unsigned int *result, int height);
static trie_status_t TrieFreeRec(trie_node_t *curr_node, unsigned int requested, int height);
static trie_node_t *TrieCreateNode();
static child_pos_t UpdateUintPtrToNext(unsigned int *result, int height);
static boolean_t VerifyNodeExistence(trie_node_t *node, int side_bit, unsigned int *result);

/******************************* API Functions ***********************************/

trie_t *TrieCreate(unsigned int height)
{
    trie_t *trie = (trie_t *)calloc(1, sizeof(trie_t));
	if (NULL == trie)
    {
        perror("Allocation Error");
        return NULL;
    }
    
    trie->root = TrieCreateNode(trie);
    trie->counter = 0;
    trie->height = height;
    
    return trie;
}

void TrieDestroy(trie_t *trie)
{
	TrieDestroyRec(trie->root);
	free(trie);
}

int TrieInsert(trie_t *trie, unsigned int requested, unsigned int *result)
{
    int status = 0;
    *result = requested;

	assert(NULL != trie);
    
    if (trie->root->is_full)
    {
        *result = UINT_MAX;
        return FULL_TREE;
    }
    
    status = TrieInsertRec(trie->root, result, trie->height - 1);
    
    if (SEARCH_BIGGER == status)    /*not found any bigger search from scratch*/
    {
        *result = 0;
        status = TrieInsertRec(trie->root, result, trie->height - 1);
    }

    trie->counter += (SUCCESS == status) ? 1 : 0;
    *result = (SUCCESS != status) ? UINT_MAX : *result;

    return status;
}

int TrieFree(trie_t *trie, unsigned int requested)
{
    int status = 0;

	assert(NULL != trie);

    status = TrieFreeRec(trie->root, requested, trie->height - 1);

    trie->counter -= (SUCCESS == status) ? 1 : 0;

    return status;
}

size_t TrieCountFree(const trie_t *trie)
{
	assert(NULL != trie);

    return ((1 << trie->height) - trie->counter);
}

int TrieIsEmpty(const trie_t *trie)
{
	assert(NULL != trie);

    return (0 == trie->counter);
}

/****************************** Static Functions *********************************/

static void TrieDestroyRec(trie_node_t *node)
{
	if (NULL == node)
	{
		return;
	}
	
	TrieDestroyRec(node->children[LEFT]);
	TrieDestroyRec(node->children[RIGHT]);
    free(node);
	node = NULL;
}

static int TrieInsertRec(trie_node_t *curr_node, unsigned int *result, int height)
{
    int side_bit = 0;
    trie_status_t status = SUCCESS;

	assert(NULL != curr_node);

    if (0 > height)
    {
        curr_node->is_full = TRUE;
       
        return SUCCESS;
    }
    
	side_bit = (*result >> height & 1);
    
    if (NULL != curr_node->children[side_bit] && curr_node->children[side_bit]->is_full)
    {
        if(NULL != curr_node->children[1 - side_bit] && curr_node->children[1 - side_bit]->is_full)
        {
            *result = UINT_MAX;
            
            return SEARCH_BIGGER;
        }
        /*some1 is full need to fix height */
        if (0 == side_bit)
        {   
            /* set off all bits on the right to current bit and set current bit on */
            side_bit = UpdateUintPtrToNext(result, height);
        }

        else
        {
            return SEARCH_BIGGER;
        }
    }

	if (FALSE == VerifyNodeExistence(curr_node, side_bit, result))
    {
        return FAILURE;
    }
    
    status = TrieInsertRec(curr_node->children[side_bit], result, height - 1);

    if (SEARCH_BIGGER == status)
    {
        if (1 == side_bit)  /*go up until the first zero */
        {
            return SEARCH_BIGGER;
        }

        else   
        {
            /* set off all bits on the right to current bit and set current bit on */
            side_bit = UpdateUintPtrToNext(result, height);

            if (NULL == curr_node->children[side_bit])
            {
                curr_node->children[side_bit] = TrieCreateNode();
                if (NULL == curr_node->children[side_bit])
                {
                    *result = UINT_MAX;
                    
                    return FAILURE;
                }
            }
            
            status = TrieInsertRec(curr_node->children[side_bit], result, height - 1);
        }
    }
    
    curr_node->is_full = IS_FULL(curr_node->children[LEFT], curr_node->children[RIGHT]);
    
    return status;
}

static trie_status_t TrieFreeRec(trie_node_t *curr_node, unsigned int requested, int height)
{
    int side_bit = requested >> height & 1;
    trie_status_t status = SUCCESS;
    
	assert(NULL != curr_node);

    if (0 == height)
    {
        if (TRUE != curr_node->children[side_bit]->is_full)
        {
            return DOUBLE_FREE;
        }
        else
        {
            curr_node->children[side_bit]->is_full = FALSE;
            curr_node->is_full = FALSE;

            return SUCCESS;
        }
    }
    
    if (NULL != curr_node->children[side_bit])
    {
        status = TrieFreeRec(curr_node->children[side_bit], requested, height - 1);
        curr_node->is_full = FALSE;
    }
    else
    {
        status = DOUBLE_FREE;
    }
    
    return status;
}

static trie_node_t *TrieCreateNode()
{
	trie_node_t *trie_node = (trie_node_t *)calloc(1, sizeof(trie_node_t));

	if (NULL == trie_node)
    {
        perror("Allocation Error");
        return NULL;
    }

	trie_node->children[LEFT] = NULL;
    trie_node->children[RIGHT] = NULL;
	trie_node->is_full = FALSE;
    
    return trie_node;
}

static child_pos_t UpdateUintPtrToNext(unsigned int *result, int height)
{
    *result &= ~((1 << (height + 1)) - 1);
    *result ^= (1 << height);

    return RIGHT;
}

static boolean_t VerifyNodeExistence(trie_node_t *node, int side_bit, unsigned int *result)
{
    boolean_t boolean = TRUE;

    if (NULL == node->children[side_bit])
    {
        node->children[side_bit] = TrieCreateNode();
        
        if (NULL == node->children[side_bit])
        {
            *result = UINT_MAX;
            boolean = FALSE;
        }
    }

    return boolean;
}