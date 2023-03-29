/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	*****				*
*	Date      : 29/03/2023			*
************************************/

#include <stdio.h>	/* printf */

#include "fsm.h"

#define U_LINE 	"\033[1m\033[4m"
#define RED   	"\033[1m\033[41m\x1B[30m"
#define GRN   	"\033[1m\033[42m\x1B[30m"
#define RESET 	"\033[0m"

#define TRUE 	(1)
#define FALSE 	(0)
#define FAILURE (1)
#define SUCCESS (0)

#define PRINT_TEST(x) ((TRUE == (x)) ? printf(GRN"SUCCESS!"RESET"\n\n") : printf(RED"FAILURE!, line %d"RESET"\n\n", __LINE__))
                                 	  
int main()
{
	char *str1 = "010101";
	char *str2 = "0111110";
	char *str3 = "110101";
	char *str4 = "00";
	char *str5 = "0";
	
	state_t result_state = INITIALE_STATE;
	
	printf(U_LINE"Test FSM:\n\n"RESET);
	
	result_state = InputReader(str1);
	PRINT_TEST(result_state == MIDDLE);
	
	result_state = InputReader(str2);
	PRINT_TEST(result_state == ACCEPTED);
	
	result_state = InputReader(str3);
	PRINT_TEST(result_state == ERROR);
	
	result_state = InputReader(str4);
	PRINT_TEST(result_state == ACCEPTED);
	
	result_state = InputReader(str5);
	PRINT_TEST(result_state == MIDDLE);
	
	return 0;
}
