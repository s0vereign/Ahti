#pragma once

#include <complex>

namespace math
{
    inline double fftw_mult_real(double a, double b, std::complex<double> z)
    {
        // Returns the real part of a complex multiplication
        // of an std::complex and two doubles of a fftw_complex
        auto x = z.real();
        auto y = z.imag();

        return(a*x - b*y);
    }

    inline double fftw_mult_imag(double a, double b, std::complex<double> z)
    {
        // Returns the imaginary part of a complex multiplication
        // of an std::complex and two doubles of a fftw_complex
        auto x = z.real();
        auto y = z.imag();

        return(y*a + b*x);
    }
}