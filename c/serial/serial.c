/********************************
*	Developper: Yossi Matzliah	*
*	Date: 		25/01/2023		*
*	Reviewer:	Lilach			*
********************************/

#include "serial.h"

FILE *SaveString(const char str[], FILE *file)
{
	size_t i = 0;
	
	while ('\0' != str[i]) 
	{
		fwrite(&str[i], sizeof(char), 1, file);
		++i;
	}
	fwrite(&str[i], sizeof(char), 1, file);
	
	return file;
}

FILE *SaveGrade(float *grade, FILE *file)
{
	fwrite(grade, sizeof(float), 1, file);
	
	return file;
}

FILE *LoadString(char str[], FILE *file)
{
	int i = 0;
	
	while (1) 
	{
		fread(&str[i], sizeof(char), 1, file);
		if ('\0' == str[i])
		{
			break;
		}
		++i;
	}
	
	return file;
}

FILE *LoadGrade(float *grade, FILE *file)
{
	fread(grade, sizeof(float), 1, file);
	
	return file;
}

status_t SaveStudent (student_t *student, FILE *file)
{
	if (NULL == file) 
	{
		perror("Cant access the file!\n");
		return SAVE_FILE_ERR;
	}
	
	file = SaveString(student->first_name, file);
	file = SaveString(student->last_name, file);
	file = SaveGrade(&student->grades.real_grades.physics, file);
	file = SaveGrade(&student->grades.real_grades.math, file);
	file = SaveGrade(&student->grades.humanities_grades.sociology, file);
	file = SaveGrade(&student->grades.humanities_grades.literature, file);
	file = SaveGrade(&student->grades.sport_grade, file);
	
	return SUCCESS;
	
}

status_t LoadStudent(student_t *student, FILE *file)
{
	if (NULL == file) 
	{
		perror("Cant access the file!\n");
		return LOAD_FILE_ERR;
	}
	
	file = LoadString(student->first_name, file);
	file = LoadString(student->last_name, file);
	file = LoadGrade(&student->grades.real_grades.physics, file);
	file = LoadGrade(&student->grades.real_grades.math, file);
	file = LoadGrade(&student->grades.humanities_grades.sociology, file);
	file = LoadGrade(&student->grades.humanities_grades.literature, file);
	file = LoadGrade(&student->grades.sport_grade, file);
	
	return SUCCESS;
}
