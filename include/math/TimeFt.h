#pragma once


#include <complex>
#include <vector>

#include "grid/CGrid.hpp"
#include "FourierCoeff.hpp"


namespace math
{
    //using namespace CGrid;
    template<typename T_G, typename T_VAL>
    void time_ft(T_G g, T_VAL& corr_fun, T_VAL& spec_fun)
    {
        const size_t nt = g.nt;
        const double dt = g.dt;

        int f_ind = - nt / 2 + 1;

        for(unsigned int i  = 0;  i < nt; i++)
        {
            fourier_1D(f_ind, nt, corr_fun, dt, 0, spec_fun[i]);
            f_ind++;
        }

    }
}