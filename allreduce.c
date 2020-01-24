/*

Robert Long 23 Jan 2020

HPC4 course

MPI All reducen practical

*/ 

#include <mpi.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
  int size, rank;
  int sum, buff;
  double time;

  MPI_Init(&argc, &argv);

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  sum =0;

  buff = rank;
  
  time = MPI_Wtime();

  MPI_Allreduce(&buff, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

  time = MPI_Wtime() - time;

  printf ("sum = %d on processor %d\n", sum, rank);

  MPI_Barrier(MPI_COMM_WORLD);

  if (rank == 0) printf ("time taken = %f \n",time);

  MPI_Finalize();

}
