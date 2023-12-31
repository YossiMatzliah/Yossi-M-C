/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Tomer				*
*	Date      : 25/04/2023			*
************************************/

#include <stdio.h>	

#include "knight.h"

#define U_LINE 	"\033[1m\033[4m"
#define RED   	"\033[1m\033[41m\x1B[30m"
#define GRN   	"\033[1m\033[42m\x1B[30m"
#define RESET 	"\033[0m"

#define TRUE 	(1)
#define FALSE 	(0)
#define SUCCESS (0)
#define FAILURE (1)

#define PRINT_TEST(x) ((TRUE == (x)) ? printf(GRN"SUCCESS!"RESET"\n\n") : printf(RED"FAILURE!, line %d"RESET"\n\n", __LINE__))

#define NEW_LINE printf("\n")



/*****************************************************************/

static void  TestKnightTour();

/*****************************************************************/

int main()
{
	TestKnightTour();

	return 0;
}

/**************************************************************/

static void TestKnightTour()
{
	int board[ROWS][COLUMNS] = {{0}};
	
	printf(U_LINE"\nTest Knight's Tour ( + Print Board):\n\n"RESET);

	PRINT_TEST(SUCCESS == KnightTour(board, 0, 0));
	PrintBoard(board);

	/*PRINT_TEST(SUCCESS == KnightTour(board, 3, 7));*/	/* board 8X8 */
	/*PrintBoard(board);*/

	PRINT_TEST(SUCCESS == KnightTour(board, 2, 2));
	PrintBoard(board);

	PRINT_TEST(FAILURE == KnightTour(board, 3, 2)); /* board 5X5 */
	PRINT_TEST(SUCCESS == KnightTour(board, 1, 3));
	PrintBoard(board);

	PRINT_TEST(SUCCESS == KnightTour(board, 0, 4));
	PrintBoard(board);
}
