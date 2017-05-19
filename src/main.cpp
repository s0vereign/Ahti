#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <iostream>

// Use useful debugging output
#define DEBUG_ENABLED
#include "debug/DebugDef.h"

#include "worker/SerialWorker.hpp"

int
main(int argc, char **argv)
{


    int size;
    int rank;

    const double inv_fthsqrt_pi(0.7511255444649425);
    // MPI calls
    
    auto in_fun = [inv_fthsqrt_pi](std::complex<double> x) {return inv_fthsqrt_pi * 2*x *  std::exp(-x*x/2.0);};
    auto pot_fun = [](double x) {return x*x/2.0;};

    Grid::Grid<1> g(-5.0, 5.0, 65536/8, 0.0, 1.0, 3);
    
    Worker::start_serial_worker(g, in_fun, pot_fun);

    return EXIT_SUCCESS;

}
