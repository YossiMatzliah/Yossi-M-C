/************************************
 *	Developer :	Yossi Matzliah      *
 *	Reviewer  :					*
 *	Date      : /04/2023			*
 ************************************/

#include <stdio.h>  /* perror */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <math.h>   /* pow */

#include "trie.h"

#define IS_FULL(left, right) (NULL != left && NULL != right && left->is_full == TRUE && right->is_full == TRUE)

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

/**********************************************************************************
*								Static Functions								  *
***********************************************************************************/

static void TrieDestroyRec(trie_node_t *node);
static int TrieInsertRec(trie_node_t *curr_node, unsigned int *result, int height);
static trie_status_t TrieFreeRec(trie_node_t *curr_node, unsigned int requested, int height);
/*static size_t TrieCountFull(trie_node_t *node, int height, size_t counter);*/
static trie_node_t *TrieCreateNode();

/**********************************************************************************
*								API Functions									  *
***********************************************************************************/

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
        return FULL_TREE;  
    }
    
    status = TrieInsertRec(trie->root, result, trie->height - 1);

    if (FIND_SMALLER == status)
    {
        printf("FIND_SMALLER\n");
        *result = 0;
        status = TrieInsertRec(trie->root, result, trie->height - 1);
    }

    trie->root->is_full = IS_FULL(trie->root->children[LEFT], trie->root->children[RIGHT]);
    printf("trie->root->is_full = %d\n", trie->root->is_full);

    trie->counter += (SUCCESS == status) ? 1 : 0; 

    return status;
}

int TrieFree(const trie_t *trie, unsigned int requested)
{
	assert(NULL != trie);

    return (int)TrieFreeRec(trie->root, requested, trie->height - 1);
}

size_t TrieCountFree(const trie_t *trie)
{
    /*size_t counter = 0;
    size_t full_nodes = 0;*/
    
	assert(NULL != trie);

	/*full_nodes = TrieCountFull(trie->root, trie->height - 1, counter);*/

    return (pow(2, trie->height) - trie->counter);
}

int TrieIsEmpty(const trie_t *trie)
{
	assert(NULL != trie);

    return (NULL == trie->root->children[LEFT] && NULL == trie->root->children[RIGHT]);
}

/**********************************************************************************
*								Static Functions								  *
**********************************************************************************/

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
        printf("SUCCESS\n");
        return SUCCESS;
    }
    
	side_bit = (*result >> height & 1);
    
    if (NULL != curr_node->children[side_bit] && curr_node->children[side_bit]->is_full)
    {
        if(NULL != curr_node->children[1 - side_bit] && curr_node->children[1 - side_bit]->is_full)
        {
            result = NULL;
            return FULL_TREE;
        }
        printf("some1 is full need to fix height = %d, result=%u\n", height, *result);
        if (0 == side_bit)
        {
            printf("here 1\n");
            *result &= ~((1 << (height + 1)) - 1);  /* set off all bits on the right to current bit and set current bit on */
            side_bit = 1;
            *result ^= (1 << height);
        }

        else
        {
            return SEARCH_BIGGER;
        }
        /*check in tests, change to search next if needed*/ /*if all "bigger" are full insert after NETWORK the first available, same if user haven't send requested ID or give invalid one, probably in dhcp.c*/
    }

	if (NULL == curr_node->children[side_bit])
    {
        curr_node->children[side_bit] = TrieCreateNode();
        if (NULL == curr_node->children[side_bit])
        {
            result = NULL;
            return FAILURE;
        }
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
            *result &= ~((1 << (height + 1)) - 1);
            side_bit = 1;
            *result ^= (1 << height);

            if (NULL == curr_node->children[side_bit])
            {
                curr_node->children[side_bit] = TrieCreateNode();
            }
            
            status = TrieInsertRec(curr_node->children[side_bit], result, height - 1);
            if (status == FULL_TREE)
            {
                return FIND_SMALLER;
            }
        }
    }

    if (SEARCH_BIGGER == status)
    {
        printf("FIND_SMALLER in TrieInsertRec\n");
        return FIND_SMALLER;
    }
    
    curr_node->is_full = IS_FULL(curr_node->children[LEFT], curr_node->children[RIGHT]);
    
    return status;
}

static trie_status_t TrieFreeRec(trie_node_t *curr_node, unsigned int requested, int height)
{
    int side_bit = (FALSE != (requested & (1 << height)));
    trie_status_t status = SUCCESS;
    
	assert(NULL != curr_node);

    if (0 == height)
    {
        if (TRUE != curr_node->is_full)
        {
            return DOUBLE_FREE;
        }
        else
        {
            curr_node->is_full = FALSE;
            return SUCCESS;
        }
    }
    
    if (NULL != curr_node->children[side_bit])
    {
        status = TrieFreeRec(curr_node->children[side_bit], requested, height - 1);
        curr_node->is_full = FALSE;
    }
    
    return status;
}

/*static size_t TrieCountFull(trie_node_t *node, int height, size_t counter)
{
	assert(NULL != node);

	if (0 == height && node->is_full)
	{
		return ++counter;
	}
	
	return TrieCountFull(node->children[LEFT], height - 1, counter);
	return TrieCountFull(node->children[RIGHT], height - 1, counter);
}*/

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
