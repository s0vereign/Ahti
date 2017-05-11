#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>



// Alpaka for Kernel Acceleration
#include <alpaka/alpaka.hpp>

// MPI
#include <mpi.h>




// Use useful debugging output
#define DEBUG_ENABLED
#include "debug/DebugDef.h"

#include "worker/Worker.hpp"

int
main(int argc, char **argv)
{


    int size;
    int rank;

    const double inv_fthsqrt_pi(0.7511255444649425);
    // MPI calls
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    
    auto in_fun = [inv_fthsqrt_pi](std::complex<double> x) {return inv_fthsqrt_pi*std::exp(-x*x/2.0);};
    auto pot_fun = [](double x) {return x*x/2.0;};

    Grid::Grid<1> g(-10.0, 10.0, 65536/4, 0.0, 1.0, 10);
    Worker::start_worker(g, size, rank, in_fun, pot_fun);
    
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return EXIT_SUCCESS;

}
