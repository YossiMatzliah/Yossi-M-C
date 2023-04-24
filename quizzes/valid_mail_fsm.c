#include <stdio.h>	/* printf */

#define SUCCESS (0)
#define FAILURE (1)
#define TRUE (1)
#define FALSE (0)

#define INPUTS (256)

#define U	 	"\033[4m"	/* Under_Line */
#define B		"\033[1m"	/* BOLD */
#define RESET 	"\033[0m"
#define RED		"\x1B[31m"
#define GRN 	"\x1B[32m"
#define PRINT printf(B GRN "success\n" RESET) : printf(B RED "fail\n" RESET)

typedef enum states
{
	INIT = 0,
	WAITING_FOR_AT = 1,
	WAITING_FOR_DOMAIN = 2,
	WAITING_FOR_PERIOD = 3,
	WAITING_FOR_SOMETHING = 4,
	VALID = 5,
	BAD = 6,
	STATES = 7
} states_t;

static void InitFSMLUT(int a[STATES][INPUTS])
{
	int i = 0;
	int j = 0;
	
	for (i = 0; i < STATES; ++i)
	{
		for (j = 0; j < INPUTS; ++j)
		{
			a[i][j] = BAD;
		}
	}
	
	for (i = '0'; i < '9'; ++i)
	{
		a[INIT][i] = WAITING_FOR_AT;
		a[WAITING_FOR_AT][i]= WAITING_FOR_AT;
		a[WAITING_FOR_DOMAIN][i]= WAITING_FOR_PERIOD;
		a[WAITING_FOR_PERIOD][i]= WAITING_FOR_PERIOD;
		a[WAITING_FOR_SOMETHING][i]= VALID;
		a[VALID][i]= VALID;
	}
	
	for (i = 'a'; i < 'z'; ++i)
	{
		a[INIT][i] = WAITING_FOR_AT;
		a[WAITING_FOR_AT][i]= WAITING_FOR_AT;
		a[WAITING_FOR_DOMAIN][i]= WAITING_FOR_PERIOD;
		a[WAITING_FOR_PERIOD][i]= WAITING_FOR_PERIOD;
		a[WAITING_FOR_SOMETHING][i]= VALID;
		a[VALID][i]= VALID;
	}
	
	for (i = 'A'; i < 'Z'; ++i)
	{
		a[INIT][i] = WAITING_FOR_AT;
		a[WAITING_FOR_AT][i]= WAITING_FOR_AT;
		a[WAITING_FOR_DOMAIN][i]= WAITING_FOR_PERIOD;
		a[WAITING_FOR_PERIOD][i]= WAITING_FOR_PERIOD;
		a[WAITING_FOR_SOMETHING][i]= VALID;
		a[VALID][i]= VALID;
	}
	
	a[INIT]['-'] = WAITING_FOR_AT;
	a[INIT]['_'] = WAITING_FOR_AT;
	a[INIT]['.'] = WAITING_FOR_AT;
	
	a[WAITING_FOR_AT]['-'] = WAITING_FOR_AT;
	a[WAITING_FOR_AT]['_'] = WAITING_FOR_AT;
	a[WAITING_FOR_AT]['.'] = WAITING_FOR_AT;
	a[WAITING_FOR_AT]['@'] = WAITING_FOR_DOMAIN;
	
	a[WAITING_FOR_DOMAIN]['-'] = WAITING_FOR_PERIOD;
	a[WAITING_FOR_DOMAIN]['_'] = WAITING_FOR_PERIOD;
	a[WAITING_FOR_DOMAIN]['.'] = WAITING_FOR_PERIOD;
	
	a[WAITING_FOR_DOMAIN]['-'] = WAITING_FOR_PERIOD;
	a[WAITING_FOR_DOMAIN]['_'] = WAITING_FOR_PERIOD;
	a[WAITING_FOR_DOMAIN]['.'] = WAITING_FOR_PERIOD;
	
	a[WAITING_FOR_PERIOD]['-'] = WAITING_FOR_PERIOD;
	a[WAITING_FOR_PERIOD]['_'] = WAITING_FOR_PERIOD;
	a[WAITING_FOR_PERIOD]['.'] = WAITING_FOR_SOMETHING;
	
	a[WAITING_FOR_SOMETHING]['-'] = VALID;
	a[WAITING_FOR_SOMETHING]['_'] = VALID;
	a[WAITING_FOR_SOMETHING]['.'] = VALID;
	
	a[VALID]['-'] = VALID;
	a[VALID]['_'] = VALID;
	a[VALID]['.'] = VALID;
}

int ValidEmail(const char *s)
{
	states_t state = INIT;
	char *run = NULL;
	static int fsm[STATES][INPUTS] ={{INIT}};
	
	run = (char *)s;
	
	if (INIT == fsm[INIT]['0'])
	{
		InitFSMLUT(fsm);
	}
	
	while ('\0' != *run)
	{
		state = fsm[state][(int)*run];
		++run;
	}

	return state == VALID;
}

int main()
{
	printf(B U"Testing Valid Email FSM:"RESET"\n");
	printf(U"Part I - Valid emails"RESET"\n");
	1 == ValidEmail("OranFreidin@gmail.com") ? PRINT;
	1 == ValidEmail("alex@haha.com") ? PRINT;
	1 == ValidEmail("vova123@gmail.co.uk") ? PRINT;
	1 == ValidEmail("vova123@gmail.co.uk_-.") ? PRINT;
	1 == ValidEmail("adi.morag@gmail.co.il") ? PRINT;
	1 == ValidEmail("...@...") ? PRINT;
	1 == ValidEmail("_@...") ? PRINT;
	1 == ValidEmail("-@...") ? PRINT;
	1 == ValidEmail(".@...") ? PRINT;
	1 == ValidEmail("NiMbUs2000@yes123..") ? PRINT;
	
	printf(U"Part II - Invalid emails"RESET"\n");
	0 == ValidEmail("OranFreidin@@gmail.com")  ? PRINT;
	0 == ValidEmail("OranFreidin@..") ? PRINT;
	0 == ValidEmail("OranFreidin@gmailcom") ? PRINT;
	0 == ValidEmail("...@..") ? PRINT;
	0 == ValidEmail("nimbus@yes-com") ? PRINT;
	0 == ValidEmail("nimbus2000@yes_com") ? PRINT;
	0 == ValidEmail("gi^di@gmail.com") ? PRINT;

	return 0;
}
