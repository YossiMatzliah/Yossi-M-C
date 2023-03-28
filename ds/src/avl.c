/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Moses				*
*	Date      : 27/03/2023			*
************************************/

#include <assert.h>	/* assert */
#include <stdlib.h>	/* malloc */
#include <stdio.h>	/* perror */
#include <errno.h>	/* errno */

#include "avl.h"

#define FALSE	(0)
#define TRUE	(1)

#define SUCCESS	(0)
#define FAILURE	(1)

#define GET_ROOT_NODE(x) ((x)->dummy_root.children[LEFT])
#define IS_LEAF(node) ((NULL == (node)->children[LEFT]) && (NULL == (node)->children[RIGHT]))
#define HAS_RIGHT_CHILD(x) (NULL != x->children[RIGHT])
#define HAS_LEFT_CHILD(x) (NULL != x->children[LEFT])
#define MAX2(a, b) (((a) > (b)) ? (a) : (b))
#define UPDATE_HEIGHT(a, b) 1 + MAX2(NodeHeight((a)), NodeHeight((b)))

typedef struct avl_node avl_node_t;

typedef enum child_pos
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_CHILDREN = 2
}child_pos_t;

struct avl_node
{
	avl_node_t *children[NUM_OF_CHILDREN];
	void *data;
	size_t height;
};

struct avl_tree
{
	avl_node_t dummy_root;
	int (*cmp_func)(const void *, const void *);
};

/************** static func *****************/

static avl_node_t *CreateNode(avl_node_t *left_child, avl_node_t *right_child, void *data, size_t height);
static void InitNode(avl_node_t *init_node, avl_node_t *left_child, avl_node_t *right_child, void *data, size_t height);
static avl_node_t *AVLInsertRec(avl_t *avl, avl_node_t *node, void *data);
static avl_node_t *BalanceTreeInsert(avl_t *avl, avl_node_t *root, void *data);
static avl_node_t *AVLRemoveRec(avl_t *avl, avl_node_t *root, const void *key);
static avl_node_t *BalanceTreeRemove(avl_t *avl, avl_node_t *root);
static void AVLDestroyRec(avl_t *avl, avl_node_t *node);
static void *AVLFindRec(const avl_t *avl, avl_node_t *node, const void *key);
static void RootCheck(avl_t *avl, avl_node_t *root, avl_node_t *temp);
static size_t AVLCountRec(avl_node_t *node);
static size_t NodeHeight(avl_node_t *node);
static int GetBalance(avl_node_t *node);
static avl_node_t *GetLeftChild(avl_node_t *node_ptr);
static avl_node_t *GetRightChild(avl_node_t *node_ptr);
static avl_node_t *GetMinimum(avl_node_t *runner);
static avl_node_t *RotateLeft(avl_t *avl, avl_node_t *root);
static avl_node_t *RotateRight(avl_t *avl, avl_node_t *root);
static int InOrder(avl_node_t *node, int (*action_func)(void *, void *), void *param);
static int PreOrder(avl_node_t *node, int (*action_func)(void *, void *), void *param);
static int PostOrder(avl_node_t *node, int (*action_func)(void *, void *), void *param);

/********************************************/

avl_t *AVLCreate(int (*cmp_func)(const void *, const void *))
{
	avl_t *new_avl = NULL;
	size_t height = 0;
	avl_node_t dummy_node = {0};
	
	assert(NULL != cmp_func);
	
	new_avl = (avl_t *)malloc(sizeof(avl_t));
	if (NULL == new_avl)
	{
    	perror("Error");
    	return NULL;
	}
	
	InitNode(&dummy_node, NULL, NULL, NULL, height);
	
	new_avl->dummy_root = dummy_node;
	new_avl->cmp_func = cmp_func;
	
	return new_avl;
}

void AVLDestroy(avl_t *avl)
{
	assert(NULL != avl);
	
	AVLDestroyRec(avl, GET_ROOT_NODE(avl));
	free(avl);
}

int AVLInsert(avl_t *avl, void *data)
{
	assert(NULL != avl);
    
	return !(NULL != AVLInsertRec(avl, GET_ROOT_NODE(avl), data));
}

void AVLRemove(avl_t *avl, const void *key)
{
	assert(NULL != avl);
	
	if (IS_LEAF(GET_ROOT_NODE(avl)))
	{
		free(GET_ROOT_NODE(avl));
		GET_ROOT_NODE(avl) = NULL;
		return;
	}
	
	AVLRemoveRec(avl, GET_ROOT_NODE(avl), key);
}

void *AVLFind(const avl_t *avl, const void *key)
{
	assert(NULL != avl);
	
	return AVLFindRec(avl, GET_ROOT_NODE(avl), key);
}

int AVLForEach(avl_t *avl, int (*action_func)(void *, void *), void *param, order_t order)
{
	assert(NULL != avl);
	assert(NULL != action_func);
	
	switch (order)
	{
		case IN_ORDER:
			return InOrder(GET_ROOT_NODE(avl), action_func, param);
		case POST_ORDER:
			return PostOrder(GET_ROOT_NODE(avl), action_func, param);
		case PRE_ORDER:
			return PreOrder(GET_ROOT_NODE(avl), action_func, param);
		default:
			perror("Invalid order!\n");
			return FAILURE;
	}
}

