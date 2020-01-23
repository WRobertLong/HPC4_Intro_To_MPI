/*

Basic node pair communication with MPI

Robert Long 23 Jan 2020

*/


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main (int argc, char *argv[]) {
   
  int send, recv, rank, size, i ;

  MPI_Status status;

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  send = 0 ; 
  recv = 0 ;

  for ( i = 0 ; i < 100 ; i++ ) {
    
    if ( rank == 0 ) {

      /* blocking send on first processor to second */
      MPI_Ssend(&send, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);

      /* blocking receive on first processor from second */
      MPI_Recv(&recv, 1, MPI_INT, 1, 2, MPI_COMM_WORLD, &status);
      send = recv + 1;

    } else {

      /* blocking receive on second processor from first */
      MPI_Recv(&recv, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

      send = recv + 1;

      /* blocking send on first processor to second */
      MPI_Ssend(&send, 1, MPI_INT, 0,2,MPI_COMM_WORLD);
    }
  printf("send: %d \n", send) ;

  }

  MPI_Finalize();

}

