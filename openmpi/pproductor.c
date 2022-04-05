#include <stdio.h>
#include "mpi.h"

#define DATOS  0  //tipos de tag
#define CONTROL 1

#define NFIL 20   //dimensiones de la matriz
#define NCOL 10


float matriz[NFIL][NCOL];
void producir_datos(int vez, int fila)
{

int i;
for(i=0; i<NCOL; i++) matriz[fila][i] = (float)vez + (float)fila;
printf("PROD: vez(%d)-fila(%d)->[%.2f]\n", vez+1, fila, matriz[fila][0]);
}
int main(int argc, char** argv) // productor
{

int    pid;     // Identificador del proceso
int    nveces, i, nfila;
MPI_Status status;

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &pid);

printf("Numero de veces a transmitir filas de la matriz[%d][%d]-->  ",NFIL,NCOL);
scanf("%d", &nveces);

for(i=0; i<nveces; i++)
{
for (nfila=0; nfila<NFIL; nfila++)
{
producir_datos(i,nfila);
MPI_Ssend(&matriz[nfila][0], NCOL, MPI_FLOAT, 1, DATOS, MPI_COMM_WORLD);
}
}
MPI_Ssend(&matriz[0][0], NCOL, MPI_FLOAT, 1, CONTROL, MPI_COMM_WORLD);
printf ("\nFIN proceso PRODUCTOR con pid: %d\n\n", pid);
MPI_Finalize();
return 0;
} /* main */