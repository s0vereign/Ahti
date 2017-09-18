#pragma once

#include <fftw3.h>
#include <complex>

#include "../containers/Array2D.hpp"
#include "../grid/Grid.hpp"
#include "../math/CMultFFTW.hpp"
#define DEBUG_ENABLED
#include "../debug/DebugDef.h"

namespace solvers
{

    template <typename T_CONT, typename  T_DIST>
    void init_psi(T_CONT& vals, T_DIST& p, Grid::Grid<2> g)
    {
        double x = g.x0;
        double y = g.y0;
        const int nx = g.nx;
        const int ny = g.ny;
        const double dx = g.dx;
        const double dy = g.dy;
        const double t0 = g.t0;


        for(int i = 0; i < nx; i++)
        {

            for(int j = 0; j < ny; j++)
            {
                std::complex<double> v = p(x,y);
                vals.set_real(v.real(),i,j);
                vals.set_imag(v.imag(),i,j);
                y += dy;

            }

            x += dx;
            y = g.y0;

        }
    };

}