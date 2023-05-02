/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Yotam S				*
*	Date      : 01/05/2023			*
************************************/

#ifndef __ILRD__OL139_40__TRIE_H__
#define __ILRD__OL139_40__TRIE_H__

#include <stddef.h>     /* size_t */

typedef struct trie trie_t;
typedef struct trie_node trie_node_t;

trie_t *TrieCreate(unsigned int height);
void TrieDestroy(trie_t *trie);
int TrieInsert(trie_t *trie, unsigned int requested, unsigned int *result);
int TrieFree(trie_t *trie, unsigned int requested);
size_t TrieCountFree(const trie_t *trie);
int TrieIsEmpty(const trie_t *trie);

#endif
