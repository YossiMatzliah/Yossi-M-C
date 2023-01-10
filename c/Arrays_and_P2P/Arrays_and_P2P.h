

/* Using a pointer to an array
Where c is the number of columns in the array. */
void PointerToArr(int (*arr)[c]);

/* Using a pointer to a pointer */
void PointerToPointer(int **arr);

/* Using a reference to an array 
Where r is the number of rows and c is the number 
of columns in the array. */
void ReferenceToArr(int arr[r][c]);

/* I would choose the last one as it is straight forward 
that we are talking about two-dimentions array */

/* To access a specific location use arr [i][j]
starting from 1, for matrix 2x2 we have
arr [0][0] arr [0][1] arr [1][0] arr [1][1] */


/* print all data types sizes */
void PrintDataType();


/* given two arrays, gets the sum of each row */
void SumOfEachRow (int arr[r][c], int *result);


/* given an array and the size of it(array of soldires and the amount),
The first one kills the next alive and give the knife 
to the next alive and so on, untill only one man standing.
returns the index of the lucky guy */
size_t Josephus (int soldier[], size_t size);



