/************************************
*	Developer :	Yossi Matzliah		*
*	Date      :	11.02.2023			*
*	Reviewer  :	Limor				*
************************************/

#include <stdio.h> /* printf */

#include "../../ds/include/list_exercises.h"

struct node
{
    void *data;
    node_t *next;
};

/*****************************/

void test(void);

int main()
{
	test();

	return 0;
}

void test(void)
{
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	
	int num10 = 10;
	int num11 = 11;
	int num12 = 12;
	
	int has_loop = 0;
	
	node_t node1;
	node_t node2;
	node_t node3;
	node_t node4;
	
	node_t node10;
	node_t node11;
	node_t node12;
	
	node_t *node_intersection = NULL;
	
	node1.data = (void *)&num1;
	node2.data = (void *)&num2;
	node3.data = (void *)&num3;
	node4.data = (void *)&num4;
	
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	
	node4.next = &node1;
	has_loop = HasLoop(&node1);
	
	(has_loop == 1) ? printf("\nHasLoop - SUCCESS!\n") : printf("FAIL!\n");
	
	node4.next = NULL;

	has_loop = HasLoop(&node1);

	(has_loop == 0) ? printf("HasLoop - SUCCESS!\n") : printf("FAIL!\n");
	
	node10.data = (void *)&num10;
	node11.data = (void *)&num11;
	node12.data = (void *)&num12;
	
	node10.next = &node11;
	node11.next = &node12;
	node12.next = &node3;
	
	node_intersection = FindIntersection(&node1, &node10);
	
	(NULL != node_intersection) ? printf("\nFindIntersection success\n") 
	: printf("FindIntersection FAILURE\n");
	
	if (*(int *)node_intersection->data == *(int *)node3.data)
	{
		printf("The value of the 1st mutual node = %d\n", *(int *)node_intersection->data);
	}
	
	printf("\nBefore Flip\n");
	PrintList(&node1);
	printf("After Flip\n");
	PrintList(Flip(&node1));
}

