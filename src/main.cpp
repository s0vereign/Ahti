#include <stdlib.h>

#include <iostream>

#include "worker/SerialWorker.hpp"

int
main(int argc, char **argv)
{


    int size;
    int rank;

    const double inv_fthsqrt_pi(0.7511255444649425);
    // MPI calls
    
    auto in_fun = [inv_fthsqrt_pi](std::complex<double> x) {return inv_fthsqrt_pi  * 2* x * std::exp(-x*x/2.0);};
    auto pot_fun = [](double x) {return x*x/2.0;};

    Grid::Grid<1> g(-30.0, 30.0, 15000, 0.0, 1.0, 3);
    
    Worker::start_serial_worker(g, in_fun, pot_fun);

    return EXIT_SUCCESS;

}
