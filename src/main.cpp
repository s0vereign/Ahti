#include <stdlib.h>
#include <fftw3.h>
#include <iostream>


#define DEBUG_ENABLED
#include "worker/SerialWorker.hpp"


int
main(int argc, char **argv)
{


    int size;
    int rank;

    const double inv_fthsqrt_pi(0.7511255444649425);
    const double inv_sqrt_two(0.70710678118654757);
    const double inv_sqrt_eight(0.35355339059327379);
    // MPI calls
    
    auto psi_0 = [inv_fthsqrt_pi](std::complex<double> x)
    {

          return std::complex<double>(inv_fthsqrt_pi   * std::exp(-x*x/2.0));

    };



    auto psi_1 = [inv_fthsqrt_pi, inv_sqrt_two](std::complex<double> x)
    {
        return std::complex<double>(inv_sqrt_two * inv_fthsqrt_pi * 2 * x * std::exp(-x*x/2.0));
    };


    auto psi_2 = [inv_fthsqrt_pi, inv_sqrt_eight, psi_0](std::complex<double> x)
    {
        return std::complex<double>(inv_sqrt_eight * (4.0*x*x - 2.0) * psi_0(x));
    };
    auto phi = [psi_0, psi_1, psi_2, inv_sqrt_two](std::complex<double> x)
    {
        return 0.57735026918962573*(psi_0(x)+psi_1(x)+psi_2(x));
    };

    auto pot_fun = [](double x)
    {
        return std::complex<double>(x * x / 2.0, 0);
    };

    const double dt = 0.3141592653589793;
    const double Nt = 2000;
    Grid::Grid<1> g(-8.0, 8.0, 2000, 0.0, dt*Nt, Nt);
    Worker::start_serial_worker(g, phi, pot_fun);


    return EXIT_SUCCESS;

}
