#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

#define tambuf 100
#define N 64

int main(int argc, char **argv)
{
int  pid, npr;
int  i;
int  buf[tambuf], buf2[tambuf], modoacceso;

char aux[20];
char linea[2000];

MPI_File dat2;
MPI_Status info;

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &pid);
MPI_Comm_size(MPI_COMM_WORLD, &npr);

if (pid == 0) for(i=0; i<N; i++) buf[i] = i*i;
// Los 64 elementos de buf se convierten a ascci, 8 lineas de 8 elementos

linea[0] = '\0';
for(i=0; i<N; i++)
{

if((i%8==0) && (i>0)) strcat(linea,"\n");
sprintf (aux, " %6d", buf[i]);
strcat (linea, aux);
}
strcat(linea,"\n");

// ahora se escribe linea
if (pid == 0)
{
    
modoacceso = (MPI_MODE_CREATE | MPI_MODE_WRONLY);
MPI_File_open(MPI_COMM_SELF, "dat2", modoacceso, MPI_INFO_NULL, &dat2);
MPI_File_seek(dat2, 0, MPI_SEEK_SET);
MPI_File_write(dat2, linea, strlen(linea), MPI_CHAR, &info);
MPI_File_close(&dat2);
}
MPI_Finalize();
return 0;
}