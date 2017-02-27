#pragma once

#include <complex>
#include <math.h>
#include "testfunctors/Gaussian.hpp"
#include "math/COperators.hpp"
#define DEBUG_ENABLED
#include "debug/DebugDef.h"

namespace math {

    template<typename FUNC_PSI>
    void fourier_1D_serial( double alpha,
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
        complex<double> j(0,1);

        auto nx1 = static_cast<double>(nx);

        for(int i = 0; i < nx; i++)
        {   
            x = h*i;
            res += psi(x)*exp(-2*M_PI*alpha*j*x/nx1);
            
        }
    }

} // MATH
