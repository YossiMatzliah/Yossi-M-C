/********************************
*	Developper: Yossi Matzliah	*
*	Date: 		28/01/2023		*
*	Reviewer:	Yotam			*
********************************/

#include "itoa.h"
#define IS_LITTLE_ENDIAN() (((*(unsigned short*)"\0\xff") == 0xff ) ? (0) : (1))

static void AtoIBaseTenTest(); 
static void ItoABaseTenTest();
static void ItoaForAnyBaseTest();
static void AtoIForAnyBaseTest();
static void CompareAtois(const char *str, int base);
static void ThreeStrTest();
static void IsLittleEndianTest();

int main()
{
	ItoABaseTenTest();
	AtoIBaseTenTest(); 
	ItoaForAnyBaseTest();
	AtoIForAnyBaseTest();
	ThreeStrTest();
	IsLittleEndianTest();
	
	return 0;
}



int CountDigits(int num)
{
	int digits_counter = 0;
	
	while (0 != num)
	{
		num /= 10;
		++digits_counter;
	}
	
	return digits_counter;
}

static void AtoIBaseTenTest()
{
	const char *str1 = "123456";
	const char *str2 = "0";
	const char *str3 = "-156";
	
	printf("Tests for AtoIBaseTen :\n\n");
	
	printf("String1 is: %s\n", str1);
	printf("Num1 from str is: %d\n\nSUCCESS!\n\n", AtoIBaseTen(str1));
	
	printf("String2 is: %s\n", str2);
	printf("Num2 from str is: %d\n\nSUCCESS!\n\n", AtoIBaseTen(str2));
	
	printf("String3 is: %s\n", str3);
	printf("Num3 from str is: %d\n\nSUCCESS!\n\n", AtoIBaseTen(str3));
}

static void ItoABaseTenTest()
{
	int num1 = 12;
	int num2 = 0;
	int num3 = 12345678;
	int num4 = -478;
	int len1 = CountDigits(num1);
	int len2 = CountDigits(num2);
	int len3 = CountDigits(num3);
	int len4 = CountDigits(num4);
	char *str1 = (char *)malloc(len1 * sizeof(char) + 2);
	char *str2 = (char *)malloc(len2 * sizeof(char) + 2);
	char *str3 = (char *)malloc(len3 * sizeof(char) + 2);
	char *str4 = (char *)malloc(len4 * sizeof(char) + 2);
	
	printf("Tests for ItoABaseTen :\n\n");

	printf("num1 is: %d\n", num1);	
	printf("str1 from num is: %s\n\nSUCCESS!\n\n", ItoABaseTen(num1, str1));
	
	printf("num2 is: %d\n", num2);
	printf("str2 from num is: %s\n\nSUCCESS!\n\n", ItoABaseTen(num2, str2));

	printf("num3 is: %d\n", num3);
	printf("str3 from num is: %s\n\nSUCCESS!\n\n", ItoABaseTen(num3, str3));
	
	printf("num4 is: %d\n", num4);
	printf("str4 from num is: %s\n\nSUCCESS!\n\n", ItoABaseTen(num4, str4));
	
	free(str1);
	free(str2);
	free(str3);
	free(str4);
}

