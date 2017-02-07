#pragma once

#include <complex>
#include "potentials/HarmOsc1D.hpp"

namespace math {

    template<typename T_REAL, typename TEST_DIST>
    void fourier_1D_serial
    (
        T_REAL x0, // starting point
        const T_REAL h,
        size_t nx, // number of nodes
        T_REAL band, // band
        std::complex<T_REAL>& res // result,
    )
    {

        /*
        * This function executes a serial 1D
        * Trapezoidal rule integration on an std
        * vector to write it in a result vector
        * for a band b
        **/

        TEST_DIST psi();
        T_REAL x = x0;
        std::complex<T_REAL> j(0,1);
        for(size_t i = 0; i < nx-1; ++i)
        {

            res += std::exp(i*band*j*x) * psi(x) + std::exp(i*band*j*(x+h)) * psi(x+h);
            x += h;

        }
        res *= h/2;
    }

} // MATH
