#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define tambuf 4*32

int main(int argc, char **argv)
{
int  pid, npr;
int  i, numdat, numint;
int  buf[tambuf], buf2[tambuf], modoacceso;

MPI_File dat1;
MPI_Status info;

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &pid);
MPI_Comm_size(MPI_COMM_WORLD, &npr);

numdat = 4;
numint = numdat * sizeof(int);
for(i=0; i<numdat; i++) buf[i] = (i+pid*numdat)*(i+pid*numdat);

modoacceso = (MPI_MODE_CREATE | MPI_MODE_RDWR);
MPI_File_open(MPI_COMM_SELF, "dat1", modoacceso, MPI_INFO_NULL, &dat1);
MPI_File_seek(dat1, pid*numint, MPI_SEEK_SET);
MPI_File_write(dat1, buf, numdat, MPI_INT, &info);
MPI_File_sync(dat1);

MPI_Barrier(MPI_COMM_WORLD);
sleep(3);

MPI_File_seek(dat1, ((pid+1)%npr)*numint, MPI_SEEK_SET);
MPI_File_read(dat1, buf2, numdat, MPI_INT, &info);
MPI_File_close(&dat1);

printf("\n > Pid %d ha leido %5d %5d %5d %5d \n", pid, buf2[0], buf2[1], buf2[2], buf2[3]);
MPI_Finalize();
return 0;
}