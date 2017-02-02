#pragma once

#include "grid/Localgrid.h"

namespace Worker {


  void start_worker(MPI_Datatype* LGrid1D, int mpi_id)
  {

    MPI_Status status;
    Grid::Localgrid1D* lgrid = Grid::create_Localgrid1D(0,0,0);
    MPI_Recv(lgrid, 1,*LGrid1D, 0, 0, MPI_COMM_WORLD, &status);
    printf("Rank %i, nx = %i, xmax = %i, xmin = %i \n", mpi_id, lgrid->nx, lgrid->xmax, lgrid->xmin);

  }




} // Worker
