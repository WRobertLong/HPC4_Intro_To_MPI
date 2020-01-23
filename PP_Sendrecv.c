/*

MPI Combined communications practical

Robert Long 23 Jan 2020

*/


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main (int argc, char *argv[]) {
   
  int send, recv, rank, size, i, left, right, value, sum ;

  MPI_Status status;

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  right = rank + 1 ;
  left = rank - 1 ;
  value = rank ;
 
  if (right >= size) 
    right = right - size ;

  if (left < 0) 
    left = left + size ;

  send = 0 ; 
  recv = 0 ;
  sum = 0 ;

  for ( i = 0 ; i < rank ; i++ ) {
    
    MPI_Sendrecv(&value, 1, MPI_INT, 1, 1, 
                 &recv, 1, MPI_INT, 0, 1,
                 MPI_COMM_WORLD, &status) ;

    sum += recv ;

    value = recv ;
  
    printf("sum: %d \n", sum) ;

  }

  MPI_Finalize();

}

