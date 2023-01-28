#ifndef __OL3940_ITOA_H_
#define __OL3940_ITOA_H_

#include <stdio.h>	/* size_t, printf, snprintf */
#include <stdlib.h> /* malloc, free, atoi */

int AtoIBaseTen(const char *str);
char *ItoABaseTen(int num, char *str);
int CountDigits(int num);
char *ItoaForAnyBase(int num, char *str, int base);
int AtoIForAnyBase(const char *str, int base);
void PrintCharInFirstTwoStrNotInLast(char *str1, char *str2, char *str3);
void IsLittleEndian();
 
#endif
