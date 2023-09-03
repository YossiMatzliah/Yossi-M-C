/************************************
*	Developer :	Yossi Matzliah		*
*	Date      :	11.02.2023			*
*	Reviewer  :	Limor				*
************************************/

#ifndef __LINKED_LIST_EX_H__
#define __LINKED_LIST_EX_H__

typedef struct node node_t;

/**********************************************************/

/* Reverse the order of a given slist. */
node_t *Flip(node_t *head);

/* Tells whther a given slist has loop. */
int HasLoop(const node_t *head);

/* Returns a pointer to a first node mutual to both slists, if any. */
node_t *FindIntersection(node_t *head_1, node_t *head_2);

/* Prints the list. */
void PrintList(const node_t *head);

#endif
