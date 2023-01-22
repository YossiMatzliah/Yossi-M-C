/* MACROS */
#define MAX2(a, b)  (a > b) ? a : b
#define MAX3(a, b, c)  MAX2(a,b) > c ? MAX2(a,b) : c 
#define SIZEOF(object) (char *)(&object+1) - (char *)(&object)
#define DECLARE_TYPE(type) __typeof__(type) newvar
/* Till here */
#include "elements.h"


int main()
{
	/* MACROS */
	int num1 = 3;
	int num2 = 7;
	int num3 = 12;
	
	DECLARE_TYPE(short);
    printf("The type size is: %ld\n", SIZEOF(newvar));
    
	printf("MAX2(%d, %d) = %d\n", num1, num2, MAX2(num1, num2));
	printf("MAX3(%d, %d, %d) = %d\n", num1, num2, num3, MAX3(num1, num2, num3));
	printf("num var size: %ld\n", SIZEOF(num1));
	/* Till here */	
	
	MainProcessor();

	return 0;
}
