/********************************
*	Developper: Yossi Matzliah	*
*	Date: 		21/01/2023		*
*	Reviewer:					*
********************************/


#include <stdio.h> /* printf, sprintf*/
#include <stdlib.h> /* malloc, realloc, free*/
#include <string.h> /* strlen, strcpy */
#define SIZE 5



typedef struct element_S el;
typedef enum {SUCCESS = 0, FAILURE = 1, ALLOC_ERR} status_t;
typedef void (*clean_up_t)(el *);
typedef status_t (*add_to_element_t)(el *, int);
typedef void (*print_element_t)(el *);


struct element_S
{
	void *value;
	print_element_t print_func_p;
	add_to_element_t add_func_p;
	clean_up_t clean_func_p;
};

static void CleanUp (el element_type[]);
static void NoCleanUp (el element_type[]);
static void PrintInt (el element_type[]);
static void PrintFloat (el element_type[]);
static void PrintStr (el element_type[]);
static status_t AddToInt (el element_type[], int num_to_add);
static status_t AddToFloat (el element_type[], int num_to_add);
static int CountDigits(int num);
static status_t AddToStr (el element_type[], int num_to_add);

status_t InitElements (el element_type[SIZE])
{
	char str2[] = "Damn";
	char *str1 = NULL;
	
	str1 = (char *)malloc(strlen(str2) + 1);
	
	if  (NULL == str1)
	{
		perror("Allocation Failed!\n");
		return ALLOC_ERR;
	}
	strcpy(str1, str2);

	*((int *)&element_type[0].value) = 7;
	*((float *)&(element_type[1].value)) = 5.5;
	element_type[2].value = str1;
	*((int *)&element_type[3].value) = 112; 
	*((float *)&element_type[4].value) = 8.2;
	
	
	return SUCCESS;
}


void MainProcessor ()
{
	int i = 0;
	int num_to_add = 0;
		
	el element_type[SIZE] = 
	{
		{NULL, 				&PrintInt,		&AddToInt, &NoCleanUp},
		{NULL, 				&PrintFloat,	&AddToFloat, &NoCleanUp},
		{NULL, 				&PrintStr, 	 	&AddToStr, &CleanUp},
		{NULL, 				&PrintInt,		&AddToInt, &NoCleanUp},
		{NULL, 				&PrintFloat,	&AddToFloat, &NoCleanUp}
	};
	
	InitElements (element_type);
	
	printf("Please enter int to add:\n");
	scanf("%d", &num_to_add);
	printf("The array value before adding:\n");
	
	for (i = 0; i < SIZE; ++i)
	{
		element_type[i].print_func_p(&element_type[i]);
		element_type[i].add_func_p(&element_type[i], num_to_add);
	}
	
	printf("\n");
	printf("The array value after adding:\n"); 
	
	for (i = 0; i < SIZE; ++i)
	{
		element_type[i].print_func_p(&element_type[i]);
		element_type[i].clean_func_p(&element_type[i]);
	}
	
	printf("\n");
}


static void CleanUp (el element_type[])
{
	free(element_type->value);
}

static void NoCleanUp (el element_type[])
{
	(void)element_type;
}

static void PrintInt (el element_type[])
{
	printf("%d,  ", *((int *)&(element_type->value)));
}

static void PrintFloat (el element_type[])
{
	printf("%.2f,  ", *((float *)&(element_type->value)));
}

static void PrintStr (el element_type[])
{
	printf("%s,  ", (char *) (element_type->value));
}

static status_t AddToInt (el element_type[], int num_to_add)
{
	(*((int *)&(element_type->value))) += num_to_add;
	return SUCCESS;
}

static status_t AddToFloat (el element_type[], int num_to_add)
{
	(*((float *)&(element_type->value))) += num_to_add;
	return SUCCESS;
}

static int CountDigits(int num)
{
	int digits_counter = 0;
	
	while (0 != num)
	{
		num /= 10;
		++digits_counter;
	}
	
	return digits_counter;
}

static status_t AddToStr (el element_type[], int num_to_add)
{
	int digits_in_add = CountDigits(num_to_add);
	int len = strlen(element_type->value);
	
	element_type->value = (void *) realloc(element_type->value, len + digits_in_add + 1);
	
	if  (NULL == element_type->value)
	{
		perror("Reallocation Failed!\n");
		return ALLOC_ERR;
	}
	
	sprintf((char *) (element_type->value), "%s%d", (char *) (element_type->value), num_to_add);
	
	return SUCCESS;
}



