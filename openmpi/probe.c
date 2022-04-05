#include <mpi.h>
#include <stdio.h>

int main (int argc, char **argv)
{

int   pid, npr, origen, destino, ndat, tag;
int   i, longitud, tam;
int   *VA, *VB;
MPI_Status info;

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &pid);
MPI_Comm_size(MPI_COMM_WORLD, &npr);

if (pid == 0)
{
srand(time(NULL));
longitud = rand() % 100;
VA = (int *) malloc (longitud*sizeof(int));
for (i=0; i<longitud; i++) VA[i] = i;

printf("\n valor de VA en P0 antes de enviar los datos\n\n");
for (i=0; i<longitud; i++) printf("%4d", VA[i]);
printf("\n\n");

destino = 1; tag = 0;
MPI_Send(VA, longitud, MPI_INT, destino, tag, MPI_COMM_WORLD);
}
else if (pid == 1)
{

origen = 0; tag = 0;
MPI_Probe(origen, tag, MPI_COMM_WORLD, &info);
MPI_Get_count(&info, MPI_INT, &tam);

if(tam != MPI_UNDEFINED)
{
VB = (int *) malloc(tam*sizeof(int));
MPI_Recv(VB, tam, MPI_INT, origen, tag, MPI_COMM_WORLD, &info);
}

printf("\n valor de VB en P1 tras recibir los datos\n\n");
for (i=0; i<tam; i++) printf("%4d", VB[i]);
printf("\n\n");
}
MPI_Finalize();
return 0;
}