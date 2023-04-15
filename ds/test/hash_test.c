/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Daniel				*
*	Date      : 15/04/2023			*
************************************/

#include <stdio.h>	/* printf */
#include <string.h>	/* strcmp, strcspn */

#include "hash.h"

#define U_LINE 	"\033[1m\033[4m"
#define RED   	"\033[1m\033[41m\x1B[30m"
#define GRN   	"\033[1m\033[42m\x1B[30m"
#define RESET 	"\033[0m"

#define TRUE 	(1)
#define FALSE 	(0)
#define SUCCESS (0)
#define FAILURE (1)

#define PRINT_TEST(x) ((TRUE == (x)) ? printf(GRN"SUCCESS!"RESET"\n\n") : printf(RED"FAILURE!, line %d"RESET"\n\n", __LINE__))

#define NEW_LINE printf("\n")

#define CAPACITY (50)
#define DICT_CAPACITY (104334)
#define MAX_WORD_LENGTH (40)

typedef struct student
{
	char *first_name;
	char *last_name;
	size_t grade;
} student_t;


/*****************************************************************/

static void TestHashCreateDestroy();
static void TestHashTableInsert();
static void TestHashTableRemove();
static void TestHashTableFind();
static void TestHashTableForEach();
static void TestHashLoad();
static void TestHashSTDev();
static void TestDictionary();

size_t HashFunction(const void *value);
int IsMatch(const void *lhd, const void *rhd);
int AddParam(void *data, void *parameter);
size_t DictionaryHashFunction(const void *value);
int DictionaryIsMatch(const void *lhd, const void *rhd);

/*****************************************************************/

int main()
{
	TestHashCreateDestroy();
	TestHashTableInsert();
	TestHashTableRemove();
	TestHashTableFind();
	TestHashTableForEach();
	TestHashLoad();
	TestHashSTDev();
	TestDictionary();

	return 0;
}


static void TestHashCreateDestroy()
{
	hash_table_t *test_table = NULL;

	test_table = HashTableCreate(CAPACITY, HashFunction, IsMatch);

	printf(U_LINE"Test Hash Create:\n\n"RESET);

	PRINT_TEST(NULL != test_table);

	PRINT_TEST(TRUE == HashTableIsEmpty(test_table));

	HashTableDestroy(test_table);
}

static void TestHashTableInsert()
{
	hash_table_t *test_table = NULL;
	int status = 0;
	size_t size = 0;

	student_t student_1 = {"Bob", "Blabla", 90};
	student_t student_2 = {"Dani", "Dan", 95};
	student_t student_3 = {"Mister", "Smartone", 100};

	printf(U_LINE"\nTest Hash Insert:\n\n"RESET);

	test_table = HashTableCreate(CAPACITY, HashFunction, IsMatch);
	
	status = HashTableInsert(test_table, &student_1);
	++size;
	
	PRINT_TEST(SUCCESS == status);
	
	PRINT_TEST(size == HashTableSize(test_table));

	PRINT_TEST(FALSE == HashTableIsEmpty(test_table));

	status = HashTableInsert(test_table, &student_2);
	++size;
	PRINT_TEST(size == HashTableSize(test_table));

	status = HashTableInsert(test_table, &student_3);
	++size;
	
	status = HashTableInsert(test_table, &student_3);
	++size;

	PRINT_TEST(size == HashTableSize(test_table));

	HashTableDestroy(test_table);
}

