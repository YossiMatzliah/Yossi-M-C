#ifndef __WORD_BOUNDARY_H__
#define __WORD_BOUNDARY_H__
#include <stddef.h> /* size_t */
#include <stdio.h> /* printf, __WORDSIZE */


void *MemSet (void *str, int c, size_t n);
void *MemCpy (void *dest, const void *src, size_t n);
void *MemMove (void *dest, const void *src, size_t n);
void WordBounderyTest();


#endif
