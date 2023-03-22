/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Daniel				*
*	Date      : 21/03/2023			*
************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc, free */
#include <string.h>	/* str funcs */

#include "bst.h"

#define U_LINE 	"\033[1m\033[4m"
#define RED   	"\033[1m\033[41m\x1B[30m"
#define GRN   	"\033[1m\033[42m\x1B[30m"
#define RESET 	"\033[0m"

#define TRUE 	(1)
#define FALSE 	(0)
#define FAILURE (1)
#define SUCCESS (0)

#define PRINT_TEST(x) ((TRUE == (x)) ? printf(GRN"SUCCESS!"RESET"\n\n") : printf(RED"FAILURE!, line %d"RESET"\n\n", __LINE__))

#define NEW_LINE printf("\n")

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

/*****************************************************************/

static void TestBSTCreate();
static void TestBSTIsEmpty();
static void TestBSTInsertRemove();
static void TestBSTIter();
static void TestBSTFind();
static void TestBSTForEach();
static void TestBSTHeight();

int CompareFunc(const void *data1, const void *data2);
int AddParam(void *data, void *parameter);
static void PrintTree(bst_node_t *node, int level);

/*****************************************************************/

int main()
{
	TestBSTCreate();
	TestBSTIsEmpty();
	TestBSTInsertRemove();
	TestBSTIter();
	TestBSTFind();
	TestBSTForEach();
	TestBSTHeight();
	
	return 0;
}

static void TestBSTCreate()
{
	bst_t *bst = NULL;
	 
	printf(U_LINE"Test BST Create:\n"RESET);
	
	bst = BSTCreate(CompareFunc);
	
	PRINT_TEST(NULL != bst);

	BSTDestroy(bst);
}

static void TestBSTIsEmpty()
{
	bst_t *bst = NULL;
	 
	printf(U_LINE"Test BST IsEmpty:\n"RESET);
	
	bst = BSTCreate(CompareFunc);
	
	PRINT_TEST(BSTIsEmpty(bst));

	BSTDestroy(bst);
}

static void TestBSTInsertRemove()
{
	int num1 = 10;
	int num2 = 2;
	int num3 = 8;
	int num4 = 5;
	int num5 = 18;
	bst_iter_t iter1 = NULL;
	bst_iter_t iter2 = NULL;
	bst_iter_t iter3 = NULL;
	bst_iter_t iter4 = NULL;
	bst_iter_t iter5 = NULL;
	bst_t *bst = NULL;
	
	bst = BSTCreate(CompareFunc);
	
	printf(U_LINE"Test BST Insert:"RESET"\n");
	
	iter1 = BSTInsert(bst, (void *)&num1);
	iter2 = BSTInsert(bst, (void *)&num2);
	iter3 = BSTInsert(bst, (void *)&num3);
	iter4 = BSTInsert(bst, (void *)&num4);
	iter5 = BSTInsert(bst, (void *)&num5);
	
	PrintTree(iter1, 2);
	
	PRINT_TEST(num1 == *(int *)BSTGetData(iter1));
	
	PRINT_TEST(num4 == *(int *)BSTGetData(iter3->children[LEFT]));	
	
	PRINT_TEST(num3 == *(int *)BSTGetData(iter2->children[RIGHT]));	
	
	PRINT_TEST(NULL == iter5->children[RIGHT]);
	
	printf(U_LINE"Test BST Remove:"RESET"\n");
	
	BSTRemove(iter3);			
	PRINT_TEST(num4 == *(int *)BSTGetData(iter2->children[RIGHT]));
	
	BSTRemove(iter1);			
	PRINT_TEST(num5 == *(int *)BSTGetData(bst->dummy_root.children[LEFT]));	
	
	BSTRemove(iter4);
	PRINT_TEST(NULL == iter2->children[RIGHT]);
	
	BSTDestroy(bst);
}

static void TestBSTIter()
{
	bst_t *bst = NULL;

	bst_iter_t iter = NULL;
	bst_iter_t iter_prev = NULL;

	int num1 = 50;
	int num2 = 33;
	int num3 = 77;
	int num4 = 10;
	int num5 = 52;
	int num6 = 13;
	
	printf(U_LINE"Test BST Iterators:\n"RESET);
	
	bst = BSTCreate(CompareFunc);
	BSTInsert(bst, &num1);
	BSTInsert(bst, &num3);
	BSTInsert(bst, &num2);
	BSTInsert(bst, &num4);
	BSTInsert(bst, &num5);
	BSTInsert(bst, &num6);
	
	iter = BSTBeginIter(bst);
	PRINT_TEST(num4 == *(int *)BSTGetData(iter));
	
	iter = BSTNextIter(iter);
	PRINT_TEST(num6 == *(int *)BSTGetData(iter));
	
	iter = BSTNextIter(iter);
	PRINT_TEST(num2 == *(int *)BSTGetData(iter));
	
	iter = BSTNextIter(iter);
	PRINT_TEST(num1 == *(int *)BSTGetData(iter));
	
	iter = BSTNextIter(iter);
	PRINT_TEST(num5 == *(int *)BSTGetData(iter));
	
	iter_prev = BSTPrevIter(iter);
	PRINT_TEST(num1 == *(int *)BSTGetData(iter_prev));

	PRINT_TEST(FALSE == BSTIsSameIter(iter_prev, iter));
	iter = BSTPrevIter(iter);
	PRINT_TEST(TRUE == BSTIsSameIter(iter_prev, iter));
	
	iter = BSTNextIter(iter);
	PRINT_TEST(num5 == *(int *)BSTGetData(iter));
	iter = BSTNextIter(iter);
	PRINT_TEST(num3 == *(int *)BSTGetData(iter));
	
	iter = BSTNextIter(iter);
	PRINT_TEST(BSTEndIter(bst) == iter);
	
	BSTDestroy(bst);
}

