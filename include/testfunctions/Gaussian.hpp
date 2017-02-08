#pragma once

#include <complex>


namespace testfunctions {

    struct Gaussian
    {

        Gaussian() {};

        std::complex<double> operator()(std::complex<double> x)
        {
            return std::exp(-x*x);
        }
    };

}// testfunctions