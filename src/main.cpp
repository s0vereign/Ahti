#include <stdlib.h>
#include <fftw3.h>
#include <iostream>


#define DEBUG_ENABLED
#include "worker/SerialWorker3D.hpp"


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

    auto phi = [psi_0](std::complex<double> x, std::complex<double> y, std::complex<double> z)
    {

        return psi_0(x) * psi_0(y) * psi_0(z);
    };

    auto pot_fun = [](double x, double y, double z)
    {
        return std::complex<double>(x * x / 2.0 + y*y/2.0 + z*z/2.0, 0);
    };

    const double dt = 0.0001;
    const double Nt = 2;

    const double xmax = 6.0;
    const double xmin = -6.0;
    const double ymax = xmax;
    const double ymin = xmin;
    const double zmax = xmax;
    const double zmin = xmin;
    const int nx = 300;
    const int ny = 300;
    const int nz = 300;


    Grid::Grid<3> g(xmin, xmax, ymin, ymax, zmin, zmax, nx, ny, nz, 0, Nt*dt, Nt);

    Worker::start_serial_worker(g, phi, pot_fun);
    std::cout << "dt was " << g.dt << std::endl;
    return EXIT_SUCCESS;

}
