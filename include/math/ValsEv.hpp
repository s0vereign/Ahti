#pragma once

#include <complex>
#include <vector>
#include <cassert>

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
                 const Grid<1>& grid,
                 POT p
                 )
    {
	  	// local number of grid points
        const int nx = lgrid.nx1 - lgrid.nx0;

	  	// Global number of grid points
        const int gnx = grid.nx;

	  	// length of the box
        const double l0 = grid.x1 - grid.x0;
        const complex<double> iu(0,1);

	  	// Starting index for each loop (n has to be reset to this after each point calculation)
	  	const int n0 =  - gnx / 2 + 1;

	  	int n = n0;
      	double x = lgrid.x0;
      	const double dx = grid.dx;
  		const double c =  2.0*M_PI/l0;

		for(unsigned int i = 0; i < vals.size(); i++)
        {
            
            for(unsigned int j = 0; j < coef.size() - 1; j++)
            {

                vals[i] += coef[j]* exp(  iu * c * double(n) * x);
                n++;
            }
		        n = n0;
            x += dx;
        }

    }

	template<typename POT>
	void phase_fac( LocalGrid<1> lgrid,
					Grid<1> g,
					POT p,
					vector<complex<double> >& vals
				  )
	{

  		double x  = lgrid.x0;
  		const double dx = lgrid.dx;
  		const double dt = g.dt;
  		const complex<double> iu(0,1);
  		for(int i = 0; i < vals.size(); i++)
  		{
			vals[i] *= std::exp(- iu * dt * p(x));
			x += dx;
		}

	}
} // MATH
