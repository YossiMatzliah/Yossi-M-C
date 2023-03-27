/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Daniel				*
*	Date      : 22/03/2023			*
************************************/

#include <assert.h>	/* assert */
#include <stdlib.h>	/* malloc, free */

#include "bst.h"

#define FALSE	(0)
#define TRUE	(1)

#define IS_LEAF(node) ((NULL == (node)->children[LEFT]) && (NULL == (node)->children[RIGHT]))
#define HAS_RIGHT_CHILD(x) (NULL != x->children[RIGHT])
#define HAS_LEFT_CHILD(x) (NULL != x->children[LEFT])
#define IS_LEFT_CHILD(x) ((x) == x->parent->children[LEFT])
#define IS_RIGHT_CHILD(x) ((x) == x->parent->children[RIGHT])
#define MAX2(a, b) (((a) > (b)) ? (a) : (b))

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

static bst_node_t *CreateNode(void *data);
static bst_iter_t GetLeftChild(bst_iter_t iterator);
static bst_iter_t GetRightChild(bst_iter_t iterator);
static bst_iter_t GetMostLeftChild(bst_iter_t iterator);
static bst_iter_t GetMostRightChild(bst_iter_t iterator);
static void SwitchParentChild(bst_iter_t parent_iter, bst_iter_t new_child_iter, child_pos_t old_child_pos);
static size_t BSTHeightRec(bst_node_t *node);

/********************************************/

bst_t *BSTCreate(int (*cmp_func)(const void *, const void *))
{
	bst_t *bst = (bst_t *)malloc(sizeof(bst_t));
	bst_node_t dummy_root = {NULL};

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

	while (FALSE == BSTIsEmpty(bst))		
	{
		BSTRemove(BSTBeginIter(bst));		
	}

	free(bst);
	bst = NULL;
}

int BSTIsEmpty(const bst_t *bst)
{
	assert(NULL != bst);
	
	return (NULL == bst->dummy_root.children[LEFT]);
}

bst_iter_t BSTInsert(bst_t *bst, void *data)
{
	bst_iter_t new_node = NULL;
	bst_iter_t curr_node = NULL;
	bst_iter_t parent_node = NULL;
	child_pos_t child_pos = LEFT;
	int cmp_res = 0;
	
	assert(NULL != bst);
	assert(NULL != data);
	
	new_node = CreateNode(data);
	if (NULL == new_node)
	{
		return NULL;
	}
	
	curr_node = bst->dummy_root.children[LEFT];
	parent_node = BSTEndIter(bst);
	
	while (NULL != curr_node)
	{
		cmp_res = bst->cmp_func(data, curr_node->data);
	
		assert(0 != cmp_res);
		
		parent_node = curr_node;
		if (0 > cmp_res)
		{
			curr_node = curr_node->children[LEFT];
			child_pos = LEFT;
		}
		else
		{
			curr_node = curr_node->children[RIGHT];
			child_pos = RIGHT;
		}
	}
	
	new_node->parent = parent_node;
	parent_node->children[child_pos] = new_node;
	
	return new_node;
}

void BSTRemove(bst_iter_t iter)
{
	bst_iter_t remove_iter = NULL;
	bst_iter_t parent = NULL;
	bst_iter_t child = NULL;
	bst_iter_t next_iter = NULL;
	child_pos_t remove_iter_pos = LEFT;
	
	assert(NULL != iter);
	
	remove_iter = iter;
	parent = remove_iter->parent;
	remove_iter_pos = (TRUE == IS_LEFT_CHILD(remove_iter)) ? LEFT : RIGHT;
	
	if (TRUE == IS_LEAF(remove_iter))
	{
		parent->children[remove_iter_pos] = NULL;
	}
	
	else if (FALSE == HAS_RIGHT_CHILD(remove_iter) ||
			 FALSE == HAS_LEFT_CHILD(remove_iter))
	{
		child = (FALSE == HAS_RIGHT_CHILD(remove_iter)) ? GetLeftChild(remove_iter) : GetRightChild(remove_iter);
		
		SwitchParentChild(parent, child, remove_iter_pos);
	}
	
	else
	{
		next_iter = BSTNextIter(remove_iter);
		
		next_iter->children[LEFT] = GetLeftChild(remove_iter);
		remove_iter->children[LEFT]->parent = next_iter;
		
		SwitchParentChild(parent, next_iter, remove_iter_pos);
	}
	
	free(remove_iter);
}

bst_iter_t BSTEndIter(const bst_t *bst)
{
	assert(NULL != bst);

	return (bst_iter_t)(&(bst->dummy_root));
}

bst_iter_t BSTBeginIter(const bst_t *bst)
{
	bst_node_t *runner = NULL;
	
	assert(NULL != bst);
	
	runner = (bst_iter_t)&bst->dummy_root;;
	
	while (NULL != runner->children[LEFT])
	{
		runner = runner->children[LEFT];
	}
	
	return (bst_iter_t)runner;
}

