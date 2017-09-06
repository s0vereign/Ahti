#pragma once

#include <complex>
#include <cmath>

namespace qsystems
{
    namespace distosc
    {
        class VD_1D
        {
            protected:
            double w;
            double a;

            public:
            VD_1D() = default;
            VD_1D(double w_, double a);
            inline auto operator()(const std::complex<double> &x, const double &t) -> std::complex<double>;
        };

        class VD_2D
        {
            protected:
            double w1,w2;
            double a1, a2;

            public:
            VD_2D(double w1, double w2, double a1, double a2);
            inline auto operator()(const std::complex<double> &x,
                                   const std::complex<double> &y,
                                   const double &t) -> std::complex<double>;
        };

        class VD_3D
        {
            protected:
            double w1,w2,w3;
            double a1,a2,a3;

            public:
            VD_3D(double w1, double w2, double w3, double a1, double a2, double a3);
            inline auto operator()(const std::complex<double> &x,
                                   const std::complex<double> &y,
                                   const std::complex<double> &z,
                                   const double &t)
                -> std::complex<double>;
        };
    } // distosc
} // qsystems