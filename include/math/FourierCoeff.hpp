#pragma once

#include <complex>
#define _USE_MATH_DEFINES
#include <cmath>

#define DEBUG_ENABLED
#include "debug/DebugDef.h"

namespace math {

    template<typename FUNC_PSI>
    void fourier_1D_serial( double m,
                            int nx,
                            FUNC_PSI& psi,
                            double h_,
                            double x0,
                            std::complex<double>& res)
    {
        using std::complex;
        using std::exp;


        complex<double> x(x0,0);
        complex<double> h(h_,0);
        complex<double> iu(0,1);


        double nx1 = double(nx);
        res = complex<double>(0.0,0.0);
        
        for(int i = 0; i < nx; i++)
        {   
            x += h;
            res += psi(x)*exp(-2*M_PI*m*iu*double(i)/nx1);
            
        }

        res *= 1/nx1;
	
    }

} // MATH
