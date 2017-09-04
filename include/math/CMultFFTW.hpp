#pragma once

#include <complex>
#include <iostream>

namespace math
{

    inline double fftw_mult_real(double a, double b, std::complex<double> z)
    {
        // Returns the real part of a complex multiplication
        // of an std::complex and two doubles of a fftw_complex
        auto x = z.real();
        auto y = z.imag();

        return (a*x - b*y);
    }

    inline double fftw_mult_imag(double a, double b, std::complex<double> z)
    {
        // Returns the imaginary part of a complex multiplication
        // of an std::complex and two doubles of a fftw_complex
        auto x = z.real();
        auto y = z.imag();
        std::cout << y*a + b*x << std::endl;
        return (y*a + b*x);
    }

    inline void fftw_mult(fftw_complex& c, std::complex<double> z)
    {
        double x(z.real()),y(z.imag()),a(c[0]),b(c[1]);
        c[0] = a * x - b * y;
        c[1] = y * a + b * x;

    }

    inline void operator*=(fftw_complex& c, std::complex<double> z)
    {
        math::fftw_mult(c, z);
    }

}

