#pragma once

#include <complex>

namespace math
{
    inline double fftw_mult_real(double a, double b, std::complex<double> z)
    {
        auto x = z.real();
        auto y = z.imag();

        return(a*x - b*y);
    }

    inline double fftw_mult_imag(double a, double b, std::complex<double> z)
    {
        auto x = z.real();
        auto y = z.imag();

        return(y*a + b*x);
    }
}