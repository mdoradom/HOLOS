#include <stdio.h>
#include "measure.h"
#ifndef N
#define N 256  /* Dimensión por defecto */
#endif

float A[N][N], B[N][N], C[N][N]; 

/* Execute the call f() and measure its execution time in useconds */
double measure( void (*f)(void) )
{
	return measure_full((int(*)(int,int))f, 0xDEAD, 0xDEAD, 1, 0.01, 1); // Single execution
}


void init_data();
void code();
int main() {
  double t;
  int i, j;


  // Inicializacion de las matrices A, B y C
  init_data();

  // CODIGO A EVALUAR: forma ijk del producto de dos matrices de tamaño NxN
  t = measure(code);


  if (N > 6) {
    printf("FORMA ijk (%d), Milisegundos = %f \n\n", N, t/1000.0);
  }
  if (N <= 6) {
    /* 
     * Para Ns peque¤as se saca el resultado para comprobar que las tres
     * formas dan el mismo resultado
     */
    printf("\nFORMA ijk \n\n");
    for (i=0; i<N; i++) {
      for (j=0; j<N; j++)
        printf("%10f ", C[i][j]);
      printf ("\n");
    }
  }

#ifdef _WIN32
  printf("Press return to continue\n");
  char c;
  read(0, &c, 1);
#endif
  return 0;
}

void init_data()
{
  float x;
  int i, j;
  x = 0.001;
  for (i=0; i<N; i++)
    for (j=0; j<N; j++) {
      A[i][j] = 3.4 + x;
      B[i][j] = 0.1 + x;
      C[i][j] = 0.0;
      x = x + 0.02;
    }
}

void code()
{
  int i, j, k;
  float tmp;
  for (i=0; i<N; i++)
    for (j=0; j<N; j++) {
      tmp = C[i][j];
      for (k=0; k<N; k++)
        tmp = tmp + A[i][k] * B[k][j];
      C[i][j] = tmp;
    }
}
