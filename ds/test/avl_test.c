/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Moses				*
*	Date      : 27/03/2023			*
************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc, free */
#include <string.h>	/* str funcs */
#include <assert.h>	/* assert */

#include "avl.h"

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

#define GET_ROOT_NODE(x) ((x)->dummy_root.children[LEFT])

typedef enum child_pos
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_CHILDREN = 2
}child_pos_t;

typedef struct avl_node avl_node_t;

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

/*****************************************************************/

static void TestAVLCreate();
static void TestAVLIsEmpty();
static void TestAVLInsertRemove();
static void TestAVLFind();
static void TestAVLForEach();
static void TestAVLHeight();

int CompareFunc(const void *data1, const void *data2);
int AddParam(void *data, void *parameter);
static void PrintTree(avl_node_t *node, int level);
static avl_node_t *GetLeftChild(avl_node_t *node_ptr);
static avl_node_t *GetRightChild(avl_node_t *node_ptr);
static void PrintTreeReport(avl_node_t *node);

/*****************************************************************/

int main()
{
	TestAVLCreate();
	TestAVLIsEmpty();
	TestAVLInsertRemove();
	TestAVLFind();
	TestAVLForEach();
	TestAVLHeight();
	
	return 0;
}

static void TestAVLCreate()
{
	avl_t *avl = NULL;
	 
	printf(U_LINE"Test AVL Create:\n"RESET);
	
	avl = AVLCreate(CompareFunc);
	
	PRINT_TEST(NULL != avl);

	AVLDestroy(avl);
}

static void TestAVLIsEmpty()
{
	avl_t *avl = NULL;
	 
	printf(U_LINE"Test AVL IsEmpty:\n"RESET);
	
	avl = AVLCreate(CompareFunc);
	
	PRINT_TEST(AVLIsEmpty(avl));

	AVLDestroy(avl);
}

static void TestAVLInsertRemove()
{
	int num1 = 10;
	int num2 = 2;
	int num3 = 8;
	int num4 = 5;
	int num5 = 18;
	int status = FAILURE;
	avl_t *avl = NULL;
	
	avl = AVLCreate(CompareFunc);
	
	printf(U_LINE"Test AVL Insert:"RESET"\n");
	
	status = AVLInsert(avl, (void *)&num1);
	/*PrintTreeReport(GET_ROOT_NODE(avl));*/
	AVLInsert(avl, (void *)&num2);
	/*PrintTreeReport(GET_ROOT_NODE(avl));*/
	PRINT_TEST(num1 == *(int *)GET_ROOT_NODE(avl)->data);
	AVLInsert(avl, (void *)&num3);
	/*PrintTreeReport(GET_ROOT_NODE(avl));*/
	PRINT_TEST(num3 == *(int *)GET_ROOT_NODE(avl)->data);
	AVLInsert(avl, (void *)&num4);
	/*PrintTreeReport(GET_ROOT_NODE(avl));*/
	AVLInsert(avl, (void *)&num5);
	
	PRINT_TEST(*(int *)(GetLeftChild(GET_ROOT_NODE(avl))->data) == num2);
	
	PrintTreeReport(GET_ROOT_NODE(avl));
	
	PRINT_TEST(SUCCESS == status);

	PRINT_TEST(5 == AVLCount(avl));
	PRINT_TEST(3 == AVLHeight(avl));
	
	/*PrintTreeReport(GET_ROOT_NODE(avl));*/
	
	PrintTree(GET_ROOT_NODE(avl), 2);

	printf(U_LINE"Test AVL Remove:"RESET"\n");
	
	AVLRemove(avl, (void *)&num2);
	PRINT_TEST(*(int *)(GET_ROOT_NODE(avl)->data) == num3);
	/*PrintTreeReport(GET_ROOT_NODE(avl));
	printf("Tree after Remove:\n");
	PrintTree(GET_ROOT_NODE(avl), 2);*/
	
	AVLRemove(avl, (void *)&num4);
	PRINT_TEST(*(int *)(GET_ROOT_NODE(avl))->data == num1);
	
	/*PrintTreeReport(GET_ROOT_NODE(avl));
	PrintTree(GET_ROOT_NODE(avl), 2);*/
	
	AVLInsert(avl, (void *)&num4);
	AVLInsert(avl, (void *)&num2);
	/*PrintTreeReport(GET_ROOT_NODE(avl));
	PrintTree(GET_ROOT_NODE(avl), 2);*/
	AVLRemove(avl, (void *)&num5);
	PRINT_TEST(*(int *)(GetRightChild(GET_ROOT_NODE(avl))->data) == num1);
	/*PrintTreeReport(GET_ROOT_NODE(avl));
	PrintTree(GET_ROOT_NODE(avl), 2);*/
	
	AVLDestroy(avl);
}

