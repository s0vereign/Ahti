#pragma once

#include <complex>
#include <vector>

#include "grid/Grid.hpp"
#include "grid/LocalGrid.hpp"


#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif


namespace math{

    using std::complex;
    using std::vector;
    using std::exp;
    using Grid::LocalGrid;
    using Grid::Grid;

    int get_n(int n, int gnx)
    {
        return n - gnx/2 + 1;
    }

    template<typename POT>
    void vals_ev(vector<complex<double> >& vals,
                 vector<complex<double> >& coef,
                 const LocalGrid<1>& lgrid,
                 Grid<1>& grid,
                 int ind_s,
                 POT p
                 )
    {
        const int nx = lgrid.nx1 - lgrid.nx0;
        const int gnx = grid.nx;
        const double l0 = grid.x1 - grid.x0;
        const complex<double> iu(0,1);
        int n = ind_s - gnx / 2 + 1; 
        double x = lgrid.x0;
        double dx = grid.dx;
        DEBUG("x0 = " << x << ", n = " << n);
        
        for(unsigned int i = 0; i < vals.size(); i++)
        {
            
            for(unsigned int j = 0; j < coef.size(); j++)
            {

                vals[i] += coef[j]*exp(iu*2.0*M_PI/l0*double(n)*x);
                
            }
            
            n++;
            x += dx;
        }
    }
} // MATH