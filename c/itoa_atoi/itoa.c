/********************************
*	Developper: Yossi Matzliah	*
*	Date: 		28/01/2023		*
*	Reviewer:	Yotam			*
********************************/

#include <string.h> /* strlen */
#include <ctype.h> /* isdigit, isalpha, toupper */
#include "itoa.h"
#define ALPHABET_NUM 26

typedef enum flag_t {NEG = -1, ZERO, POS} flag_t;

flag_t flag = POS;	

int TenExpN(int n)
{
	int i = 0;	
	int x = 10, result = 1;
	
	for (i = 0; i < n; ++i)
	{
		result *= x;
	}
	
	return result;
}

int AtoIBaseTen(const char *str)
{
	int i = 0; 
	int num = 0;
	int len = strlen(str);
	flag = POS;
	
	for (i = 0; i < len; ++i)
	{
		if ('-' == *str && POS == flag)
		{
			++i;
			flag = NEG;
		}
		
		num += ((*(str + i) - '0') * (TenExpN(len - i - 1)));
	}
	
	if (NEG == flag)
	{
		num = -num;
	}
	
	return num;
}	



char *ItoABaseTen(int num, char *str)
{
	int len = CountDigits(num);
	char *runner = str;

	if( num == ZERO)
	{
		*str = '0';
		++runner;
	}
	
	if(num < 0)
	{
		*str = '-';
		++runner;
		num *= -1;
	}

	while(len > 0)
	{
		--len;
		++runner;
	}
	
	*runner = '\0';
	--runner;
	
	while(num > 0)
	{
		*runner = ('0' + (num % 10));
		num /= 10;
		--runner;
	}

	return str;
}

char *ItoaForAnyBase(int num, char *str, int base)
{
	int count = 1;
	int tmp_num = num;
	char *runner = str;	

	if (2 > base || 36 < base)
	{
		return NULL;
	} 
    
	if (num < 0) 
	{
		*runner = '-';
		tmp_num = -num;
		num = -num;
		++str;
	}

	while (base <= tmp_num)
	{
		++count;
		tmp_num /= base;
	}
    		
	runner += count;
	*runner = '\0';
	
	do 
	{
		*--runner = (num % base) + (num % base > 9 ? 'A' - 10 : '0');
		num /= base;
	} while (num);

	return str;
}

int AtoIForAnyBase(const char *str, int base) 
{
	int num = 0, tmp = 0;
	flag = ZERO;	
	
	if(10 == base && '-' == *str)
	{
		flag = NEG;
		++str;
	}
	
	while('\0' != *str)
	{
		tmp = *str;
		
		if(tmp >= '0' && tmp <= '9')
		{
			tmp -= '0';
		}
		
		else
		{
		 	if(tmp >= 'A' && tmp <= 'Z') 
			{
				tmp -= ('A' - 10);
			}
			
			else
			{
				break;
			}
		}		
		num = ((base * num) + tmp);
		++str;
	}
	
	if (NEG == flag)
	{
		num *= -1;
	}
	 
	return num;
}

static void PrintLowerCaseMutualChar(char *str)
{
	size_t i = 0;
		
	for(i = 0; i < ALPHABET_NUM + 1; ++i)
	{
		if('2' == str[i])
		{
			printf("%c ", (char)('a' + i));
		}
	}
	printf("\n");
}

static void PrintUpperCaseMutualChar(char *str)
{
	size_t i = 0;

	for(i = 0; i < ALPHABET_NUM + 1; ++i)
	{
		if('2' == str[i])
		{
			printf("%c ", (char)('A' + i));
		}
	}
	printf("\n");
}

void LettersOnlyInFirstTwo(char *str1, char *str2, char *str3)
{
	char lower_case_abc[ALPHABET_NUM + 1] = {0};
	char upper_case_abc[ALPHABET_NUM + 1] = {0};
	
	while ('\0' != *str1)
	{
		if (0 != islower(*str1))
		{
			lower_case_abc[*str1 - 'a'] = '1';
		}
		
		else if (0 != isupper(*str1))
		{
			upper_case_abc[*str1 - 'A'] = '1';
		}
		++str1;
	}
	
	while ('\0' != *str2)
	{
		if ((0 != islower(*str2)) && ('1' == lower_case_abc[*str2 - 'a']))
		{
			lower_case_abc[*str2 - 'a'] = '2';
		}
		
		else if ((0 != isupper(*str2)) && ('1' == upper_case_abc[*str2 - 'A']))
		{
			upper_case_abc[*str2 - 'A'] = '2';
		}
		++str2;
	}
	
	while('\0' != *str3)
	{
		if (0 != islower(*str3))
		{
			lower_case_abc[*str3 - 'a'] = '0';
		}
		
		else if (0 != isupper(*str3))
		{
			upper_case_abc[*str3 - 'A'] = '0';
		}
		++str3;
	}

	PrintLowerCaseMutualChar(lower_case_abc);
	PrintUpperCaseMutualChar(upper_case_abc);
}

void IsLittleEndian()
{
	unsigned int value = 1;
    char *ptr = (char *)&value;
 
	if (1 == *ptr)
    { 
		printf("Your system is Little endian.\n");
	}
	
	else
	{
		printf("Your system is Big endian.\n");
	}
}
