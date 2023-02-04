/********************************
*	Developper: Yossi Matzliah	*
*	Date: 		04/02/2023		*
*	Reviewer:	Avri			*
********************************/

#include "/home/yossi/git/ds/include/dynamic_vector.h"

static void DynamicVectorTest();
static void PrintCurrentSize(vector_t *vector);
static void PrintCurrentCapacity(vector_t *vector);

int main()
{
	DynamicVectorTest();
	
	return 0;
}

static void PrintCurrentSize(vector_t *vector)
{
	printf ("size of vector is currently: %lu\n", VectorSize(vector));
}

static void PrintCurrentCapacity(vector_t *vector)
{
	printf ("capacity of vector1 is: %lu\n", VectorCapacity(vector));
}

static void DynamicVectorTest()
{
	size_t capacity1 = 4;
	int item1 = 1;
	int item2 = 2;
	int item3 = 3;
	int item4 = 4;
	int item5 = 5;
	int item6 = 6;
	int item7 = 7;
	char *get_access_check = '\0';
	size_t item_size1 = sizeof(item1);
	vector_t *vector1 = VectorCreate(capacity1, item_size1);
	
	PrintCurrentCapacity(vector1);
	PrintCurrentSize(vector1);
	printf ("Vector is empty? Yes. Should be 1 is: %d\nSUCCESS\n", VectorIsEmpty(vector1));
	VectorPushBack(vector1, &item1);
	PrintCurrentSize(vector1); 
	VectorPushBack(vector1, &item2);
	PrintCurrentSize(vector1); 
	VectorPushBack(vector1, &item3);
	PrintCurrentSize(vector1); 
	printf ("\nBefore adding last\n");
	PrintCurrentCapacity(vector1);
	VectorPushBack(vector1, &item4);
	PrintCurrentSize(vector1);
	printf ("\nAfter adding last(should be 2 times than before)\n"); 
	PrintCurrentCapacity(vector1);
	printf ("SUCCESS\n");
	VectorPopBack(vector1);
	printf ("After pop \n");
	PrintCurrentSize(vector1);
	printf ("\nBefore 1/4 of capacity\n"); 
	PrintCurrentCapacity(vector1);
	VectorPopBack(vector1);
	printf ("After pop \n");
	PrintCurrentSize(vector1);
	printf ("After 1/4 of capacity(should be 2 times less than before) \n");
	PrintCurrentCapacity(vector1);
	printf ("SUCCESS\n");
	VectorPopBack(vector1);
	PrintCurrentSize(vector1);
	printf ("Vector is empty? No. Should be 0 is: %d\nSUCCESS\n", VectorIsEmpty(vector1));
	PrintCurrentCapacity(vector1);
	VectorPopBack(vector1);
	PrintCurrentSize(vector1);
	printf ("Vector is empty? Yes. Should be 1 is: %d\nSUCCESS\n", VectorIsEmpty(vector1));
	PrintCurrentCapacity(vector1); 
	VectorPushBack(vector1, &item5);
	PrintCurrentSize(vector1);
	VectorPushBack(vector1, &item6);
	PrintCurrentSize(vector1);
	VectorPushBack(vector1, &item7);
	PrintCurrentSize(vector1);
	get_access_check = VectorGetAccessToElement(vector1, 1);
	printf("GetAccessCheck: Should be %d, is: %d\n", item6, *((int *)get_access_check));
	VectorPopBack(vector1);
	printf ("After pop \n");
	PrintCurrentSize(vector1);
	VectorReserve(vector1, 10);
	printf ("Should be 10 after reserve\n");
	PrintCurrentCapacity(vector1);
	printf ("SUCCESS\n");
	PrintCurrentSize(vector1);
	VectorShrinkToSize(vector1);
	printf ("After shrink need to be: size + 1\n");
	PrintCurrentCapacity(vector1); 
	VectorDestroy(vector1);
}
