/**************************************
*	Developer :	Yossi Matzliah        *
*	Reviewer  :	"MedalCollector" Oran *
*	Date      : 18/03/2023			  *
**************************************/

#include <assert.h>	/* assert */
#include <string.h>	/* strncmp */

#include "recursion.h"

#define EQUAL	(0)
#define FALSE	(0)
#define TRUE	(1)

/************** static func *****************/

static void SortAndInsert(stack_t *stack, int *data);

/********************************************/

int FiboIter(int element_index)
{
	int num_1 = 0;
	int num_2 = 1;
	int fib = 0;
	
	assert(0 < element_index);
	
	if (2 == element_index)
	{
		return num_2;
	}
	
	while (element_index > 2)
	{
		fib = num_1 + num_2;
		num_1 = num_2;
		num_2 = fib;
		--element_index;
	}
	
	return fib;
}

int FiboRec(int element_index)
{
	assert(0 < element_index);
	
	if (1 == element_index)	
    {
        return 0;
    }
    
    else if (2 == element_index)
	{
		return 1;
	}
	else
	{
		return FiboRec(element_index - 1) + FiboRec(element_index - 2);
	}
}

node_t *FlipList(node_t *node)
{
	node_t *new_head = NULL;

	if ((NULL == node) || (NULL == node->next))
	{
		return node;
	}
	
	new_head = FlipList(node->next);
	node->next->next = node;
	node->next = NULL;
	
	return new_head;
}

void SortUnsortedStack(stack_t *stack)
{
	int data = 0;
	
	assert(NULL != stack);
	
	if (FALSE == StackIsEmpty(stack))
	{
		data = *(int *)StackPeek(stack);
		StackPop(stack);
		SortUnsortedStack(stack);
		SortAndInsert(stack, &data);
	}
}

size_t StrLenRec(const char *src)
{
	if ('\0' == *src)
	{
		return 0;
	}
	
	return 1 + StrLenRec(src + 1);
}

int StrCmpRec(const char *str1, const char *str2)
{
	if(('\0' == *str1) ||  (0 != (*str1 - *str2)))
	{
		return *str1 - *str2;
	}
	
	return StrCmpRec((str1 + 1), (str2 + 1));
}

char *StrCpyRec(char *dest, const char *src)
{
	*dest = *src;
	
	if ('\0' != *src)
	{
		StrCpyRec((dest + 1), (src + 1));
	}
	
	return dest;
}

char *StrCatRec(char *dest, const char *src)
{
	if ('\0' != *dest)
	{
		StrCatRec(dest + 1 , src);
	}
	
	else
	{
		StrCpyRec(dest, src);
	}
	
	return dest;
}

char *StrStrRec(const char *haystack, const char *needle)
{
	int cmp_val = 0;
	
	if ('\0' == *haystack)
	{
		return NULL;
	}
	
	if (*haystack == *needle)
	{
		cmp_val = strncmp(haystack, needle, StrLenRec(needle));
		if (EQUAL == cmp_val)
		{
			return (char *)haystack;
		}
	}
	
	return StrStrRec(haystack + 1, needle);
}

/***********************************************************************/

static void SortAndInsert(stack_t *stack, int *data)
{	
	int tmp_data = 0;
	
	if ((TRUE == StackIsEmpty(stack)) || (*data > *(int *)StackPeek(stack)))
	{
		StackPush(stack, (void *)data);
	}
	
	else
	{
		tmp_data = *(int *)StackPeek(stack);
		StackPop(stack);
		SortAndInsert(stack, data);
		StackPush(stack, &tmp_data);
	}
}
