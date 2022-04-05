#include <stdio.h>
#include "mpi.h"

#define DATOS   //tipos de tag
#define CONTROL 1

#define MAXIMA_LONG 10   //dimension buffer consumidor

void consumir_datos(float buffer[], int longitud)
{
int i;
float suma = 0.0;
for(i=0; i<longitud; i++) suma += buffer[i];
printf("\t\t\t\tCONSUM: buffer[]=%3.2f ->suma:%3.2f\n", buffer[0], suma );
}

int main(int argc, char** argv) //consumidor
{
int  pid;   // Identificador del proceso
int  nveces, i, nfila;
MPI_Status status;

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &pid);

float buffer_consum[MAXIMA_LONG];
int longitud;
while (1)
{
MPI_Recv(&buffer_consum[0], MAXIMA_LONG, MPI_FLOAT, 0,
MPI_ANY_TAG, MPI_COMM_WORLD, &status);
if (status.MPI_TAG == CONTROL) break;
MPI_Get_count(&status, MPI_FLOAT, &longitud);
consumir_datos(&buffer_consum[0], longitud);
}
printf ("\n\n\t\t\t\tFIN proceso CONSUMIDOR con pid: %d\n\n", pid);
MPI_Finalize();
return 0;
} /* main */
