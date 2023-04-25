/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Tomer				*
*	Date      : 25/04/2023			*
************************************/

#ifndef __ILRD__OL139_40__KNIGHT_TOUR_H__
#define __ILRD__OL139_40__KNIGHT_TOUR_H__

#define ROWS (5)
#define COLUMNS (5)

/*
* KnightTour description:
*	Find the route for knight.
*
* @param:
*   matrix - starting board.
*	row - starting point, row location.
*	col - starting point, col location.
*	ROWS - row size.
*	COLUMNS - col size.
* 
* @return:
*   Returns - if there is a valid soultion retuen 0, else return non zero.
*
* complexity
*	Time: O(8^n).
*	Space O(1)
*/
int KnightTour(int matrix[ROWS][COLUMNS], int row, int col);

/*
* PrintBoard description:
*	Print the soultion to the Knight Tour.
*
* @param:
*	solution - Pointer to the heap.
*	ROWS - row size.
*	COLUMNS - col size.
* 
* @return:
*    Returns - void.
*
* complexity
*	Time: O(ROWS * COLUMNS).
*	Space O(1)
*/
void PrintBoard(int solution[ROWS][COLUMNS]);

/*

------ ADVANCED ------ :

* PrintBoard description:
*	Print the soultion to the Knight Tour, with puppy that pop and walked on places.
*
* @param:
*	solution - Pointer to the heap.
*	ROWS - row size.
*	COLUMNS - col size.
* 
* @return:
*    Returns - void.
*
* complexity
*	Time: O(ROWS * COLUMNS).
*	Space O(1)
*/
/*void PoopingDog(int solution[ROWS][COLUMNS]);*/

#endif
