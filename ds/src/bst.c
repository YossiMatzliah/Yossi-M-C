/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Daniel				*
*	Date      : 21/03/2023			*
************************************/

#include <assert.h>	/* assert */
#include <string.h>	/* strncmp */

#include "bst.h"

#define EQUAL	(0)
#define FALSE	(0)
#define TRUE	(1)

typedef enum child_pos
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_CHILDREN = 2
}child_pos_t;

struct bst_node
{
	bst_node_t *parent;
	bst_node_t *children[NUM_OF_CHILDREN];
	void *data;
};

struct binary_search_tree
{
	bst_node_t dummy_root;
	int (*cmp_func)(const void *, const void *);
};

/************** static func *****************/



/********************************************/

bst_t *BSTCreate(int (*cmp_func)(const void *, const void *))
{
	bst_t *bst = (bst_t *)malloc(sizeof(bst_t));
	bst_node_t dummy_root = {0};

	assert(NULL != cmp_func);
	
	if (NULL == bst)
    {
        return NULL;
    }
    
    bst->cmp_func = cmp_func;
    bst->dummy_root = dummy_root;
    
    return bst;
}

void BSTDestroy(bst_t *bst)
{
    assert(NULL != bst);

    while (!BSTIsEmpty(bst))
    {
        BSTRemove(BSTBeginIter(bst));
    }

    free(bst);
}

int BSTIsEmpty(const bst_t *bst)
{
	assert(NULL != bst);
	
    return (NULL == bst->dummy_root.children[LEFT]);
}

bst_iter_t BSTInsert(bst_t *bst, void *data)
{
	
}

void BSTRemove(bst_iter_t iter)
{
	
}

bst_iter_t BSTEndIter(const bst_t *bst)
{
	
}

bst_iter_t BSTBeginIter(const bst_t *bst)
{
   
}

int BSTIsSameIter(const bst_iter_t iter1, const bst_iter_t iter2)
{
	
}

void *BSTGetData(bst_iter_t iter)
{
	
}

bst_iter_t BSTNextIter(const bst_iter_t iter)
{
	
}

bst_iter_t BSTPrevIter(const bst_iter_t iter)
{
	
}

size_t BSTSize(const bst_t *bst)
{
	
}

size_t BSTHeight(const bst_t *bst)
{
    
}

bst_iter_t BSTFind(const bst_t *bst, const void *key) 	
{
	
}

int BSTForEach(bst_iter_t from, const bst_iter_t to, int (*action_func)(void *, void *), void *param)
{
	
}

/************************ Static Functions ************************/



