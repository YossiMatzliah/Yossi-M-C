#define SUCCESS (0)
#define FAILURE (1)
#define TRUE (1)
#define FALSE (0)

#define U	 	"\033[4m"	/* Under_Line */
#define B		"\033[1m"	/* BOLD */
#define BOLD_RED 	"\033[1m\033[41m\x1B[30m"
#define BOLD_BLUE	"\033[1m\033[44m\x1B[30m"

#define RESET 	"\033[0m"
#define BOLD_GRN	"\033[1m\033[42m\x1B[30m"

#define BLK 	"\x1B[30m"
#define RED		"\x1B[31m"
#define GRN 	"\x1B[32m"
#define YLW 	"\x1B[33m"
#define BLUE 	"\x1B[34m"
#define PURP 	"\x1B[35m"
#define CYAN 	"\x1B[36m"
#define WHITE 	"\x1B[37m"

#define BG_BLK	"\x1B[40m"
#define BG_RED	"\x1B[41m"
#define BG_GRN	"\x1B[42m"
#define BG_YLW 	"\x1B[43m"
#define BG_BLUE	"\x1B[44m"
#define BG_PURP	"\x1B[45m"
#define BG_CYAN	"\x1B[46m"
#define BG_WHITE	"\x1B[47m"

#define RESET 	"\033[0m"

#define TEST	B U
#define SUB_TEST	U

#define PRINT printf(B GRN "success\n" RESET) : printf(B RED "fail\n" RESET)



