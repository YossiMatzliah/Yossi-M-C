/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Or	  				*
*	Date      : 14/03/2023			*
************************************/

#ifndef __ILRD_OL139_40_SORT_H__
#define __ILRD_OL139_40_SORT_H__

#include <stddef.h>	/* size_t */

/*
* BubbleSort Description:
* Sorts the array using the "Bubble Sort" method.
*
* @Params:
*  	array - The array to be sorted.
*		If array is invalied - behavior is undefined.
*  	size - The size of the array to be sorted.
*		If size is not the real size of array, function won't work well.
*	cmp_func - A pointer to the compare function.
*
* @Returns:
* 	none
*
* @Complexity
* 	Time: O(n^2)
*	Space: O(1)
*/
void BubbleSort(int array[], size_t size, int (*cmp_func)(const int lhs, const int rhs));

/*
* InsertionSort Description:
* Sorts the array using the "Insertion Sort" method.
*
* @Params:
*  	array - The array to be sorted.
*		If array is invalied - behavior is undefined.
*  	size - The size of the array to be sorted.
*		If size is not the real size of array, function won't work well.
*	cmp_func - A pointer to the compare function.
*
* @Returns:
* 	none
*
* @Complexity
* 	Time: O(n^2)
*	Space: O(1)
*/
void InsertionSort(int array[], size_t size, int (*cmp_func)(const int lhs, const int rhs));

/*
* SelectionSort Description:
* Sorts the array using the "Selection Sort" method.
*
* @Params:
*  	array - The array to be sorted.
*		If array is invalied - behavior is undefined.
*  	size - The size of the array to be sorted.
*		If size is not the real size of array, function won't work well.
*	cmp_func - A pointer to the compare function.
*
* @Returns:
* 	none
*
* @Complexity
* 	Time: O(n^2)
*	Space: O(1)
*/
void SelectionSort(int array[], size_t size, int (*cmp_func)(const int lhs, const int rhs));

/*
* CountingSort Description:
* Sorts the array using the "Counting Sort" method
*
* @Params:
*	array - The array to be sorted
*	size - The size of the array to be sorted
*		If size is not the real size of array, function won't work well.
*
* @Returns:
*   0 in case of success
*   1 in case of failure
*
* @Complexity
*   Time: O(n + k)
*   Space: O(k)
*
*   k is the difference between the largest and smallest elements
*/
int CountingSort(int array[], size_t size);

/*
* RadixSort Description:
* Sorts the array using the "Radix Sort" method
*
* @Params:
*	array - The array to be sorted
*	size - The size of the array to be sorted
*		If size is not the real size of array, function won't work well.
*
* @Returns:
*	0 in case of success
*	1 in case of failure
*
* @Complexity
*	Time: O(n * k)
*	Space: O(n)
*    
*	k is the number of digits in the largest element 
*/
int RadixSort(int array[], size_t size);

#endif

