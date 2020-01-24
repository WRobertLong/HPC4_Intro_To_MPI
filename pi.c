/* 
  Robert Long
  MPI parallel computation of Pi
  23 Jan 2020
*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char * argv[]) {
  int rank, size;
  MPI_Status status;
  int i, iter, liter;
  double npi, temp, recv;

  MPI_Init( & argc, & argv); /* Initialise MPI */
  MPI_Comm_rank(MPI_COMM_WORLD, & rank); /* Get rank */
  MPI_Comm_size(MPI_COMM_WORLD, & size); /* Get size */

  liter = 100000; /* Local iteration count */
  iter = size * liter; /* Total number of iterations */

  npi = 0.0;
  /* compute local pi */
  for (i = 1; i <= liter; i++) {
    temp = (((i + liter * rank) - 0.5) / iter) * (((i + liter * rank) - 0.5) / iter);
    npi = npi + 1.0 / (1.0 + temp);
  }
  
  /* Receive partial pi from all processors on rank 0 */
  if (rank == 0) {
    for (i = 1; i < size; i++) {
      MPI_Recv( & recv, 1, MPI_DOUBLE, i, i, MPI_COMM_WORLD, & status);
      npi = npi + recv;
    }
    /* print pi */
    printf("pi = %f\n", (4.0 * npi / iter));
  } else {
    /* All other processes send to rank 0 */
    MPI_Ssend( & npi, 1, MPI_DOUBLE, 0, rank, MPI_COMM_WORLD);
  }

  MPI_Finalize();
}