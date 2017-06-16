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

        const complex<double> j(0,1);

        int n = lgrid.nx0 - gnx/2 + 1;
	  	double c  = dt/2 * pow(2.0 * M_PI / l, 2.0);
        for(int i = 0; i < coef.size(); i++)
        {
            coef[i] *= exp(- j * c * double(n*n));
            n++;
        }
    }
}
