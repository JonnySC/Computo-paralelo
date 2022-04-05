#include <stdio.h>
#include "mpi.h"

#define N 100000
int main(int argc, char** argv)
{

int pid, kont;  // Identificador del proceso
int a[N], b[N], c[N], d[N];
MPI_Status status;

// Identificador del proceso
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &pid);

for (kont=100; kont<=N; kont=kont+100)
{
if (pid == 0)
{

MPI_Send(&a[0], kont, MPI_INT, 1, 0, MPI_COMM_WORLD);
MPI_Recv(&b[0], kont, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
printf("emisor %d \n", kont);
}
else
{
MPI_Send(&c[0], kont, MPI_INT, 0, 0, MPI_COMM_WORLD);
MPI_Recv(&d[0], kont, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
printf("             receptor %d \n", kont);
}
}
MPI_Finalize();
return 0;
} /* main */