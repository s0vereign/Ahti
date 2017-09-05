#include <stdlib.h>
#include <fftw3.h>
#include <iostream>


#define DEBUG_ENABLED
#include "worker/SerialWorker3D.hpp"
#include "../include/quantumsystems/Harmonicoscillator.hpp"

int
main(int argc, char **argv)
{


    int size;
    int rank;

    using qsystems::harmosc::Psi0;
    using qsystems::harmosc::Psi1;
    using qsystems::harmosc::Psi2;

    auto phi = [](const std::complex<double>& x,
                  const std::complex<double>& y,
                  const std::complex<double>& z)
    {
        Psi2 p2;
        Psi0 p0;

        return p0(x) * p0(y) * p0(z);
    };

    using V = qsystems::harmosc::V_3D;

    V pot_fun;
    const double dt = 0.01;
    const double Nt = 2;

    const double xmax = 6.0;
    const double xmin = -6.0;
    const double ymax = xmax;
    const double ymin = xmin;
    const double zmax = xmax;
    const double zmin = xmin;
    const int nx = 200;
    const int ny = 200;
    const int nz = 200;


    Grid::Grid<3> g(xmin, xmax, ymin, ymax, zmin, zmax, nx, ny, nz, 0, Nt*dt, Nt);

    Worker::start_serial_worker(g, phi, pot_fun);
    std::cout << "dt was " << g.dt << std::endl;
    return EXIT_SUCCESS;

}
