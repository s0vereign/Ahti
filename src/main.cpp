#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// Alpaka for Kernel Acceleration
#include <alpaka/alpaka.hpp>

// MPI
#include <mpi.h>

// Include Gridinformation
#include "grid/SimConf.h"
#include "grid/GridControl.h"
#include "grid/Globalgrid.h"
#include "grid/Localgrid.h"

// Include Master and Worker
#include "master/Master.h"
#include "worker/Worker.h"

using namespace Grid;


int
main(int argc, char **argv)
{

    MPI_Init(&argc, &argv);

    int size;
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Datatype LGrid1D;
    commit_Localgrid1D(&LGrid1D);



    MPI_Comm_size(MPI_COMM_WORLD,&size);

    size_t nx = 1000;
    Sim1D* sim = create_Sim1D(nx, nx-1, 0);

    if(rank == 0)
    {
	     Master::start_master(&LGrid1D, sim, size, rank);
    }

    if(rank != 0)
    {
	     Worker::start_worker(&LGrid1D, rank);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return EXIT_SUCCESS;

}
