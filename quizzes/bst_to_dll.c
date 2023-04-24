#include <stdio.h>	/* printf */
#include "uts.c"

typedef struct node node_t;

struct node
{
	int *num;
	node_t *parent;
	node_t *left_child;
	node_t *right_child;
	node_t *left;
	node_t *right;
};

enum child_type
{
	LEFT = 0,
	RIGHT = 1,
	NONE = 2
};

typedef enum child_type child_type_t;
	
/********** static functions *********/	
	
node_t *Begin(node_t *node);
node_t *Next(node_t *node);
child_type_t ChildType(node_t *node);
void InitNode(node_t *node, int *num, node_t *parent, node_t *left_child, node_t *right_child);
void PrintBST(node_t *head);
node_t *BSTToSortedList(node_t *root);
void PrintSortedList(node_t *head);
void PrintSortedListBackWards(node_t *head);

int main()
{
	int a[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	
	node_t node1 = {NULL};
	node_t node2 = {NULL};
	node_t node3 = {NULL};
	node_t node4 = {NULL};
	node_t node5 = {NULL};
	node_t node6 = {NULL};
	node_t node7 = {NULL};
	node_t node8 = {NULL};
	node_t node9 = {NULL};
	node_t node10 = {NULL};
	node_t node11 = {NULL};
	node_t node12 = {NULL};
	node_t node13 = {NULL};
	node_t node14 = {NULL};
	node_t node15 = {NULL};
	
	InitNode(&node1,  &a[0],  &node2, NULL, NULL);
	InitNode(&node2,  &a[1],  &node4, &node1, &node3);
	InitNode(&node3,  &a[2],  &node2, NULL, NULL);
	InitNode(&node4,  &a[3],  &node8, &node2, &node6);
	InitNode(&node5,  &a[4],  &node6, NULL, NULL);
	InitNode(&node6,  &a[5],  &node4, &node5, &node7);
	InitNode(&node7,  &a[6],  &node6, NULL, NULL);
	InitNode(&node8,  &a[7],  NULL, &node4, &node12);
	InitNode(&node9,  &a[8],  &node10, NULL, NULL);
	InitNode(&node10, &a[9],  &node12, &node9, &node11);
	InitNode(&node11, &a[10], &node10, NULL, NULL);
	InitNode(&node12, &a[11], &node8, &node10, &node14);
	InitNode(&node13, &a[12], &node14, NULL, NULL);
	InitNode(&node14, &a[13], &node12, &node13, &node15);
	InitNode(&node15, &a[14], &node14, NULL, NULL);
	
	PrintBST(&node2);

	BSTToSortedList(&node1);

	PrintSortedList(&node1);
	PrintSortedListBackWards(&node1);

	return 0;
}

node_t *Begin(node_t *node)
{
	while (NULL != node->left_child)
	{
		node = node->left_child;
	}
	
	return node;
}

node_t *Next(node_t *node)
{
	child_type_t type = LEFT;
	
	if (NULL != node->right_child)
	{
		node = node->right_child;
		
		return Begin(node);
	}
	
	type = ChildType(node);
	
	if (LEFT == type)
	{
		return node->parent;
	}
	
	while (RIGHT == type)
	{
		node = node->parent;
		type = ChildType(node);
		
		if (NONE == type)
		{
			return NULL;
		}
	}
	
	node = node->parent;
	
	return node;
}

node_t *BSTToSortedList(node_t *root)
{
	node_t *head = Begin(root);
	node_t *run = head;
	node_t *temp = NULL;
	run->left = NULL;
	
	while (NULL != Next(run))
	{
		run->right = Next(run);
		temp = run;
		run = Next(run);
		run->left = temp;
	}
	
	return head;
}

child_type_t ChildType(node_t *node)
{
	if (NULL == node->parent)
	{
		return NONE;
	}
	
	if (node->parent->left_child == node)
	{
		return LEFT;
	}
	
	return RIGHT;
}

void InitNode(node_t *node, int *num, node_t *parent, node_t *left_child, node_t *right_child)
{
	node->num = num;
	node->parent = parent;
	node->left_child = left_child;
	node->right_child = right_child;
}

void PrintBST(node_t *head)
{
	node_t *run = Begin(head);
	printf("BST: "PURP);
	
	while (NULL != run)
	{
		printf("(%2d)->", *run->num);
		run = Next(run);
	}
	
	printf(RESET"\n");
}

void PrintSortedList(node_t *head)
{
	node_t *run = Begin(head);
	printf("DLL: "PURP"X<-");
	
	while (NULL != run)
	{
		printf("(%2d)<->", *run->num);
		run = run->right;
	}
	
	printf("X"RESET"\n");
}

void PrintSortedListBackWards(node_t *head)
{
	node_t *run = Begin(head);
	printf("DLL Backwards: "PURP"X<-");
	
	while (NULL != run->right)
	{
		run = run->right;
	}
	
	while (NULL != run)
	{
		printf("(%2d)->", *run->num);
		run = run->left;
	}
	
	printf("X"RESET"\n");
}


