/**************************************
*	Developer :	Yossi Matzliah        *
*	Reviewer  :	"MedalCollector" Oran *
*	Date      : 18/03/2023			  *
**************************************/

#ifndef __RECURSION_H__
#define __RECURSION_H__

#include "stack.h"

typedef struct node node_t;

struct node
{
	int *data;
	node_t *next;
};

/***********************************************************/

/*
* FiboIter Description:
*	Finds the number of a requested index in Fibonacci sequence.
*		The implamention is iteratively.
*
* @Params:
*	element_index - The index of the Fibonacci sequence that want to check.
*
* @Returns:
*	Return the number corresponding to the index in Fibonacci sequence.
*
* @Complexity
*	Time: O(n)
*	Space: O(1)
*/
int FiboIter(int element_index);

/*
* FiboRec Description:
*	Finds the number of a requested index in Fibonacci sequence.
*		The implamention is recursively.
*
* @Params:
*	element_index - The index of the Fibonacci sequence that want to check.
*
* @Returns:
*	Return the number corresponding to the index in Fibonacci sequence.
*
* @Complexity
* 	Time: O(2 ^ n)
*	Space: O(n)
*/
int FiboRec(int element_index);

/*
* FlipList Description:
* 	Flips the given list recursively.
*
* @Params:
*	node - Pointer to the first node (the head) of the list.
*
* @Returns:
*	NULL - If the list is empty.
*	node_t pointer - Pointer to the new head.
*
* @Complexity
*	Time: O(n)
*	Space: O(n)
*/
node_t *FlipList(node_t *node);

/*
* SortUnsortedStack Description:
* 	The function sort a give stack of ints, the highest number is at the top.
*  
* @Params:
*  	stack - Pointer to the stack.
*
* @Returns:
*	none.
*
* @Complexity
* 	Time: O(n ^ 2)
*	Space: O(n)
*/
void SortUnsortedStack(stack_t *stack);

/*
* StrLenRec Description:
*	Counts the number of charecters in a given string recursively.
* 		Note - The null terminator is not included.
*
* @Params:
*	src - The src string.
*
* @Returns:
*	The number of characters in the string.
*
* @Complexity
*	Time: O(n)
*	Space: O(n)
*/
size_t StrLenRec(const char *src);

/*
* StrCmpRec Description:
* 	The function compares two strings s1 and s2 lexicographically-wise recursively.
*
* @Params:
*  	str1 - one string to compare.
*	str2 - other string to compare to.
*
* @Returns:
* 	for each iteration:
*		0, if the str1 and str2 are equal.
*		A negative value if str1 is less than str2.
*		A positive value if s1str1is greater than str2.
*
* @Complexity
* 	Time: O(n)
*	Space: O(n)
*/
int StrCmpRec(const char *str1 , const char *str2);

/*
* StrCpyRec Description:
* 	The function copies the string form src to dest including the 
*	NULL terminator recursively.
*  
* @Params:
*  	dest - The string to copy to.
*	src - The string to copy from.
*
* @Returns:
*	Pointer to dest.
*
* @Complexity
* 	Time: O(n)
*	Space: O(n)
*/
char *StrCpyRec(char *dest, const char *src);

/*
* StrCatRec Description:
*	The function appends the string form src to dest recursively.
* 		Note - The NULL terminator in dest will be overwritten but will be appended at the
*  end.
*  
* @Params:
*  	dest - The string to copy to.
*	src - The string to copy from.
*
* @Returns:
*	Pointer to dest.
*
* @Complexity
* 	Time: O(n)
*	Space: O(n)
*/
char *StrCatRec(char *dest , const char *src);

/*
* StrStrRec Description:
*	The function searches the string "needle" in the string "haystack" (excluding the 
*  	NULL terminator) recursively.
*  
* @Params:
*  	haystack - The string search in.
*	needle - The string to serached for.
*
* @Returns:
*	Pointer to the first occurrence of the string needle in haystack.
*	NULL - if not found.
*
* @Complexity
* 	Time: O(n)
*	Space: O(n)
*/
char * StrStrRec(const char *haystack, const char *needle);

#endif
