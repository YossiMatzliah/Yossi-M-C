#include <stdio.h>	/*for printf*/
#include <assert.h> /*for assert*/
#include <stdlib.h> /*for exit*/
#include "file.c"



struct print_me
{
	int a;
	FuncPtr Print;
};



void PrintMeTest();
void ArrStructFilesTest();

int main ()
{
	/* 
	PrintMeTest();
	*/
	
	ArrStructFilesTest();
	return 0;
}


void PrintMeTest()
{
	struct print_me p_arr[10];
	size_t i = 0;
	
	for (i = 0; i < 10; i++)
	{
		p_arr[i].a = i;
		p_arr[i].Print = &Print;
		p_arr[i].Print(p_arr[i].a);
	}
}


void ArrStructFilesTest()
{
	const char *file = "file.txt";
	/*FILE *fp = fopen(file, "w");
	
	fclose(fp);*/
	Master(file);
}


