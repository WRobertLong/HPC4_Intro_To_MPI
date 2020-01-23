#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
  int size, rank, i;
  int sbuf;
  int *rbuf;
  double time;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  rbuf = (int*) malloc (size);

  if (rank == 0) sbuf = 12;

  MPI_Bcast(&sbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);

  MPI_Barrier(MPI_COMM_WORLD);

  sbuf = sbuf + rank;

  MPI_Gather(&sbuf, 1, MPI_INT, rbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank == 0){
    printf("Rank 0 has:- \n");
    for (i=0; i<size; i++){
      printf ("- gathered value %d from Rank %d \n",rbuf[i],i);
    }
  }

  free(rbuf);

  MPI_Finalize();

  return(0);
}
