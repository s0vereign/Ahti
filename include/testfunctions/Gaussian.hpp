#pragma once

#include <complex>

namespace testfunctions {

    struct Gaussian
    {
        std::complex<double> operator()(std::complex<double> x)
        {
            std::complex<double> k(std::exp(-x*x));
            return k;
        }
    };

}// testfunctions