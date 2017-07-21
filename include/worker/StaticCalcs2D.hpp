#pragma once

#include <fftw3.h>

#include "../grid/Grid.hpp"

namespace Worker
{

    template <typename T_CONT, typename  T_DIST>
    void init_psi(T_CONT& vals, T_DIST p, Grid::Grid<2> g)
    {
        double x = g.x0;
        double y = g.y0;
        const int nx = g.nx;
        const int ny = g.ny;
        const double dx = g.dx;
        const double dy = g.dy;

        for(int i = 0; i < nx; i++)
        {

            for(int j = 0; j < ny; j++)
            {
                vals.set(p(x,y),i,j);
                y += dy;
            }

            x += dx;
        }
    };

}