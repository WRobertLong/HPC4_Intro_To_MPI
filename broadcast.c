/* 

  Robert Long
  MPI broadcast practical
  23 Jan 2020
*/


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main (int argc, char *argv[]) {


   int i, rank, size, sum, value, recv, rbuf, sbuf ;
   int right, left;
   double time;
   MPI_Status status;
   MPI_Request request;
  
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   
   if(rank == 0) {
     sbuf = 15 ;
  }
  
  MPI_Bcast(&sbuf, 1, MPI_INT, 0, MPI_COMM_WORLD) ;


  MPI_Barrier(MPI_COMM_WORLD);
  
  sbuf += rank ;
  MPI_Gather(&sbuf, 1, MPI_INT, &rbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);


  if (rank == 0) {
    for (i = 0; i < size; i++) {
       printf (" %d ", rbuf);
 
    }
    printf ("\n");
  }  


 
   MPI_Finalize();
}
