#include <stdio.h>
#include <stdlib.h>

#define N 180     // multiplo de 12 (2x2, 3x3, 4x4)

int main(int argc, char** argv)
{
int   i, j;
int   A[N][N];
int   sum=0;


/* inicilaizacion de la matriz */
for(i=0; i<N; i++)
for(j=0; j<N; j++) A[i][j] = rand() % 20;

/* operación a paralelizar, distribuyendo la matriz por bloques */
for(i=0; i<N; i++)
for(j=0; j<N; j++) sum = (sum + A[i][j]) % 10;

printf("\n   suma de A   % 10 = %d\n\n", sum);
return 0;
} /* main */

