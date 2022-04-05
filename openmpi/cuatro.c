#include <stdio.h>
#include <mpi.h>

#define N 10   // N par pero no multiplo de 4

int main(int argc, char** argv)
{
int  pid, npr;
int  i, j;
int  A[N][N], B[N][N];

MPI_Status info;
MPI_Datatype CUATRO;

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &pid);
MPI_Comm_size(MPI_COMM_WORLD, &npr);



if (pid == 0)
{
for(i=0; i<N; i++)
for(j=0; j<N; j++) A[i][j] = i*N + j;



printf( "\n <Cuatro> de A(+) en P0:% d %d %d %d\n ", A[N/4][N/4], A[N/4][3*N/4],
A[3*N/4][N/4], A[3*N/4][3*N/4]);
}
else if (pid == 1)
{
for(i=0; i<N; i++)
for(j=0; j<N; j++) B[i][j] = -(i*N + j);

printf( "\n <Cuatro> de B(-) en P1: %d %d %d %d\n ", B[N/4][N/4], B[N/4][3*N/4],
B[3*N/4][N/4], B[3*N/4][3*N/4]);
}
MPI_Finalize();
return 0;
} /* main */