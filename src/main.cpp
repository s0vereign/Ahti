#include <stdlib.h>
#include <fftw3.h>
#include <iostream>


#define DEBUG_ENABLED
#include "worker/SerialWorker1D.hpp"
#include "../include/quantumsystems/Harmonicoscillator.hpp"

int
main(int argc, char **argv)
{


    int size;
    int rank;

    using qsystems::harmosc::Psi0;
    using qsystems::harmosc::Psi1;
    using qsystems::harmosc::Psi2;
    using V = qsystems::harmosc::V_1D;


    auto phi = [](const std::complex<double>& x,
                  const std::complex<double>& y,
                  const std::complex<double>& z)
    {
        Psi2 p2;
        Psi1 p1;
        Psi0 p0;

        return p2(x) * p2(y) * p2(z);
    };

    auto phi2D = [](const std::complex<double>& x,
                  const std::complex<double>& y)
    {
        Psi2 p2;
        Psi1 p1;
        Psi0 p0;

        return p0(x) * p0(y);
    };

    auto psi1D = [](const std::complex<double>& x)
    {
        Psi0 p0;
        return p0(x);
    };

    V pot_fun;
    const double dt = 0.01;
    const double Nt = 100;

    const double xmax = 6.0;
    const double xmin = -6.0;
    const double ymax = xmax;
    const double ymin = xmin;
    const double zmax = xmax;
    const double zmin = xmin;
    const int nx = 1000;
    const int ny = 1000;
    const int nz = 200;


//    Grid::Grid<3> g(xmin, xmax, ymin, ymax, zmin, zmax, nx, ny, nz, 0, Nt*dt, Nt);
//    Grid::Grid<2> g(xmin, xmax, ymin, ymax, nx, ny, 0, dt*Nt, Nt);
    Grid::Grid<1> g(xmin, xmax, nx, 0, dt*Nt, Nt);
    Worker::start_serial_worker(g, psi1D, pot_fun);
    std::cout << "dt was " << g.dt << std::endl;
    return EXIT_SUCCESS;

}