static void TestHashTableRemove()
{
	hash_table_t *test_table = NULL;
	size_t size = 0;

	student_t student_1 = {"Bob", "Blabla", 90};
	student_t student_2 = {"Dani", "Dan", 95};
	student_t student_3 = {"Mister", "Smartone", 100};

	printf(U_LINE"\nTest Hash Remove:\n\n"RESET);

	test_table = HashTableCreate(CAPACITY, HashFunction, IsMatch);
	
	HashTableInsert(test_table, &student_1);
	++size;
	HashTableInsert(test_table, &student_2);
	++size;
	HashTableInsert(test_table, &student_3);
	++size;
	HashTableInsert(test_table, &student_3);
	++size;

	HashTableRemove(test_table, &student_3);
	--size;
	PRINT_TEST(size == HashTableSize(test_table));

	HashTableRemove(test_table, &student_3);
	--size;
	PRINT_TEST(size == HashTableSize(test_table));

	HashTableRemove(test_table, &student_1);
	--size;
	PRINT_TEST(size == HashTableSize(test_table));
	HashTableRemove(test_table, &student_2);
	--size;
	PRINT_TEST(size == HashTableSize(test_table));

	PRINT_TEST(TRUE == HashTableIsEmpty(test_table));

	HashTableDestroy(test_table);
}

void TestHashTableFind()
{
	hash_table_t *test_table = NULL;
	void *found_data_ptr = NULL;

	student_t student_1 = {"Bob", "Blabla", 90};
	student_t student_2 = {"Dani", "Dan", 95};
	student_t student_3 = {"Mister", "Smartone", 100};
	student_t student_4 = {"Jacoben", "Brown", 95};
	student_t student_not_found = {"Aladin", "One", 85};

	printf(U_LINE"\nTest Hash Find:\n\n"RESET);

	test_table = HashTableCreate(CAPACITY, HashFunction, IsMatch);
	
	HashTableInsert(test_table, &student_1);
	HashTableInsert(test_table, &student_2);
	HashTableInsert(test_table, &student_3);
	HashTableInsert(test_table, &student_4);

	found_data_ptr = HashTableFind(test_table, (void *)&student_4);
	
	PRINT_TEST(NULL != found_data_ptr);

	PRINT_TEST(student_4.first_name == ((student_t *)found_data_ptr)->first_name);

	found_data_ptr = HashTableFind(test_table, (void *)&student_not_found);
    PRINT_TEST(NULL == found_data_ptr);

	HashTableDestroy(test_table);
}

void TestHashTableForEach()
{
	hash_table_t *test_table = NULL;
	size_t param_to_add = 1;
	int func_status = FAILURE;
	size_t grade_to_check = 0;

	student_t student_1 = {"Bob", "Blabla", 90};
	student_t student_2 = {"Dani", "Dan", 95};
	student_t student_3 = {"Mister", "Smartone", 99};
	student_t student_4 = {"Jacoben", "Brown", 95};

	printf(U_LINE"\nTest Hash For Each:\n\n"RESET);

	test_table = HashTableCreate(CAPACITY, HashFunction, IsMatch);
	
	HashTableInsert(test_table, &student_1);
	HashTableInsert(test_table, &student_2);
	HashTableInsert(test_table, &student_3);
	HashTableInsert(test_table, &student_4);

	grade_to_check = student_3.grade;

	func_status = HashTableForEach(test_table, AddParam, &param_to_add);
	
	PRINT_TEST(SUCCESS == func_status);
	
	PRINT_TEST(grade_to_check + param_to_add == student_3.grade);
	
	HashTableDestroy(test_table);
}

static void TestHashLoad()
{
    hash_table_t *test_table = NULL;
    double hash_load_res = 0;
    double load_should_be = 4 / (double)CAPACITY;

    student_t student1 = {"Bob", "Blabla", 90};
    student_t student2 = {"Dani", "Dan", 95};
    student_t student3 = {"Mister", "Smartone", 100};
    student_t student4 = {"Jacoben", "Brown", 95};

    printf(U_LINE"\nTest Hash Load:\n\n"RESET);

    test_table = HashTableCreate(CAPACITY, HashFunction, IsMatch);
    
    HashTableInsert(test_table, &student1);
    HashTableInsert(test_table, &student2);
    HashTableInsert(test_table, &student3);
    HashTableInsert(test_table, &student4);

    hash_load_res = HashLoad(test_table);
    
    printf("hash load is: %.2f\n", hash_load_res);
    PRINT_TEST(hash_load_res == load_should_be);

    HashTableDestroy(test_table);
}

