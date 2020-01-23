#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main (int argc, char *argv[]) {
   int rank, size, i;
   int send,recv;
   MPI_Status status;
   
   MPI_Init(&argc, &argv); /* initialise MPI */
   MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* get rank */
   MPI_Comm_size(MPI_COMM_WORLD, &size); /* get size */
   
   if (size == 1) {
    printf ("Error: number of processors must be 2 or greater\n");
    MPI_Finalize();
    exit (1);
   }
   
   send =0;
   recv = 0;
   
   if (rank == 0) {send = 8;} /* Initialise send buffer */
   for (i=0; i<100; i++){ /* repeat for 100 iterations */
    if (rank == 0) {
/* blocking send on first processor to second */
    MPI_Ssend(&send,1,MPI_INT, 1, 1, MPI_COMM_WORLD);
    printf ("%d sent on processor %d\n",send,rank);
/* blocking receive on first processor from second */    
    MPI_Recv(&recv,1,MPI_INT, 1, 2, MPI_COMM_WORLD, &status);
    printf ("%d received on processor %d\n",recv,rank);
    printf ("Adding 1 to receive buffer and placing in send buffer\n");
    send = recv +1;
  } else if (rank == 1) {
/* blocking receive on second processor from first */
    MPI_Recv(&recv,1,MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
    printf ("%d received on processor %d\n",recv,rank);
    printf ("Adding 1 to receive buffer and placing in send buffer\n");
    send = recv +1;
/* blocking send on first processor to second */
    MPI_Ssend(&send,1,MPI_INT, 0,2,MPI_COMM_WORLD);
    }
   }
   MPI_Finalize(); /* finalise MPI */
}