static void TestAVLFind()
{
	avl_t *avl = NULL;

	int num1 = 50;
	int num2 = 33;
	int num3 = 77;
	int num4 = 10;
	int num5 = 52;
	int num6 = 13;
	
	int key = 33;
	
	printf(U_LINE"Test AVL Find:\n"RESET);
	
	avl = AVLCreate(CompareFunc);
	AVLInsert(avl, &num1);
	AVLInsert(avl, &num3);
	AVLInsert(avl, &num2);
	AVLInsert(avl, &num4);
	AVLInsert(avl, &num5);
	AVLInsert(avl, &num6);
	
	/*PrintTree(GET_ROOT_NODE(avl), 2);*/
	
	PRINT_TEST(key == *(int*)AVLFind(avl, &key));
	
	key = 100;
	
	PRINT_TEST(NULL == AVLFind(avl, &key));
	
	AVLDestroy(avl);
}

static void TestAVLForEach()
{
	avl_t *avl = NULL;

	int num1 = 50;
	int num2 = 33;
	int num3 = 77;
	int num4 = 10;
	int num5 = 55;
	int num6 = 15;
	
	int checker = FAILURE;
	int param_to_add = 1;
	
	printf(U_LINE"Test AVL ForEach:\n"RESET);
	
	avl = AVLCreate(CompareFunc);
	AVLInsert(avl, &num1);
	AVLInsert(avl, &num3);
	AVLInsert(avl, &num2);
	AVLInsert(avl, &num4);
	AVLInsert(avl, &num5);
	AVLInsert(avl, &num6);
	
	/*PrintTree(GET_ROOT_NODE(avl), 2);*/
	
	checker = AVLForEach(avl, AddParam, &param_to_add, IN_ORDER);
	PRINT_TEST(SUCCESS == checker);
	
	PRINT_TEST(51 == *(int*)GET_ROOT_NODE(avl)->data);
	
	checker = AVLForEach(avl, AddParam, &param_to_add, POST_ORDER);
	PRINT_TEST(SUCCESS == checker);
	PRINT_TEST(52 == *(int*)GET_ROOT_NODE(avl)->data);
	
	checker = AVLForEach(avl, AddParam, &param_to_add, PRE_ORDER);
	PRINT_TEST(SUCCESS == checker);
	PRINT_TEST(53 == *(int*)GET_ROOT_NODE(avl)->data);
	
	/*PrintTree(GET_ROOT_NODE(avl), 2);*/
	
	AVLDestroy(avl);
}

static void TestAVLHeight()
{
	avl_t *avl = NULL;


	int num1 = 50;
	int num2 = 33;
	int num3 = 77;
	int num4 = 10;
	int num5 = 52;
	int num6 = 13;
	
	size_t count = 6;
	size_t height = 3;
	
	printf(U_LINE"Test AVL Height:\n"RESET);
	
	avl = AVLCreate(CompareFunc);
	AVLInsert(avl, &num1);
	AVLInsert(avl, &num3);
	AVLInsert(avl, &num2);
	AVLInsert(avl, &num4);
	AVLInsert(avl, &num5);
	AVLInsert(avl, &num6);
	
	PRINT_TEST(count == AVLCount(avl));
	PRINT_TEST(height == AVLHeight(avl));
	
	/*PrintTree(GET_ROOT_NODE(avl), 2);*/
	
	AVLRemove(avl, (void *)&num5);
	--count;
	AVLRemove(avl, (void *)&num3);
	--count;
	AVLRemove(avl, (void *)&num4);
	--count;
	--height;
	PRINT_TEST(count == AVLCount(avl));
	/*PrintTree(GET_ROOT_NODE(avl), 2);
	PrintTreeReport(GET_ROOT_NODE(avl));*/
	PRINT_TEST(height == AVLHeight(avl));
	
	AVLDestroy(avl);
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

static void PrintTree(avl_node_t *node, int level)
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

static void PrintTreeReport(avl_node_t *node)
{
	if (NULL == node) return;
	printf("Data: %d   ", *(int*)node->data);
	if (NULL != node->children[LEFT])
		printf("L: %d  ", *(int*)node->children[LEFT]->data);
	if (NULL != node->children[RIGHT])
		printf("R: %d  ", *(int*)node->children[RIGHT]->data);
	printf("\n");
	PrintTreeReport(node->children[LEFT]);
	PrintTreeReport(node->children[RIGHT]);
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