int BSTIsSameIter(const bst_iter_t iter1, const bst_iter_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);
	
	return iter1 == iter2;
}

void *BSTGetData(bst_iter_t iter)
{
	assert(NULL != iter);

	return iter->data;
}

bst_iter_t BSTNextIter(const bst_iter_t iter)
{
	bst_iter_t next_iter = NULL;
	
	assert(NULL != iter);
	
	next_iter = iter;
	
	if (TRUE == HAS_RIGHT_CHILD(next_iter))
	{
		next_iter = GetRightChild(next_iter);
		next_iter = GetMostLeftChild(next_iter);
	}
	
	else if (TRUE == IS_LEFT_CHILD(next_iter))
	{
		next_iter = next_iter->parent;
	}
	
	else
	{
		while (next_iter != GetLeftChild(next_iter->parent))
		{
			next_iter = next_iter->parent;
		}
		
		next_iter = next_iter->parent;
	}
	
	return next_iter;
}

bst_iter_t BSTPrevIter(const bst_iter_t iter)
{
	bst_iter_t next_iter = NULL;
	
	assert(NULL != iter);
	
	next_iter = iter;
	
	if (TRUE == HAS_LEFT_CHILD(next_iter))
	{
		next_iter = GetLeftChild(next_iter);
		next_iter = GetMostRightChild(next_iter);
	}
	
	else if (TRUE == IS_RIGHT_CHILD(next_iter))
	{
		next_iter = next_iter->parent;
	}
	
	else
	{
		while (NULL != next_iter->parent && next_iter != GetRightChild(next_iter->parent))
		{
			next_iter = next_iter->parent;
		}
		
		next_iter = next_iter->parent;
	}
	
	return next_iter;
}

size_t BSTSize(const bst_t *bst)
{
	size_t counter = 0;
	bst_node_t *iter = NULL;
	
	assert(NULL != bst);
	
	iter = BSTBeginIter(bst);
	
	for (counter = 0; &bst->dummy_root != iter; ++counter)
	{
		iter = BSTNextIter(iter);
	}
	
	return counter;
}

size_t BSTHeight(const bst_t *bst)
{
	assert(NULL != bst);
	
	return BSTHeightRec(bst->dummy_root.children[LEFT]);
}

bst_iter_t BSTFind(const bst_t *bst, const void *key) 	
{
	bst_iter_t current = NULL;
	
	assert(NULL != bst);
	assert(NULL != key);
	
	current = bst->dummy_root.children[LEFT];
	while (current != BSTEndIter(bst) && NULL != current)
	{
		if (bst->cmp_func(current->data, key) == 0)
		{
			return current;
		}
		current = current->children[bst->cmp_func(current->data, key) < 0];
	}

	return BSTEndIter(bst);
}

int BSTForEach(bst_iter_t from, const bst_iter_t to, int (*action_func)(void *, void *), void *param)
{
	int res = 0;
	bst_iter_t iter = from;
	
	while (iter != to && res == 0 && NULL != iter->data)
	{
		res = action_func(iter->data, param);
		iter = BSTNextIter(iter);
	}

	return res;
}

/************************ Static Functions ************************/

static bst_node_t *CreateNode(void *data)
{
	bst_node_t *new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
	
	if (NULL == new_node)
	{
		return NULL;
	}

	new_node->parent = NULL;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	new_node->data = data;

	return new_node;
}

static bst_iter_t GetLeftChild(bst_iter_t iterator)
{
	assert(NULL != iterator);
	
	return iterator->children[LEFT];
}

static bst_iter_t GetRightChild(bst_iter_t iterator)
{
	assert(NULL != iterator);
	
	return iterator->children[RIGHT];
}

static bst_iter_t GetMostLeftChild(bst_iter_t iterator)
{
	assert(NULL != iterator);
	
	while (NULL != GetLeftChild(iterator))
	{
		iterator = GetLeftChild(iterator);
	}
	
	return iterator;
}

static bst_iter_t GetMostRightChild(bst_iter_t iterator)
{
	assert(NULL != iterator);
	
	while (NULL != GetRightChild(iterator))
	{
		iterator = GetRightChild(iterator);
	}
	
	return iterator;
}

static void SwitchParentChild(bst_iter_t parent_iter, bst_iter_t new_child_iter, child_pos_t old_child_pos)
{
	parent_iter->children[old_child_pos] = new_child_iter;
	new_child_iter->parent = parent_iter;
}

static size_t BSTHeightRec(bst_node_t *node)
{
	if (NULL == node || NULL == ((node->children[LEFT] && NULL == node->children[RIGHT])))
	{
		return 0;
	}
	
	return MAX2(BSTHeightRec(node->children[LEFT]), BSTHeightRec(node->children[RIGHT])) + 1;
}


