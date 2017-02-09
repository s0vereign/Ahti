#pragma once
#include <complex>

namespace math{

    std::complex<double> operator*(std::complex<double> p1, int p2)
    {
        std::complex<double> a(p1.real()*(double)p2, p1.imag()*(double)p2);
        return a;
    }
}
