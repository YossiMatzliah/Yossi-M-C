#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>

/* StrLen: return the length of a pointer */
size_t StrLen (const char *s);

/* StrCmp: function compares two strings s1 and s2 lexicographically-wise. 
   		Returns for each iteration:
   • 0, if the s1 and s2 are equal;
   • a negative value if s1 is less than s2;
   • a positive value if s1 is greater than s2.
*/
int StrCmp(const char *s1, const char *s2);


/* StrCpy: function coppies string source to destination. */
char *StrCpy (char *dest, const char *src);
 
/* StrNCpy: function coppies n bytes (amount) of characters from 
string source to destination. */
char *StrNCpy(char *dest, const char *src, size_t n);

/* StrNCmp: function compares the first n bytes (amount)of 
two strings s1 and s2 lexicographically-wise. 
   		Returns for each iteration:
   • 0, if the s1 and s2 are equal;
   • a negative value if s1 is less than s2;
   • a positive value if s1 is greater than s2.
*/
int StrNCmp(const char *s1, const char *s2, size_t n);

/* StrCaseCmp: function compares two strings s1 and s2 lexicographically-wise
   while upper-case are lowered to low-case
   		Returns for each iteration:
   • 0, if the s1 and s2 are equal;
   • a negative value if s1 is less than s2;
   • a positive value if s1 is greater than s2.
*/
int StrCaseCmp(const char *s1, const char *s2);

/* StrChr: function that search for the first incaunter with a specific char.
	returns:
	• if finds: pointer to the first incaunter;
    • if don't: NULL;
*/
char *StrChr (const char *s, int c);

/* StrDup: function that duplicate a string to new allocated memory address.
	returns:
	pointer to the new allocated copy  
*/
char *StrDup(const char *s);

/*  StrCat: function that appends a string from source to dest, 
	overwrite null-terminator.
	returns:
	pointer to the resulting string dest
*/
char *StrCat(char *dest, const char *src);

/*  StrNCat: function that appends the first n bytes from a string 
	of source to dest, overwrite null-terminator.
	returns:
	pointer to the resulting string dest
*/
char *StrNCat(char *dest, const char *src, size_t n);

/*  StrStr: function finds the first occurrence of the substring needle
	in the string haystack.  The terminating null bytes ('\0')
    are not compared.
    return a pointer to the beginning of the located substring, 
    or NULL if the substring is not found  
*/       
char *StrStr(const char *haystack, const char *needle);

/*  The function calculates the length (in bytes) of the initial 
	segment of s which consists entirely of bytes in accept.
	returns the number of bytes in the initial segment
	of s which consist only of bytes from accept
*/
size_t StrSpn(const char *s, const char *accept);



