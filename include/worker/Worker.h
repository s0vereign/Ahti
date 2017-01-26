#ifndef WORKER_H
#define WORKER_H

#include "grid/Localgrid.h"

void start_worker(MPI_Datatype* LGrid1D, int mpi_id)
{
  MPI_Status status;
  Localgrid1D* lgrid = create_Localgrid1D(0,0,0);
  MPI_Recv(lgrid, 1,*LGrid1D, 0, 0, MPI_COMM_WORLD, &status);
  printf("Recieved local grid! \n");
  printf("Rank %i, nx = %i, xmax = %i, xmin = %i \n", mpi_id, lgrid->nx, lgrid->xmax, lgrid->xmin);

}


#endif
