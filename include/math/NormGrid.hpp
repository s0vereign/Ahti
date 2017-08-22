#pragma once

#include <complex>
#include <fftw3.h>

#include "../grid/Grid.hpp"
#include "../containers/Array2D.hpp"
#include "CMultFFTW.hpp"

namespace math
{
    template<typename T_CONT>
    void norm_grid(Grid::Grid<2> g, T_CONT& data)
    {
        const int nx = g.nx;
        const int ny = g.ny;
        const std::complex<double> z(1.0/(nx*ny),0);

        for(int i = 0; i < nx; i++)
        {
            for(int j = 0; j < ny; j++)
            {
                data.mult_data(i,j,z);
            }
        }
    }
}