static void TestHashSTDev()
{
    hash_table_t *test_table = NULL;
    double standard_deviation = 0;

    student_t student1 = {"Bob", "Blabla", 90};
    student_t student2 = {"Dani", "Dan", 95};
    student_t student3 = {"Mister", "Smartone", 100};
    student_t student4 = {"Jacoben", "Brown", 95};
    student_t student5 = {"Aladin", "Din", 85};

    printf(U_LINE"\nTest Hash SD:\n\n"RESET);

    test_table = HashTableCreate(CAPACITY, HashFunction, IsMatch);
    
    HashTableInsert(test_table, &student1);
    HashTableInsert(test_table, &student2);
    HashTableInsert(test_table, &student3);
    HashTableInsert(test_table, &student4);
    HashTableInsert(test_table, &student5);
    
    standard_deviation = HashSTDev(test_table);

    printf("Hash table SD is: %f\n\n", standard_deviation);

    HashTableDestroy(test_table);
}

static void TestDictionary()
{
    size_t i = 0;
    size_t word_length = 0;
    int status = 0;
    FILE *fp = NULL;
    char *path_to_file = "/usr/share/dict/american-english";
    char dictionary[DICT_CAPACITY][MAX_WORD_LENGTH] = {{0}};
    char *to_find_1 = "sabbatical's";
    char *to_find_2 = "relinquishment";
    char *not_found = "ASCI";
    void *found_data_ptr = NULL;
    hash_table_t *test_table = NULL;
    
	printf(U_LINE"\nTest Hash Dictionary:\n\n"RESET);
    
    test_table = HashTableCreate(DICT_CAPACITY, DictionaryHashFunction, DictionaryIsMatch);
    
    fp = fopen(path_to_file, "r");
    if (NULL == fp)
    {
        printf("Error opening file");
        return;
    }
    
    for (i = 0; i < DICT_CAPACITY && 0 == status; ++i)
    {
        if (NULL == fgets(dictionary[i], MAX_WORD_LENGTH, fp))
        {
            printf("Error");
            return;
        }
        
        word_length = strlen(dictionary[i]);
        dictionary[i][word_length - 1] = '\0';
        status = HashTableInsert(test_table, dictionary + i);
    }
    
    fclose(fp);
    
    found_data_ptr = HashTableFind(test_table, (void *)to_find_1);
    PRINT_TEST(0 == strcmp(to_find_1, (char *)found_data_ptr));

    found_data_ptr = HashTableFind(test_table, (void *)to_find_2);
    PRINT_TEST(0 == strcmp(to_find_2, (char *)found_data_ptr));

    found_data_ptr = HashTableFind(test_table, (void *)not_found);
    PRINT_TEST(NULL == found_data_ptr);
    
    printf("hash load is: %.3f\n", HashLoad(test_table));
    printf("Hash table SD is: %f\n\n", HashSTDev(test_table));

    HashTableDestroy(test_table);
}

/*******************************************/

size_t HashFunction(const void *value)
{
	size_t x = ((student_t *)value)->grade;

	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;

	return x;
}

int IsMatch(const void *lhd, const void *rhd)
{
	return ((student_t *)lhd)->grade == ((student_t *)rhd)->grade;
}

int AddParam(void *data, void *parameter)
{
    ((student_t *)data)->grade += *(size_t *)parameter;
	
	return SUCCESS;
}

size_t DictionaryHashFunction(const void *value)
{
    size_t hash_val = 0;
    char *word = (char *)value;
    
    for (hash_val = 0; *word != '\0'; ++word)
    {
        hash_val = *word + 31 * hash_val;
    }
    
    return hash_val % DICT_CAPACITY;
}

int DictionaryIsMatch(const void *lhd, const void *rhd)
{
    return !(strcmp((char *)lhd, (char *)rhd));
}