static void TestBSTFind()
{
	bst_t *bst = NULL;

	bst_iter_t iter = NULL;

	int num1 = 50;
	int num2 = 33;
	int num3 = 77;
	int num4 = 10;
	int num5 = 52;
	int num6 = 13;
	
	int key = 33;
	
	printf(U_LINE"Test BST Find:\n"RESET);
	
	bst = BSTCreate(CompareFunc);
	BSTInsert(bst, &num1);
	BSTInsert(bst, &num3);
	BSTInsert(bst, &num2);
	BSTInsert(bst, &num4);
	BSTInsert(bst, &num5);
	BSTInsert(bst, &num6);
	
	iter = BSTFind(bst, &key);
	PRINT_TEST(key == *(int*)BSTGetData(iter));
	
	key = 100;
	iter = BSTFind(bst, &key);
	PRINT_TEST(NULL == iter);
	
	BSTDestroy(bst);
}

static void TestBSTForEach()
{
	bst_t *bst = NULL;

	bst_iter_t iter = NULL;
	bst_iter_t iter_from = NULL;
	bst_iter_t iter_to = NULL;

	int num1 = 50;
	int num2 = 33;
	int num3 = 77;
	int num4 = 10;
	int num5 = 52;
	int num6 = 13;
	
	int checker = FAILURE;
	int param_to_add = 1;
	
	printf(U_LINE"Test BST ForEach:\n"RESET);
	
	bst = BSTCreate(CompareFunc);
	iter = BSTInsert(bst, &num1);
	BSTInsert(bst, &num3);
	BSTInsert(bst, &num2);
	BSTInsert(bst, &num4);
	BSTInsert(bst, &num5);
	BSTInsert(bst, &num6);
	
	PrintTree(iter, 2);
	
	iter_from = BSTBeginIter(bst);
	iter_to = BSTEndIter(bst);
	
	checker = BSTForEach(iter_from, iter_to, AddParam, &param_to_add);
	PRINT_TEST(SUCCESS == checker);
	
	PRINT_TEST(11 == *(int*)BSTGetData(iter_from));
	
	PrintTree(iter, 2);
	
	BSTDestroy(bst);
}

static void TestBSTHeight()
{
	bst_t *bst = NULL;

	bst_iter_t iter = NULL;

	int num1 = 50;
	int num2 = 33;
	int num3 = 77;
	int num4 = 10;
	int num5 = 52;
	int num6 = 13;
	
	size_t size = 6;
	size_t height = 3;
	
	printf(U_LINE"Test BST Height:\n"RESET);
	
	bst = BSTCreate(CompareFunc);
	BSTInsert(bst, &num1);
	BSTInsert(bst, &num3);
	BSTInsert(bst, &num2);
	iter = BSTInsert(bst, &num4);
	BSTInsert(bst, &num5);
	BSTInsert(bst, &num6);
	
	PRINT_TEST(size == BSTSize(bst));
	PRINT_TEST(height == BSTHeight(bst));
	
	printf("height = %ld\n", BSTHeight(bst));
	
	BSTRemove(iter);
	
	--size;
	PRINT_TEST(size == BSTSize(bst));
	printf("height = %ld\n", BSTHeight(bst));
	
	PRINT_TEST(height - 1 == BSTHeight(bst));
	
	BSTDestroy(bst);
}


/******************************************************/

int AddParam(void *data, void *param)
{
	*(int *)data += *(int *)param;
	
	return SUCCESS;
}

int CompareFunc(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);  
}

static void PrintTree(bst_node_t *node, int level)
{
	int i = 0;
	
	if (NULL == node) 
	{
		return;
	}
	
	PrintTree(node->children[RIGHT], level + 1);
	
	for (i = 0 ; i < level ; ++i)
	{
        printf("    ");
	}
	printf("%d\n", *(int*)node->data);
	PrintTree(node->children[LEFT], level + 1);
}
