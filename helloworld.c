#include <stdio.h>
#include <mpi.h>

int main (int argc, char *argv[]) {
   
   MPI_Init(&argc, &argv); /* initialise MPI */
   
   printf("Hello World\n"); 
   
   MPI_Finalize(); /* finalise MPI */
}
