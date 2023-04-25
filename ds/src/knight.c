/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Tomer				*
*	Date      : 25/04/2023			*
************************************/

#include <stdio.h>	/* perror, printf */
#include <assert.h>	/* assert */
#include <stdlib.h>	/* abs */
#include <unistd.h> /* alarm */

#include "knight.h"
#include "dynamic_vector.h"
#include "heap.h"

#define WHITE_ON_BLACK  	"\033[1m\033[40m\x1B[37m"
#define BLACK_ON_WHITE   	"\033[1m\033[30m\x1B[47m"
#define RESET 	            "\033[0m"

#define ALARM_TIME (5 * 60)

typedef enum color 
{
    BLACK = 0,
    WHITE = 1
} color_t;

typedef enum status 
{
    SUCCESS = 0,
    FAILURE = 1
} status_t;

typedef enum boolean 
{
    FALSE = 0,
    TRUE = 1
} boolean_t;

typedef struct point
{
    int row;
    int col;
    int moves_num;
} point_t;

/******************************** Static Functions *********************************/

static void InitMatrixWithZero(int matrix[ROWS][COLUMNS]);
static void InitMovesLUT(int matrix[ROWS][COLUMNS], vector_t *moves_lut[ROWS][COLUMNS], point_t *point);
static void InitHeapLUT(heap_t *heap_lut[ROWS][COLUMNS]);
static status_t RecKnight(int row, int col, int matrix[ROWS][COLUMNS], vector_t *moves_lut[ROWS][COLUMNS], heap_t *heap_lut[ROWS][COLUMNS]);
static boolean_t IsValidMove(int row, int col, int matrix[ROWS][COLUMNS]);
static void InitValidMoves(int row, int col, int matrix[ROWS][COLUMNS], vector_t *moves_lut[ROWS][COLUMNS], point_t *point);
static int CountValidMoves(int row, int col, int matrix[ROWS][COLUMNS]);
static void DestroyVectorLUT(vector_t *moves_lut[ROWS][COLUMNS]);
static void DestroyHeapLUT(heap_t *heap_lut[ROWS][COLUMNS]);
int PriorityFunc(const void *lhs, const void *rhs);

/********************************** API Functions **********************************/

int KnightTour(int matrix[ROWS][COLUMNS], int row, int col)
{
    status_t status = FAILURE;
    vector_t *moves_lut[ROWS][COLUMNS] = {{0}};
    heap_t *heap_lut[ROWS][COLUMNS] = {{0}};
    point_t point = {0, 0, 0};

    InitMatrixWithZero(matrix);
    InitMovesLUT(matrix, moves_lut, &point);
    InitHeapLUT(heap_lut);

    alarm(ALARM_TIME);

    matrix[row][col] = 1;
    status = RecKnight(row, col, matrix, moves_lut, heap_lut);

    DestroyVectorLUT(moves_lut);
    DestroyHeapLUT(heap_lut);

    return status;
}

void PrintBoard(int solution[ROWS][COLUMNS])
{
    int i = 0;
    int j = 0;
    color_t board_color = BLACK;
    
    for (i = 0; i < ROWS; ++i)
    {
        for (j = 0; j < COLUMNS; ++j)
        {
            if (BLACK == board_color)
            {
                printf("%s%-4d%s", WHITE_ON_BLACK, solution[i][j], RESET);
                board_color = !board_color;
            }
            
            else
            {
                printf("%s%-4d%s", BLACK_ON_WHITE, solution[i][j], RESET);
                board_color = !board_color;
            }
        }
        
        if (0 == COLUMNS % 2)
        {
            board_color = !board_color;
        }

        printf("\n");
    }

    printf("\n");
}

/********************************** Static Functions **********************************/

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
                point->moves_num = CountValidMoves(point->row, point->col, matrix);

                if (SUCCESS != VectorPushBack(moves_lut[row][col], point))
                {
                    perror("Allocation Error");
                    return;
                }
            }
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

static void InitHeapLUT(heap_t *heap_lut[ROWS][COLUMNS])
{
    int i = 0;
    int j = 0;
    
    for (i = 0; i < ROWS; ++i)
    {
        for (j = 0; j < COLUMNS; ++j)
        {
            heap_lut[i][j] = HeapCreate(PriorityFunc);
            if (NULL == heap_lut[i][j])
            {
                perror("Allocation Error");
                return;
            }
        }
    }
}

static status_t RecKnight(int row, int col, int matrix[ROWS][COLUMNS], vector_t *moves_lut[ROWS][COLUMNS], heap_t *heap_lut[ROWS][COLUMNS])
{
    size_t i = 0;
    int next_row = 0;
    int next_col = 0;
    point_t *temp_point = {0};

    if (matrix[row][col] == ROWS * COLUMNS)
    {
        return SUCCESS;
    }

    for (i = 0; i < VectorSize(moves_lut[row][col]); ++i)
    {
        temp_point = (point_t *)VectorGetAccessToElement(moves_lut[row][col], i);
        temp_point->moves_num = CountValidMoves(temp_point->row, temp_point->col, matrix);

        if (SUCCESS != HeapPush(heap_lut[row][col], temp_point))
        {
            return FAILURE;
        }
    }

    while (TRUE != HeapIsEmpty(heap_lut[row][col]))
    {
        next_row = (((point_t *)HeapPeek(heap_lut[row][col]))->row);
        next_col = (((point_t *)HeapPeek(heap_lut[row][col]))->col);
        HeapPop(heap_lut[row][col]);

        if (IsValidMove(next_row, next_col, matrix))
        {
            matrix[next_row][next_col] = matrix[row][col] + 1;
            
            if (SUCCESS == RecKnight(next_row, next_col, matrix, moves_lut, heap_lut))
            {
                return SUCCESS;
            }
            
            matrix[next_row][next_col] = 0;
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

static int CountValidMoves(int row, int col, int matrix[ROWS][COLUMNS])
{
    int i = 0;
    int j = 0;
    int counter = 0;
    
    for (i = -2; i < 3; ++i)
    {
        for (j = -2; j < 3; ++j)
        {
            if (0 != i && 0 != j && abs(i) != abs(j) && IsValidMove(row + i, col + j, matrix))
            {
                ++counter;
            }
        }
    }
    
    return counter;
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

static void DestroyHeapLUT(heap_t *heap_lut[ROWS][COLUMNS])
{
    int i = 0;
    int j = 0;
    
    for (i = 0; i < ROWS; ++i)
    {
        for (j = 0; j < COLUMNS; ++j)
        {
            HeapDestroy(heap_lut[i][j]);
        }
    }
}

int PriorityFunc(const void *lhs, const void *rhs)
{
    return (((point_t *)rhs)->moves_num - ((point_t *)lhs)->moves_num);
}


