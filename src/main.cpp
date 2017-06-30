#include <stdlib.h>

#include <iostream>
#define DEBUG_ENABLED

#include "worker/SerialWorker.hpp"

int
main(int argc, char **argv)
{


    int size;
    int rank;

    const double inv_fthsqrt_pi(0.7511255444649425);
    // MPI calls
    
    auto in_fun = [inv_fthsqrt_pi](std::complex<double> x)
    {

          return std::complex<double>(inv_fthsqrt_pi   * std::exp(-x*x/2.0));

    };
    auto pot_fun = [](double x) {

          return std::complex<double>(x * x / 2.0, 0);


    };

    //auto pot_fun = [](double x) {return std::complex<double>(0,0);};
    Grid::Grid<1> g(-8.0, 8.0, 5000, 0.0, 0.90, 20);
    
    Worker::start_serial_worker(g, in_fun, pot_fun);


    return EXIT_SUCCESS;

}
