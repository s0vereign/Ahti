#pragma once

#include <complex>
#define _USE_MATH_DEFINES
#include <cmath>

#include "debug/DebugDef.h"

namespace math {

    template<typename FUNC_PSI>
    void fourier_1D_init(double m,
                         int nx,
                         FUNC_PSI &psi,
                         double h_,
                         double x0,
                         std::complex<double> &res)
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

            res += psi(x) * exp( - 2.0 * M_PI * m * iu * double(i) / nx1);
            x += h;
        }

	  	res *= 1 / nx1;
	
    }

    template<typename T_VAL, typename T_RES>
    void fourier_1D(double m,
                    int nx,
                    T_VAL& psi,
                    double h_,
                    double x0,
                    T_RES& res)
    {
        using std::complex;
        using std::exp;

        T_RES x(x0,0);
        T_RES h(h_,0);
        T_RES iu(0,1);

        double nx1 = double(nx);
        res = T_RES(0.0, 0.0);

        for(size_t i = 0; i < nx; i++)
        {
            res += psi[i] * exp( - 2.0 * M_PI * m * iu * double(i) / nx1);

        }

        res *= 1 / nx1;
    };

} // MATH