static void ItoaForAnyBaseTest()
{
	int num1 = 12;
	int num2 = 0;
	int num3 = 12345678;
	int base = 2;
	
	char *str1 = (char *)malloc(36 * sizeof(char) + 1);
	char *str2 = (char *)malloc(36 * sizeof(char) + 1);
	char *str3 = (char *)malloc(36 * sizeof(char) + 1);
	
	printf("Tests for ItoaForAnyBase :\n\n");
	
	printf("%d: to base %d. \n 1100 =? "
	"%s\nSUCCESS\n", num1, base, ItoaForAnyBase(num1, str1, base));
	printf("%d: to base %d. \n 0 =? "
	"%s\nSUCCESS\n", num2, base, ItoaForAnyBase(num2, str2, base));
	printf("%d: to base %d. \n 101111000110000101001110 =? "
	"%s\nSUCCESS\n", num3, base, ItoaForAnyBase(num3, str3, base));
	
	base = 8;
	printf("%d: to base %d. \n 14 =? "
	"%s\nSUCCESS\n", num1, base, ItoaForAnyBase(num1, str1, base));
	printf("%d: to base %d. \n 0 =? "
	"%s\nSUCCESS\n", num2, base, ItoaForAnyBase(num2, str2, base));
	printf("%d: to base %d. \n 57060516 =? "
	"%s\nSUCCESS\n", num3, base, ItoaForAnyBase(num3, str3, base));
	
	base = 10;
	printf("%d: to base %d. \n 12 =? "
	"%s\nSUCCESS\n", num1, base, ItoaForAnyBase(num1, str1, base));
	printf("%d: to base %d. \n 0 =? "
	"%s\nSUCCESS\n", num2, base, ItoaForAnyBase(num2, str2, base));
	printf("%d: to base %d. \n 12345678 =? "
	"%s\nSUCCESS\n", num3, base, ItoaForAnyBase(num3, str3, base));
	
	base = 16;
	printf("%d: to base %d. \n C =? "
	"%s\nSUCCESS\n", num1, base, ItoaForAnyBase(num1, str1, base));
	printf("%d: to base %d. \n 0 =? "
	"%s\nSUCCESS\n", num2, base, ItoaForAnyBase(num2, str2, base));
	printf("%d: to base %d. \n BC614E =? "
	"%s\nSUCCESS\n", num3, base, ItoaForAnyBase(num3, str3, base));
	
	base = 36;
	printf("%d: to base %d. \n C =? "
	"%s\nSUCCESS\n", num1, base, ItoaForAnyBase(num1, str1, base));
	printf("%d: to base %d. \n 0 =? "
	"%s\nSUCCESS\n", num2, base, ItoaForAnyBase(num2, str2, base));
	printf("%d: to base %d. \n 7CLZI =? "
	"%s\nSUCCESS\n", num3, base, ItoaForAnyBase(num3, str3, base));
	
	free(str1);
	free(str2);
	free(str3);	
}

static void AtoIForAnyBaseTest()
{
	int base = 10;
	const char *str1 = "0123456789";
	const char *str2 = "68ABCDEF";
	const char *str3 = "-156";
	
	printf("Tests for AtoIForAnyBase :\n\n");
	
	printf("String1 is: %s\n", str1);
	printf("In base %d is:\n 123456789 =? %d\n\nSUCCESS!\n\n", base, AtoIForAnyBase(str1, base));
	
	CompareAtois(str1, base);
	
	printf("%s in base %d is:\n -156\n", str3, base);
	CompareAtois(str3, base);
	
	base = 16;
	printf("String2 is: %s\n", str2);
	printf("In base %d is:\n 1756089839 =? %d\n\nSUCCESS!\n\n", base, AtoIForAnyBase(str2, base));
}

static void CompareAtois(const char *str, int base)
{
	if (0 != AtoIForAnyBase(str, base) - atoi(str))
	{
		printf("Failed, They are not the same: system - %d, My - %d\n\n", AtoIForAnyBase(str, base), atoi(str));
	}
	
	else
	{
		printf("SUCCESS, they are the same: %d, %d\n\n", AtoIForAnyBase(str, base), atoi(str));
    }
}

static void ThreeStrTest()
{
	char *str1 = "hello world";
	char *str2 = "hell wor";
	char *str3 = "hel";
	char *str4 = "HELlo wOrld";
	char *str5 = "hELLO";
	char *str6 = "hEl";
	
	printf ("Test Three Strings:\n");
	printf ("check1:\nstr1 = %s, str2 = %s, str3 = %s\n\n", str1, str2, str3);
	printf ("should print 'w' 'o' and 'r'\n");
	LettersOnlyInFirstTwo(str1, str2, str3);	
	
	printf ("check2:\nstr1 = %s, str2 = %s, str3 = %s\n\n", str4, str5, str6);
	printf ("should print 'L' and 'O' \n");
	LettersOnlyInFirstTwo(str4, str5, str6);	
}

void IsLittleEndianTest()
{
	printf("Test Little Endian:\n");
  	printf("Is little endian function result is:\n");
	IsLittleEndian();
	printf("Is little endian MACRO result is:\n");
	
	if(1 == IS_LITTLE_ENDIAN())
	{
		printf("Your system is Little endian.\n");
	}
	
	else
	{
		printf("Your system is Big endian.\n");
	}
	
	printf("\n");
}
