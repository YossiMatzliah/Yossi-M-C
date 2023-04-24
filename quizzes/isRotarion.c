#include <stdio.h>
#include <string.h>

int IsRotation(char*, char*);

int main()
{
	char str1[] = "OLEHL";
	char str2[] = "HELLO";
	/*char str3[] = "HELL";
	char str4[] = "123456";
	char str5[] = "123754";*/

	printf("%d\n", IsRotation(str1, str2));

	return 0;
}

int IsRotation(char *str1, char *str2)
{
	int index = -1;
	int len1 = 0;
	int len2 = 0;
	int i = 0;
	
	len1 = strlen(str1);
	len2 = strlen(str2);
	
	if (len1 != len2)
	{
		return 1;
	}
	
	for (i = 0; i < len1; i++)
	{
		if (str1[i] == str2[0])
		{
			index = i;
			break;
		}
	}
	
	if (index == -1)
	{
		return 1;
	}
	
	for (i = 0; i < len1; i++)
	{
		if (str1[(index + i) % len1] != str2[i])
		{
			return 1;
		}
	}
	return 0;
}

	

	
