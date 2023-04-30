/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :					*
*	Date      : /04/2023			*
************************************/

#ifndef __ILRD__OL139_40__TRIE_H__
#define __ILRD__OL139_40__TRIE_H__

#include <stddef.h>     /* size_t */

typedef struct trie trie_t;
typedef struct trie_node trie_node_t;

typedef enum trie_status
{
    SUCCESS = 0,
    FAILURE = 1,
    FULL_TREE = 2,
    DOUBLE_FREE = 3,
    DS_FAILURE = 4,
    SEARCH_BIGGER = 5,
    FIND_SMALLER = 6
} trie_status_t;

trie_t *TrieCreate(unsigned int height);
void TrieDestroy(trie_t *trie);
int TrieInsert(trie_t *trie, unsigned int requested, unsigned int *result);
int TrieFree(const trie_t *trie, unsigned int requested);
size_t TrieCountFree(const trie_t *trie);

#endif
