#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N  64
#define M  8*(8*7+1)   // numero total de caracteres del fichero dat2


int main(int argc, char **argv)
{
int  pid, npr;
int  i, k;
int  buf[N], modoacceso;
char aux[M];

MPI_File dat2;
MPI_Status info;

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &pid);
MPI_Comm_size(MPI_COMM_WORLD, &npr);

modoacceso = MPI_MODE_RDONLY;
MPI_File_open(MPI_COMM_WORLD, "dat2", modoacceso, MPI_INFO_NULL, &dat2);
MPI_File_seek(dat2, pid*M/npr, MPI_SEEK_SET);
MPI_File_read(dat2, aux, M/npr, MPI_CHAR, &info);
MPI_File_close(&dat2);

// convertimos de ascci a enteros
k = 0;
for(i=0; i<N/npr; i++)
{
sscanf(&aux[k], "%d", &buf[i]);
k = k+7;
if ((i%8==0) && (i>0)) k++;
}

// cada proceso imprime los dos primeros y los dos ultimos datos que ha leido
printf("\n P%d ha leido   %5d %5d ... %5d %5d \n", pid, buf[0], buf[1],
buf[N/npr-2], buf[N/npr-1]);

MPI_Finalize();
return 0;
}