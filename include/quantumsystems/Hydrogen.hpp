#pragma once

#include <complex>
#include <boost/math/special_functions/laguerre.hpp>
#include <boost/math/special_functions/spherical_harmonic.hpp>
#include <boost/math/constants/constants.hpp>

namespace qsystems
{
    namespace hydrogen
    {
        class Hplus_Pot
        {
        public:
            const std::complex<double> operator()(const std::complex<double>& x,
                                                const std::complex<double>& y,
                                                const std::complex<double>& z);
            Hplus_Pot() = default;

        };

        struct Y_lm
        {
        public:
            Y_lm() = default;
            const std::complex<double>
                    operator()( int l, int m,
                                const std::complex<double>& x,
                                const std::complex<double>& y,
                                const std::complex<double>& z);
        };

        struct R_nl
        {
        public:
            R_nl() = default;
            const std::complex<double> operator()( int n, int l,
                                                const std::complex<double>& x_,
                                                const std::complex<double>& y_,
                                                const std::complex<double>& z_);
        };

        struct Psi_nlm
        {
        public:

            std::complex<double> operator()(  int n, int l, int m,
                                            const std::complex<double>& x,
                                            const std::complex<double>& y,
                                            const std::complex<double>& z);
        };


    }
}