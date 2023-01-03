#include <stdio.h>

int main() 
{

	unsigned int number, reversed = 0;

 	printf("Enter an integer: ");
	scanf("%u", &number);

	do {
    	reversed *= 10;
    	reversed += number % 10;
    	number /= 10; 
	} while (number > 0);

  printf("Reversed number = %u \n", reversed);

  return 0;
}




