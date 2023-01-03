#include <stdio.h>


int main ()

{
	int i, length;
	char arr[]={0x22,0x48,0x65,'\n'};			/* same all same all */
	length = sizeof(arr)/sizeof(arr[0]);
	for (i=0; i<length; i++)
	{
		printf("%c", arr[i]);
	}
	return 1;
}
