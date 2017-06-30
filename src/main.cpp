#include <stdlib.h>

#include <iostream>


// Alpaka for Kernel Acceleration
//#include <alpaka/alpaka.hpp>

// MPI
#include <mpi.h>




// Use useful debugging output
#define DEBUG_ENABLED
#include "debug/DebugDef.h"

#include "worker/Worker.hpp"
#include "worker/SerialWorker.hpp"

int
main(int argc, char **argv)
{


    int size;
    int rank;

    const double inv_fthsqrt_pi(0.7511255444649425);
    // MPI calls
    
    auto in_fun = [inv_fthsqrt_pi](std::complex<double> x) {return inv_fthsqrt_pi   * std::exp(-x*x/2.0);};
    auto pot_fun = [](double x) {return x*x/2.0;};

    Grid::Grid<1> g(-8.0, 8.0, 5000, 0.0, 0.01, 10);
    
    Worker::start_serial_worker(g, in_fun, pot_fun);

    return EXIT_SUCCESS;

}
