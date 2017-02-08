#pragma once

#include <complex>
#include "potentials/HarmOsc1D.hpp"
#include "testfunctions/Gaussian.hpp"
#include "math/COperators.hpp"
namespace math {

    template<typename FUNC_PSI>
    void fourier_1D_serial( double alpha,
                            int nx,
                            FUNC_PSI& psi,
                            double h_,
                            double x0,
                            std::complex<double>& res)
    {
        
        std::complex<double> x(0,0);
        std::complex<double> h(h_,0);
        std::complex<double> j(0,1.0);
        std::complex<double> ic(0,0);
        for(int i = 1; i < nx; i++)
        {

            x += h * (double) i;
            std::complex<double> arg1 = j*alpha*i*x;
            std::complex<double> arg2 = j*alpha*i*(x+h);
            std::complex<double> arg3 = x + h;
            res = res + psi(x) * std::exp(arg1);
            res = res + psi(arg3) * std::exp(arg2);

        }
        res *= h/ (double)2;
    }

} // MATH
