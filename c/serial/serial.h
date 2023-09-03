#ifndef __SERIAL_H__
#define __SERIAL_H__
#include <stdio.h> /* printf, FILE */

typedef enum {SUCCESS = 0, FAILURE , FOPEN_ERR, FCLOSE_ERR, SAVE_FILE_ERR, LOAD_FILE_ERR} status_t;
 
typedef struct
{
    float physics;
    float math;
}real_grades_t;

typedef struct
{
    float sociology;
    float literature;
}humanities_grades_t;

typedef struct
{
    real_grades_t real_grades;
    humanities_grades_t humanities_grades;
    float sport_grade;
}grades_t;

typedef struct
{
    char first_name[20];
    char last_name[20];
    grades_t grades;
}student_t;

status_t SaveStudent (student_t *student, FILE *file);
status_t LoadStudent (student_t *student, FILE *file);

#endif
