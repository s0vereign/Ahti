#pragma once

#include <complex>
#include <vector>

#include "grid/Localgrid.hpp"

#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif

namespace math {
    
    using std::vector;
    using std::complex;
    using std::exp;
    using Grid::Localgrid1D;
    void evolve_coeff(vector<complex<double> >& coef,
                      int rank, 
                      int size,
                      int n, 
                      const Localgrid1D& lgrid,
                      double dt
                      )
    {
        const int nx = lgrid.nx;
        const complex<double> j(0,1);
        const double l = lgrid.xmax-lgrid.xmin;
        
        for(int i = 0; i < nx; i++)
        {
            coef[i] = coef[i] * exp(- j * (dt/2)*(4*M_PI*M_PI/(l*l)*n*n)); 
        }
    }
}