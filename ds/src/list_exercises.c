/************************************
*	Developer :	Yossi Matzliah		*
*	Date      :	11.02.2023			*
*	Reviewer  :	Limor				*
************************************/

#include <stdio.h> /* size_t, printf */
#include <assert.h> /* assert */

#include "../../ds/include/list_exercises.h"

struct node
{
    void *data;
    node_t *next;
};

/**********************************************************/

node_t *Flip(node_t *head)
{
	node_t *prev = NULL;
	node_t *iter = NULL;
	node_t *next = NULL;
	
	assert(NULL != head);
	
	iter = head;
	while (NULL != iter) 
	{
		next = iter->next;	
		iter->next = prev;	 		
		prev = iter;				
		iter = next;			
	}
	
	head = prev;
	
	return head;
}

int HasLoop(const node_t *head)
{
	node_t *slow = NULL;
	node_t *fast = NULL;
	
	assert(NULL != head);
	
	slow = (node_t *)head;
	fast = (node_t *)head;
	
	while (NULL != slow && NULL != fast && NULL != fast->next) 
	{
		slow = slow->next;
		fast = fast->next->next;

		if (slow == fast) 
		{
			return 1;
		}
	}
	return 0;
}

static size_t ListLength(const node_t *head)
{
	node_t *iter = (node_t *)head;
	size_t count = 0;
	
	while (NULL != iter)
	{
		++count;
		iter = iter->next;
	}
	
	return count;
}


node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	node_t *run_1 = NULL;
	node_t *run_2 = NULL;
	
	size_t len1 = 0;
	size_t len2 = 0;

	assert(head_1);
	assert(head_2);
	
	len1 = ListLength(head_1);
	len2 = ListLength(head_2);
	
	run_1 = head_1;
	run_2 = head_2;
	
	while (len1 > len2)
	{
		run_1 = run_1->next;
		--len1;
	}
	while (len2 > len1)
	{
		run_2 = run_2->next;
		--len2;
	}
	
	while (run_1 != run_2) 
	{
		run_1 = run_1->next;
		run_2 = run_2->next;
	}
	
	return run_1;
}

void PrintList(const node_t *head)
{
	node_t *iter = (node_t *)head;
	
	while (NULL != iter->next)
	{
		printf("%d, ", *(int *)iter->data);
		iter = iter-> next;
	}
	
	printf("%d. ", *(int *)iter->data);
	printf("\n");	
}

