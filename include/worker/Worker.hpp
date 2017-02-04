#pragma once

#include "grid/Localgrid.hpp"
#include "timeconf/Timeconf.hpp"

namespace Worker {


    void start_worker(MPI_Datatype* LGrid1D, MPI_Datatype * TimeType,int mpi_id)
    {

        MPI_Status status;
        Grid::Localgrid1D* lgrid = Grid::create_Localgrid1D(0,0,0);
        MPI_Recv(lgrid, 1,*LGrid1D, 0, 0, MPI_COMM_WORLD, &status);
        
    }




} // Worker
