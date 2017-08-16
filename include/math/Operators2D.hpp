#pragma once

#include <complex>
#include <memory>
#include <fftw3.h>

#include "../grid/Grid.hpp"
#include "CMultFFTW.hpp"
namespace math
{
    // Free propagation function
    template<typename T_DATA>
    struct FreePropFS
    {
        const double dt;
        std::complex<double> iu = {0.0,1.0};
        FreePropFS(double dt_) : dt(dt_){};


        // Follows the time evolution scheme in Bauke et al.
        void operator()(T_DATA& data, double px, double py)
        {
            data *= std::exp(-iu * dt / 2.0 * (px*px + py*py));
        }
    };

    // Application of the free propagation function in
    template<typename T_CONT>
    void apply_2D_TEFS_op(T_CONT& data, int step, Grid::Grid<2> g)
    {
        const int nx = g.nx;
        const int ny = g.ny;
        const double dt = g.dt;
        FreePropFS<T_CONT> op(dt);

        const double dpx = 2*M_PI/(g.x1 - g.x0);
        const double dpy = 2*M_PI/(g.y1 - g.y0);

        double px = 0;
        double py = 0;

        const double px_offset = nx / 2 * dpx;
        const double py_offset = ny / 2 * dpy;

        /*
         * Iterate of the first half of the Grid
         * thus adding the offset to the momentum
         * space values.
         */
        for(int i = 0; i < ny/2; i++)
        {
            py = i * dpy + py_offset;
            for(int j = 0; j < nx/2; j++)
            {
                px = j * dpx + px_offset;
                op(data.get_value_ptr(j,i), px, py);
            }
        }

        for(int i = ny/2; i < ny; i++)
        {
            py = -py_offset + i * dpy;
            for(int j = nx/2; j < nx; j++)
            {
                px = -px_offset + j * dpx;
                op(data.get_value_ptr(j,i), px, px);
            }
        }
    }
}