int AVLIsEmpty(const avl_t *avl)
{
	assert(NULL != avl);
	
	return (NULL == GET_ROOT_NODE(avl));
}

size_t AVLCount(const avl_t *avl)
{
	if (TRUE == AVLIsEmpty(avl))
	{
		return 0;
	}
	
   return AVLCountRec(GET_ROOT_NODE(avl));
}

size_t AVLHeight(const avl_t *avl)
{
	assert(NULL != avl);
	
	return NodeHeight(GET_ROOT_NODE(avl));
}

/************************ Static Functions ************************/

static avl_node_t *CreateNode(avl_node_t *left_child, avl_node_t *right_child, void *data, size_t height)
{
	avl_node_t *new_node = (avl_node_t *)malloc(sizeof(avl_node_t));
	
	if (NULL == new_node)
	{
		perror("Error\n");
		return NULL;
	}
	
	InitNode(new_node, left_child, right_child, data, height);
	
	return new_node;
}

static void InitNode(avl_node_t *init_node, avl_node_t *left_child, avl_node_t *right_child, void *data, size_t height)
{
	init_node->children[LEFT] = left_child;
	init_node->children[RIGHT] = right_child;
	init_node->data = data;
	init_node->height = height;
}

static void AVLDestroyRec(avl_t *avl, avl_node_t *node)
{
    if (NULL != node)
	{
		AVLDestroyRec(avl, node->children[LEFT]);
		AVLDestroyRec(avl, node->children[RIGHT]);
		free(node);
	}
}

static avl_node_t *AVLInsertRec(avl_t *avl, avl_node_t *node, void *data)
{
	if (NULL == node)
	{
		node = CreateNode(NULL, NULL, data, 1);
		
		if (TRUE == AVLIsEmpty(avl))
		{
			GET_ROOT_NODE(avl) = node;
		}
		
		return node;
	}
	
	if (0 < avl->cmp_func(data, node->data))
	{
		node->children[RIGHT] = AVLInsertRec(avl, GetRightChild(node), data);
	}
	
	if (0 > avl->cmp_func(data, node->data))
	{
		node->children[LEFT] = AVLInsertRec(avl, GetLeftChild(node), data);
	}
	
  	node->height = UPDATE_HEIGHT(GetLeftChild(node), GetRightChild(node));
	
	return BalanceTreeInsert(avl, node, data);
}

static avl_node_t *BalanceTreeInsert(avl_t *avl, avl_node_t *root, void *data)
{
	if (1 < GetBalance(root))
	{
		if (0 < avl->cmp_func(data, GetLeftChild(root)->data))
		{
			root->children[LEFT] = RotateLeft(avl, GetLeftChild(root));
		}
		
		return RotateRight(avl, root);
	}
	
	if (-1 > GetBalance(root))
	{
		if (0 > avl->cmp_func(data, GetRightChild(root)->data))
		{
			root->children[RIGHT] = RotateRight(avl, GetRightChild(root));
		}
		
		return RotateLeft(avl, root);
	}
	
	return root;
}

static avl_node_t *AVLRemoveRec(avl_t *avl, avl_node_t *root, const void *key)
{
	int cmp_result = 0;
	avl_node_t *temp = NULL;
	child_pos_t child_position = LEFT;
	
	if (NULL == root)
	{
		return root;
	}
	
	cmp_result = avl->cmp_func(key, root->data);
	
	if (0 != cmp_result)
	{
		child_position =  (0 > cmp_result) ? LEFT: RIGHT;
		root->children[child_position] = AVLRemoveRec(avl, root->children[child_position], key);
	}
	
	else
	{
		if (FALSE == HAS_LEFT_CHILD(root))
		{
			temp = GetRightChild(root);
			RootCheck(avl, root, temp);
			free(root);
			
			return temp;
		}
		
		else if (FALSE == HAS_RIGHT_CHILD(root))
		{
			temp = GetLeftChild(root);
			RootCheck(avl, root, temp);
			free(root);
			
			return temp;
		}
		
		temp = GetMinimum(GetRightChild(root));
		root->data = temp->data;
		
		root->children[RIGHT] = AVLRemoveRec(avl, root->children[RIGHT], temp->data);
	}

	root->height = UPDATE_HEIGHT(GetLeftChild(root), GetRightChild(root));
	
	return BalanceTreeRemove(avl, root);
}

static avl_node_t *BalanceTreeRemove(avl_t *avl, avl_node_t *root)
{
	if (NULL == root)
	{
		return root;
	}

	root->height = UPDATE_HEIGHT(GetLeftChild(root), GetRightChild(root));

	if (1 < GetBalance(root))
	{
		if (0 > GetBalance(GetLeftChild(root)))
		{
			root->children[LEFT] = RotateLeft(avl, GetLeftChild(root));
		}
		
		return RotateRight(avl, root);
	}

	if (-1 > GetBalance(root))
	{
		if (0 < GetBalance(GetRightChild(root)))
		{
			root->children[RIGHT] = RotateRight(avl, GetRightChild(root));
		}
		
		return RotateLeft(avl, root);
	}
	
	return root;
}

