#pragma once

#include <complex>
#include <vector>

#include "grid/Localgrid.hpp"

#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif


namespace math{

    using std::complex;
    using std::vector;
    using std::exp;
    using Grid::Localgrid1D;

    int get_n(int n, int gnx)
    {
        return n - gnx/2;
    }

    template<typename T_CONF>
    void vals_ev(vector<complex<double> >& vals,
                 vector<complex<double> >& coef,
                 const Localgrid1D& lgrid,
                 const T_CONF& conf,
                 int size, 
                 int rank)
    {
        const int nx = lgrid.nx;
        const int gnx = conf.gnx;
        const double l0 = lgrid.xmax - lgrid.xmin;
        const complex<double> iu(0,1);

        for(int i = 0; i < nx; i++)
        {
            for(int j = 0; i < nx; j++)
            {
                int n = get_n(j, gnx);
                vals[i] += coef[j]*exp(iu*2*M_PI/l0*n);
            }
        }
    }
} // MATH