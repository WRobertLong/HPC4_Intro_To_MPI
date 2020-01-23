#include <stdio.h>
#include <mpi.h>

int main (int argc, char *argv[]) {
   int rank, size;

   MPI_Init(&argc, &argv); /* Initialise MPI */   
   MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* Get rank */   
   MPI_Comm_size(MPI_COMM_WORLD, &size); /* Get size */   
   
   printf("Hello from rank %d of size %d \n",rank, size);
   
   MPI_Finalize();
}
