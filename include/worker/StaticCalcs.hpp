#pragma once 


#include <complex>
#include <vector>
#include <algorithm>

#include "grid/Grid.hpp"
#include "grid/LocalGrid.hpp"
#include "math/FourierCoeff.hpp"
#include "math/CoeffEv.hpp"


namespace Worker 
{
    using std::complex;
    using std::vector;
    
    template<typename DIST>
    void calc_coeff(Grid::LocalGrid<1> lgrid, Grid::Grid<1> g, DIST d,vector<complex<double> >& res)
    {
        const int n0 = lgrid.nx0 - g.nx/2 + 1;
        const int n1 = lgrid.nx1 - g.nx/2 + 1;
        
        double dx = lgrid.dx;
        
        int ind0 = n0;
        
        for( complex<double> & c : res)
        {
            math::fourier_1D_serial(ind0, g.nx, d, dx, lgrid.x0, c);
            ind0 += 1;
        }
        
    };
    
    template<typename DIST, typename POT>
    void time_evo(Grid::LocalGrid<1> lgrid, Grid::Grid<1> g, DIST d, POT p, vector<complex<double>>& res)
    {
        int t = 0;
        int nt = g.nt;
        const double dt = (g.tmax-g.tmin)/(nt);
        
        for(int i = 0; i < nt; i++)
        {
            
        }
        
    };
}
