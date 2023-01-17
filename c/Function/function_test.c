#include <stdio.h>
#include <stdlib.h>
#include "function.c"


void KeyboardPressedSCTest();
void KeyboardPressedIETest();
void KeyboardPressedLUTTest();


int main ()
{
	KeyboardPressedSCTest();
	KeyboardPressedIETest();
	KeyboardPressedLUTTest();
	
	return 0;
}



void KeyboardPressedSCTest()
{	
	KeyboardPressedSC();
}

void KeyboardPressedIETest()
{	
	KeyboardPressedIE();
}

void KeyboardPressedLUTTest()
{	
	KeyboardPressedLUT();
}


