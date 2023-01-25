/********************************
*	Developper: Yossi Matzliah	*
*	Date: 		24/01/2023		*
*	Reviewer:	Lilach			*
********************************/

#include <string.h> /* memcpy */
#include "serial.h"

void InitStudent (student_t *student);
static void PrintStudent (student_t *student);
static status_t CompareStructs(student_t *student, student_t *after_ser_student);

int main ()
{
	FILE *file = NULL;
	student_t student1 = {0};
	student_t after_ser_student1 = {0};
	
	InitStudent (&student1);
	PrintStudent (&student1);
	
	file = fopen("student_info.bin", "wb");
	if (NULL == file) 
	{
		perror("Error opening file!\n");
		return FOPEN_ERR;
	}

	if (0 != (SaveStudent(&student1, file)))
	{
		perror("Can't save file!\n");
		return SAVE_FILE_ERR;
	}
	
	if (0 != (fclose(file)))
	{
		perror("Can't close file!\n");
		return FCLOSE_ERR;
	}
	
	file = fopen("student_info.bin", "rb");
	if (NULL == file) 
	{
		perror("Error opening file!\n");
		return FOPEN_ERR;
	}

	if (0 != (LoadStudent(&after_ser_student1, file)))
	{
		perror("Can't load file!\n");
		return LOAD_FILE_ERR;
	}
	
	if (0 != (fclose(file)))
	{
		perror("Can't close file!\n");
		return FCLOSE_ERR;
	}
	
	printf("\nAfter serialization and deserialization:\n\n");
    PrintStudent(&after_ser_student1);
	
	if (0 == CompareStructs(&student1, &after_ser_student1))
	{
		printf("SUCCESS\n");
	}
	else
	{
		printf("Failed, not compared!\n");
	}
	
	return SUCCESS;
}

void InitStudent (student_t *student)
{
	char first_name[] = "Avi";
	char last_name[] = "Levi";
	
	memcpy(student->first_name, first_name, sizeof(first_name));
	memcpy(student->last_name, last_name, sizeof(last_name));
	student->grades.real_grades.physics = 70.5;
	student->grades.real_grades.math = 81.7;
	student->grades.humanities_grades.sociology = 66.5;
	student->grades.humanities_grades.literature = 88.5;
	student->grades.sport_grade = 95;
}

static void PrintStudent(student_t *student)
{
	printf("Student Name: %s %s\n", student->first_name, student->last_name);
	printf("Grades:\n");
	printf("Math: %.1f\n", student->grades.real_grades.math);
	printf("Physics: %.1f\n", student->grades.real_grades.physics);
    printf("sociology: %.1f\n", student->grades.humanities_grades.sociology);
	printf("literature: %.1f\n", student->grades.humanities_grades.literature);
	printf("Sports: %.1f\n", student->grades.sport_grade);
}

static status_t CompareStructs(student_t *student, student_t *after_ser_student)
{
	size_t diff_counter = 0;
	
	diff_counter += strcmp(after_ser_student->first_name, student->first_name);
	diff_counter += strcmp(after_ser_student->last_name, student->last_name);
	diff_counter += (after_ser_student->grades.real_grades.math != 
	student->grades.real_grades.math);
	diff_counter += (after_ser_student->grades.real_grades.physics != 
	student->grades.real_grades.physics);
	diff_counter += (after_ser_student->grades.humanities_grades.sociology !=
	 student->grades.humanities_grades.sociology);
	diff_counter += (after_ser_student->grades.humanities_grades.literature !=
	 student->grades.humanities_grades.literature);
	diff_counter += (after_ser_student->grades.sport_grade != 
	student->grades.sport_grade);
	
	if (0 != diff_counter)
	{
		return FAILURE;
	}
	
	else
	{
		return SUCCESS;
	}
}



