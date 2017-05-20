#pragma once

#include <complex>
#include <vector>

#include "grid/LocalGrid.hpp"

#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif

namespace math {
    
    using std::vector;
    using std::complex;
    using std::exp;
    using Grid::LocalGrid;
    void evolve_coeff(vector<complex<double> >& coef,
                      const int gnx,
                      const double l,
                      const LocalGrid<1>& lgrid,
                      const double dt
                      )
    {

        //const int nx = lgrid.nx0;
        const complex<double> j(0,1);

        int n = lgrid.x0 - gnx/2 + 1;
        for(int i = 0; i < coef.size(); i++)
        {   
            
            coef[i] *= exp(- j * (dt/2)*(4*M_PI*M_PI/(l*l))*double(n*n)); 
            n++;
        }
    }
}
