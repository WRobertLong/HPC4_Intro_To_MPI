#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
  int size, rank, i, arraysize;
  int *rbuf, *sbuf, *gbuf;
  double time;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  arraysize = 4;
  rbuf = (int*) malloc (arraysize);
  sbuf = (int*) malloc (arraysize * size);
  gbuf = (int*) malloc (arraysize * size);

  if (rank == 0){
    for (i=0; i<arraysize*size; i++){
      sbuf[i] = i;
      gbuf[i] = 0;
    }
  }else{
   for (i=0; i<arraysize*size; i++){
     sbuf[i] = 0;
     gbuf[i] = 0;
    }
  }

  for (i=0; i<arraysize; i++) rbuf[i] = 0;

  MPI_Scatter(sbuf,arraysize,MPI_INT,rbuf,arraysize,MPI_INT,0,MPI_COMM_WORLD);

  MPI_Barrier(MPI_COMM_WORLD);

  for (i=0; i<arraysize; i++) rbuf[i] += rank;

  MPI_Gather(rbuf,arraysize,MPI_INT,gbuf,arraysize,MPI_INT,0,MPI_COMM_WORLD);

  if (rank == 0){
    for (i=0; i<arraysize*size; i++){
      printf (" %d  ", gbuf[i]);
    }
    printf ("\n");
  }

  MPI_Finalize();

}
