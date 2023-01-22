#include "g.h"

int main()
{
	printf ("first g_s value is: %d" ,g_s);
	foo();
	printf ("after func g_s value is: %d" ,g_s);
	return 0;
}
