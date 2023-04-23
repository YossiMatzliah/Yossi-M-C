/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	????				*
*	Date      : ?/04/2023			*
************************************/

#include <stdio.h>	/* perror, printf */
#include <assert.h>	/* assert */
#include <stdlib.h>	/* abs */

#include "knight.h"
#include "dynamic_vector.h"

typedef enum status 
{
    SUCCESS,
    FAILURE
} status_t;

typedef enum boolean 
{
    FALSE,
    TRUE
} boolean_t;

typedef struct point
{
    int row;
    int col;
} point_t;

/******************************** Static Functions *********************************/

static status_t RecKnight(int row, int col, int matrix[ROWS][COLUMNS], vector_t *moves_lut[ROWS][COLUMNS], int moves_count);
static boolean_t IsValidMove(int row, int col, int matrix[ROWS][COLUMNS]);
static void InitMatrixWithZero(int matrix[ROWS][COLUMNS]);
static void InitMovesLUT(int matrix[ROWS][COLUMNS], vector_t *moves_lut[ROWS][COLUMNS], point_t *point);
static void DestroyVectorLUT(vector_t *moves_lut[ROWS][COLUMNS]);
static void InitValidMoves(int row, int col, int matrix[ROWS][COLUMNS], vector_t *moves_lut[ROWS][COLUMNS], point_t *point);

/********************************** API Functions **********************************/

int KnightTour(int matrix[ROWS][COLUMNS], int row, int col)
{
    status_t status = FAILURE;
    vector_t *moves_lut[ROWS][COLUMNS] = {{0}};
    point_t point = {0, 0};
    int moves_count = 1;

    InitMatrixWithZero(matrix);
    InitMovesLUT(matrix, moves_lut, &point);

    matrix[row][col] = moves_count;
    status = RecKnight(row, col, matrix, moves_lut, moves_count + 1);
    PrintBoard(matrix);

    DestroyVectorLUT(moves_lut);

    return status;
}

void PrintBoard(int solution[ROWS][COLUMNS])
{
    int i = 0;
    int j = 0;
    
    for (i = 0; i < ROWS; ++i)
    {
        for (j = 0; j < COLUMNS; ++j)
        {
            printf("%4d",  solution[i][j]);
        }
        
        printf("\n");
    }
    
    printf("\n");
}

/********************************** Static Functions **********************************/

static status_t RecKnight(int row, int col, int matrix[ROWS][COLUMNS], vector_t *moves_lut[ROWS][COLUMNS], int moves_count)
{
    size_t i = 0;
    int next_row = 0;
    int next_col = 0;
    
    if (moves_count == ROWS * COLUMNS + 1)
    {
        return SUCCESS;
    }
    
    for (i = 0; i < VectorSize(moves_lut[row][col]); ++i)
    {
        next_row = (((point_t *)VectorGetAccessToElement(moves_lut[row][col], i))->row);
        next_col = (((point_t *)VectorGetAccessToElement(moves_lut[row][col], i))->col);
        
        if (IsValidMove(next_row, next_col, matrix))
        {
            matrix[next_row][next_col] = moves_count;
            
            if (SUCCESS == RecKnight(next_row, next_col, matrix, moves_lut, moves_count + 1))
            {
                return SUCCESS;
            }
            
            else
            {
                matrix[next_row][next_col] = 0;
            }
        }
    }
    
    return FAILURE;
}

static boolean_t IsValidMove(int row, int col, int matrix[ROWS][COLUMNS]) 
{  
    if (0 <= row && row < ROWS && 0 <= col && col < COLUMNS && 0 == matrix[row][col])
    {
        return TRUE;
    }
  
    return FALSE;
}

static void InitValidMoves(int row, int col, int matrix[ROWS][COLUMNS], vector_t *moves_lut[ROWS][COLUMNS], point_t *point)
{
    int i = 0;
    int j = 0;
    
    for (i = 2; i > -3; --i)
    {
        for (j = 2; j > -3; --j)
        {
            if (0 != i && 0 != j && abs(i) != abs(j) && IsValidMove(row + i, col + j, matrix))
            {
                point->row = row + i;
                point->col = col + j;

                if (SUCCESS != VectorPushBack(moves_lut[row][col], point))
                {
                    perror("Allocation Error");
                    return;
                }
            }
        }
    }
}

static void InitMatrixWithZero(int matrix[ROWS][COLUMNS])
{
    int i = 0;
    int j = 0;
    
    for (i = 0; i < ROWS; ++i)
    {
        for (j = 0; j < COLUMNS; ++j)
        {
            matrix[i][j] = 0;
        }
    }
}

static void InitMovesLUT(int matrix[ROWS][COLUMNS], vector_t *moves_lut[ROWS][COLUMNS], point_t *point)
{
    int i = 0;
    int j = 0;
    
    for (i = 0; i < ROWS; ++i)
    {
        for (j = 0; j < COLUMNS; ++j)
        {
            moves_lut[i][j] = VectorCreate(ROWS, sizeof(point_t));
            if (NULL == moves_lut[i][j])
            {
                perror("Allocation Error");
                return;
            }
            
            InitValidMoves(i, j, matrix, moves_lut, point);
        }
    }
}

static void DestroyVectorLUT(vector_t *moves_lut[ROWS][COLUMNS])
{
    int i = 0;
    int j = 0;
    
    for (i = 0; i < ROWS; ++i)
    {
        for (j = 0; j < COLUMNS; ++j)
        {
            VectorDestroy(moves_lut[i][j]);
        }
    }
}