static void *AVLFindRec(const avl_t *avl, avl_node_t *node, const void *key)
{
	if (NULL == node)
	{
		return NULL;
	}
	
	if (0 < avl->cmp_func(key, node->data))
	{
		return AVLFindRec(avl, GetRightChild(node), key);
	}
	
	if (0 > avl->cmp_func(key, node->data))
	{
		return AVLFindRec(avl, GetLeftChild(node), key);
	}
	
	return node->data;
}

static int InOrder(avl_node_t *node, int (*action_func)(void *, void *), void *param)
{   
	int status = SUCCESS;
	 
	if (NULL == node)
	{
		return SUCCESS;
	}
	
	status = InOrder(GetLeftChild(node), action_func, param);
	if (SUCCESS != status)
	{
		return status;
	}
	
	status = action_func(node->data, param);
	if (SUCCESS != status)
	{
		return status;
	}
	
	status = InOrder(GetRightChild(node), action_func, param);
	if (SUCCESS != status)
	{
		return status;
	}
	
	return status;
}

static int PostOrder(avl_node_t *node, int (*action_func)(void *, void *), void *param)
{
	int status = SUCCESS;
	 
	if (NULL == node)
	{
		return SUCCESS;
	}
	
	status = InOrder(GetLeftChild(node), action_func, param);
	if (SUCCESS != status)
	{
		return status;
	}
	
	status = InOrder(GetRightChild(node), action_func, param);
	if (SUCCESS != status)
	{
		return status;
	}
	
	status = action_func(node->data, param);
	if (SUCCESS != status)
	{
		return status;
	}
	
	return status;
}

static int PreOrder(avl_node_t *node, int (*action_func)(void *, void *), void *param)
{
	int status = SUCCESS;
	 
	if (NULL == node)
	{
		return SUCCESS;
	}
	
	status = action_func(node->data, param);
	if (SUCCESS != status)
	{
		return status;
	}

	status = InOrder(GetLeftChild(node), action_func, param);
	if (SUCCESS != status)
	{
		return status;
	}
	
	status = InOrder(GetRightChild(node), action_func, param);
	if (SUCCESS != status)
	{
		return status;
	}
	
	return status;
}

static size_t AVLCountRec(avl_node_t *node)
{
	if (NULL == node)
	{
		return 0;
	}
	
	return AVLCountRec(GetLeftChild(node)) + AVLCountRec(GetRightChild(node)) + 1;
}

static size_t NodeHeight(avl_node_t *node)
{
	if (NULL == node)
	{
		return 0;
	}
	
	return node->height;
}

static avl_node_t *GetLeftChild(avl_node_t *node_ptr)
{
	assert(NULL != node_ptr);
	
	return node_ptr->children[LEFT];
}

static avl_node_t *GetRightChild(avl_node_t *node_ptr)
{
	assert(NULL != node_ptr);
	
	return node_ptr->children[RIGHT];
}

static avl_node_t *GetMinimum(avl_node_t *runner)
{
	while (NULL != GetLeftChild(runner))
	{
		return runner = GetLeftChild(runner);
	}
	
	return runner;
}

static int GetBalance(avl_node_t *node)
{
	if (NULL == node)
	{
		return 0;
	}
	
	return NodeHeight(GetLeftChild(node)) - NodeHeight(GetRightChild(node));
}

static avl_node_t *RotateLeft(avl_t *avl, avl_node_t *root)
{
	avl_node_t *right_child = GetRightChild(root);

	root->children[RIGHT] = GetLeftChild(right_child);
	right_child->children[LEFT] = root;
	
	root->height = UPDATE_HEIGHT(GetLeftChild(root), GetRightChild(root));
	right_child->height = UPDATE_HEIGHT(GetLeftChild(right_child), GetRightChild(right_child));
	
	if (root == avl->dummy_root.children[LEFT])
	{
		avl->dummy_root.children[LEFT] = right_child;
	}

	return right_child;
}

static avl_node_t *RotateRight(avl_t *avl, avl_node_t *root)
{
	avl_node_t *left_child = GetLeftChild(root);
	
	root->children[LEFT] = GetRightChild(left_child);
	left_child->children[RIGHT] = root;
	
	root->height = UPDATE_HEIGHT(GetLeftChild(root), GetRightChild(root));
	left_child->height = UPDATE_HEIGHT(GetLeftChild(left_child), GetRightChild(left_child));
	
	if (root == avl->dummy_root.children[LEFT])
	{
		avl->dummy_root.children[LEFT] = left_child;
	}

	return left_child;
}

static void RootCheck(avl_t *avl, avl_node_t *root, avl_node_t *temp)
{
	if (root == GET_ROOT_NODE(avl))
	{
		GET_ROOT_NODE(avl) = temp;    
	}
}

