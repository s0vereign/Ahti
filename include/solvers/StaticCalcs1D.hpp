#pragma once 


#include <complex>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <fftw3.h>

#include "grid/CGrid.hpp"
#include "grid/LocalGrid.hpp"
#include "math/FourierCoeff.hpp"
#include "math/CoeffEv.hpp"
#include "math/ValsEv.hpp"
#include "containers/Array1D.hpp"

#include "debug/DebugDef.h"
#include "output/SaveStep.hpp"



#define FILE "wf_out.h5"

namespace solvers
{
    using std::complex;
    using std::vector;


    void shift_res(vector<complex<double>>& res)
    {
        // This function shifts the real spaced function
        // to the right index position in 1D

        vector<complex<double>> cpy(res.size());
        std::copy(res.begin()+res.size()/2, res.end(), cpy.begin());
        std::copy(res.begin(), res.begin() + res.size()/2 , cpy.begin()+cpy.size()/2);
        std::copy(cpy.begin(), cpy.end(), res.begin());
    };

	void ex_im_rl(vector<complex<double>>& res)
	{
	  	// This function is a temporary hack in order to
	  	// solve the sign question


		std::transform(res.begin(), res.end(), res.begin(),
					   [](complex<double> a)
					   {
		  					return complex<double>(a.imag(), a.real());
						});
	};

    template<typename DIST>
    void calc_coeff(Grid::LocalGrid<1> lgrid, Grid::CGrid<1> g, DIST d,vector<complex<double> >& res)
    {
        const int n0 = lgrid.nx0  - g.nx / 2 + 1;
        double dx = lgrid.dx;
        double ind0 = double(n0);
        for( int i = 0; i < res.size(); i++)
        {
            math::fourier_1D_init(ind0, g.nx, d, dx, g.x0, res[i]);
            ind0++;

        }
    };

    template<typename T_VAL, typename T_IN>
    void recalc_coeff(Grid::LocalGrid<1> lgrid, Grid::CGrid<1> g, T_VAL& coef, T_IN psi)
    {
        const int n0 = lgrid.nx0 - g.nx / 2 + 1;
        double dx = lgrid.dx;
        double ind0 = double(n0);

        for(size_t i = 0; i  < coef.size(); i++)
        {
            math::fourier_1D(ind0, g.nx, psi, dx, g.x0, coef[i]);
            ind0++;
        }
    };

    template<typename T_VAL, typename DIST>
    void init_psi(Grid::CGrid<1> g, DIST d, T_VAL& psi)
    {

        double x = g.x0;
        double dx = g.dx;

        for(size_t i = 0; i < psi.get_nx(); i++)
        {
            psi.set_stdc(i, d(x));
            x += dx;
        }
    };


    template<typename T_VAL>
    void weigh_corr_fun(T_VAL& corr_fun, Grid::CGrid<1> g)
    {
        for(unsigned int i = 0; i < g.nt; i ++)
        {
            corr_fun[i] *= 1 - cos(2*M_PI*g.t1*i*g.dt);
        }
    }


}
