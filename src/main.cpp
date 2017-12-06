#include <stdlib.h>
#include <fftw3.h>
#include <iostream>
#include <cstdlib>
#include <omp.h>


#define DEBUG_ENABLED
#include "../include/containers/Array1D.hpp"
#include "grid/CGrid.hpp"
#include "solvers/Split_Solver_1D.hpp"
#include "../include/quantumsystems/Harmonicoscillator.hpp"
#include "../include/quantumsystems/dist-harm-osc.hpp"


/** @file main.cpp
 *  @author Maximilian Böhme
 *  @brief The file containing the main function
 * */


/**
 * @brief The main function. The entry point and currently where the simulation configuration is done.
 *
 * The main method is the basic configuration point in the project.
 * In order to define a system one has to include the desired headers
 * contained in the ../include/quantumsystems folder. This will provide the
 * desired potential function objects as well as some Eigenfunctions if the
 * system has a analytical solution. The next dependency is the choice of the
 * solver-rountine. This depends in the spatial dimensionality of the system.
 * Currently the project only provides the split-operator method in order to
 * solve a system to up to three dimensions. The general unit system the code
 * currently uses is the atomic unit system. If you aren't familiar with this
 * particular unit system, please read: https://en.wikipedia.org/wiki/Atomic_units.
 *
 * The argc argument specifies in the current implementation the number of OpenMP
 * threads the code uses. So for instane the call
 * ./ahti 4
 * will start a simulation with 4 OpenMP threads.
 *
 * In order to configure a simulation the user has to specify a grid of the
 * corresponding dimensionality. The headers are located in the ../include/grid
 * folder. In order to create a grid-spec object please refer to the documentation
 * of the corresponding headers.
 *
 * So in a nutshell:
 * 1. Include all the desired headers
 * 2. Instantiate the function objects of the test-wave-function and the potential
 * 3. Specify the grid parameters by instantiating a grid object
 * 4. Call the solver function
 *
 * @return: int code which indicates if the program ran succsessfull
 */
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
    using V = qsystems::harmosc::V_1D;


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
        Psi1 p1;
        Psi2 p2;
        return p0(x);
    };

    double a1 = 0.1;
    double w1 = 2 * M_PI/1000;
    //V pot_fun(w1, w1, w1, a1, a1, a1);
    V pot_fun;
    const double dt = 0.001;
    const double Nt = 10000;

    const double xmax = 6.0;
    const double xmin = -6.0;
    const double ymax = xmax;
    const double ymin = xmin;
    const double zmax = xmax;
    const double zmin = xmin;
    const int nx = 1000;
    const int ny = 500;
    const int nz = 300;


    //CGrid::CGrid<3> g(xmin, xmax, ymin, ymax, zmin, zmax, nx, ny, nz, 0, Nt*dt, Nt);
    //CGrid::CGrid<2> g(xmin, xmax, ymin, ymax, nx, ny, 0, dt*Nt, Nt);
    Grid::CGrid<1> g(xmin, xmax, nx, 0, dt*Nt, Nt);
    solvers::solve(g, psi1D, pot_fun, num_threads);
    std::cout << "dt was " << g.dt << std::endl;
    return EXIT_SUCCESS;

}
