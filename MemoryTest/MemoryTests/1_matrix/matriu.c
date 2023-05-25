#include <stdio.h>
#include "measure.h"
#include <stdlib.h>


#define N 2048*2
#define ROWS N
#define COLS N

/* Data matrix */
char M[ROWS][COLS];

/* Execute the call f() and measure its execution time in useconds */
double measure( void (*f)(void) )
{
	return measure_full((int(*)(int,int))f, 0xDEAD, 0xDEAD, 3, 0.01, 10); // 1% error
}

/* init_data - initializes the array */
void init_data()
{
	int i, j;
	for(i=0; i<ROWS; i++) {
		for(j=0; j<COLS; j++) {
			M[i][j] = i+j*10;
		}
	}
}

/* Traverse matrix 'M' by rows */
void matrix_rows()
{
	int i, j;
	for(i=0; i<ROWS; i++) {
		for(j=0; j<COLS; j++) {
			M[i][j] = i+j;
		}
	}
}

/* Traverse matrix 'M' by columns */
void matrix_cols()
{
	int i, j;
	for(j=0; j<COLS; j++) {
		for(i=0; i<ROWS; i++) {
			M[i][j] = i+j;
		}
	}
}

int main()
{
	printf(" Matrix of %d x %d elements \n", ROWS, COLS);
	printf("    Size = %8ld bytes / %8ldKBs / %8ldMBs\n", sizeof(M), sizeof(M)/1024, sizeof(M)/(1024*1024));
	printf(" rowsize = %8ld bytes / %8ldKBs / %8ldMBs\n", COLS*sizeof(M[0][0]), COLS*sizeof(M[0][0])/1024, COLS*sizeof(M[0][0])/(1024*1024));

	init_data();

	//Initial traversal to warmup the memory...
	printf(" * Time to initialize : %f useconds\n", measure(matrix_rows));

	printf(" Traverse using rows...\n");
	printf(" * Time (1)           : %f useconds\n", measure(matrix_rows));
	printf(" * Time (2)           : %f useconds\n", measure(matrix_rows));
	printf(" * Time (3)           : %f useconds\n", measure(matrix_rows));
	printf(" Traverse using columns...\n");
	printf(" * Time (1)           : %f useconds\n", measure(matrix_cols));
	printf(" * Time (2)           : %f useconds\n", measure(matrix_cols));
	printf(" * Time (3)           : %f useconds\n", measure(matrix_cols));

#ifdef _WIN32
	printf("Press return to continue\n");
	char c;
	read(0, &c, 1);
#endif
}
