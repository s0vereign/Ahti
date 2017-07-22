#include <stdlib.h>
#include <fftw3.h>
#include <iostream>


#define DEBUG_ENABLED
#include "worker/SerialWorker2D.hpp"


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

    auto phi = [psi_0](std::complex<double> x, std::complex<double> y)
    {

        return psi_0(x) * psi_0(y);
    };

    auto pot_fun = [](double x, double y)
    {
        return std::complex<double>(x * x / 2.0 + y*y/2.0, 0);
    };

    const double dt = 0.0156637;
    const double Nt = 10;

    const double xmax = 6.0;
    const double xmin = -xmax;
    const double ymax = xmax;
    const double ymin = xmin;
    const int nx = 500;
    const int ny = 500;

    Grid::Grid<2> g(xmin, xmax, nx, ymin, ymax, ny, 0, Nt*dt, Nt);

    Worker::start_serial_worker(g, phi, pot_fun);
    return EXIT_SUCCESS;

}
