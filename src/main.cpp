#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// Alpaka for Kernel Acceleration
#include <alpaka/alpaka.hpp>

// MPI
#include <mpi.h>

// Include Gaussian Test functor
#include "testfunctors/Gaussian.hpp"

// Include Gridinformation
#include "grid/SimConf.hpp"
#include "grid/GridControl.hpp"
#include "grid/Globalgrid.hpp"
#include "grid/Localgrid.hpp"

// Include Master and Worker
#include "master/Master.hpp"
#include "worker/Worker.hpp"

// Include the TimeConf Type
#include "timeconf/Timeconf.hpp"

// Include Config struct
#include "config/Config1D.hpp"


using namespace Grid;


int
main(int argc, char **argv)
{


    int size;
    int rank;

    // MPI calls
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Datatype LGrid1D;
    MPI_Datatype TimeType;
    commit_Localgrid1D(&LGrid1D);
    TimeConf::commit_TimeConf(&TimeType);
    MPI_Comm_size(MPI_COMM_WORLD,&size);


    size_t nx = 10000;
    config::Config1D<testfunctions::Gaussian> c(0.0,
                                                100.0,
                                                0.0,
                                                100.0,
                                                nx,
                                                testfunctions::Gaussian());



    Sim1D* sim = create_Sim1D(nx, nx-1, 0);


    if(rank == 0)
    {
	     Master::start_master(&LGrid1D, c, sim, size, rank);
    }

    if(rank != 0)
    {
         Worker::start_worker(&LGrid1D, c,rank);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return EXIT_SUCCESS;

}
