#include <stdlib.h>
#include <fftw3.h>
#include <iostream>
#include <cstdlib>
#include <omp.h>


#define DEBUG_ENABLED
#include "solvers/Split_Solver_3D.hpp"
#include "../include/quantumsystems/Harmonicoscillator.hpp"
#include "../include/quantumsystems/dist-harm-osc.hpp"

int
main(int argc, char **argv)
{


    int num_threads = 0;

    if(argc < 2)
    {
        num_threads = 1;
        std::cout << "Using serial execution" << std::endl;
        omp_set_num_threads(num_threads);
    }
    else
    {
        num_threads = atoi(argv[1]);
        std::cout << "Using parallel execution with " << num_threads << " threads" << std::endl;
        omp_set_dynamic(0);
        omp_set_num_threads(num_threads);
    }

    using qsystems::harmosc::Psi0;
    using qsystems::harmosc::Psi1;
    using qsystems::harmosc::Psi2;
    using V = qsystems::harmosc::V_3D;


    auto phi = [](const std::complex<double>& x,
                  const std::complex<double>& y,
                  const std::complex<double>& z)
    {
        Psi2 p2;
        Psi1 p1;
        Psi0 p0;

        return p0(x) * p0(y) * p0(z);
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

    double def = 0.01;
    V pot_fun;
    const double dt = 0.001;
    const double Nt = 1000;

    const double xmax = 6.0;
    const double xmin = -6.0;
    const double ymax = xmax;
    const double ymin = xmin;
    const double zmax = xmax;
    const double zmin = xmin;
    const int nx = 300;
    const int ny = 200;
    const int nz = 200;


    Grid::Grid<3> g(xmin, xmax, ymin, ymax, zmin, zmax, nx, ny, nz, 0, Nt*dt, Nt);
//    Grid::Grid<2> g(xmin, xmax, ymin, ymax, nx, ny, 0, dt*Nt, Nt);
//    Grid::Grid<1> g(xmin, xmax, nx, 0, dt*Nt, Nt);
    solvers::solve(g, phi, pot_fun, num_threads);
    std::cout << "dt was " << g.dt << std::endl;
    return EXIT_SUCCESS;

}
