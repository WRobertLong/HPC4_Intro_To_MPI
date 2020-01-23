#include <stdio.h>
#include <mpi.h>

int main (int argc, char *argv[]) {
   int rank, size;
   
   MPI_Init(&argc, &argv); /* initialise MPI */
   MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* Get rank */
   MPI_Comm_size(MPI_COMM_WORLD, &size); /* Get size */
   /* Only rank == 0 should print */
   if (rank == 0) {   
     printf("Hello from rank %d of size %d \n",rank, size);
   }
   MPI_Finalize();
}
