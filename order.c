/* 
  Robert Long
  MPI Scan & MPI Barrier practical
  23 Jan 2020
*/

#include <mpi.h>
#include <stdio.h>

int main(int argc, char * argv[]) {
  int size, rank, i;
  int sum, buff;
  double time;

  MPI_Init( & argc, & argv);

  MPI_Comm_size(MPI_COMM_WORLD, & size);
  MPI_Comm_rank(MPI_COMM_WORLD, & rank);

  sum = 0;

  buff = rank;

  time = MPI_Wtime();

  MPI_Scan( & buff, & sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

  time = MPI_Wtime() - time;

  for (i = 0; i < size; i++) {
    if (rank == i) {
      printf("sum = %d on processor %d\n", sum, rank);
      MPI_Barrier(MPI_COMM_WORLD);
    }
  }

  if (rank == 0) {
    printf("time taken = %f \n", time);
  }

  MPI_Finalize();

  return (0);

}