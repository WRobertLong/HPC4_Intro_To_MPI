#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main (int argc, char *argv[]) {
   int i, rank, size, sum, value, recv;
   int right, left;
   double time;
   MPI_Status status;
   MPI_Request request;
/* Initialise MPI */   
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   
   sum = 0;
/* set value to be process rank */   
   value = rank;
/* find processors to right and left */   
   right = rank +1;
/* Circular topology p(size) -> p(0) */  
   if (right >= size) {
   right = right -size;
   }   
   left = rank -1;
/* circular topology p(-1) -> p(size -1) */   
   if (left < 0) {
   left = left + size;
   }
   
/* Loop over number of processors */
   time = MPI_Wtime();  /* start timer */ 
   for (i=0; i<size; i++) {
/* Non-blocking send to processor +1 */
     MPI_Issend(&value, 1, MPI_INT, right, 1, MPI_COMM_WORLD, &request);
/* blocking receive from processor -1 */   
     MPI_Recv(&recv, 1, MPI_INT, left, 1, MPI_COMM_WORLD, &status);
/* add up received value to sum */   
     sum = sum + recv;
/* test that comm has completed */   
     MPI_Wait(&request, &status);
     value = recv;
   }
   time = MPI_Wtime() - time; /* end timer */
   printf ("Rank %4d, sum=%4d, time=%10.8f.\n",rank,sum,time);
/* terminate MPI */   
   MPI_Finalize();
}
