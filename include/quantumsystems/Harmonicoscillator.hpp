#pragma once

#include <complex>
#include <cmath>

namespace qsystems
{
    namespace harmosc
    {
        struct Psi0
        {
            private:
            const double inv_fthsqrt_pi = 0.7511255444649425;

            public:
            const double w;
            const double sqrt_w;
            Psi0(double w) : w(w), sqrt_w(sqrt(w))
            {
            };

            const std::complex<double>
            operator()(const std::complex<double> &x);
        };

        struct Psi1
        {
            private:
            Psi0 p0;

            const double inv_sqrt_two = 0.70710678118654757;

            public:
            Psi1(double w) : p0(w)  {};

            const std::complex<double>
            operator()(const std::complex<double> &x);
        };

        struct Psi2
        {
            private:
            Psi0 p0;
            const double inv_sqrt_eight = 0.35355339059327379;

            public:
            Psi2() = default;
            const std::complex<double>
            operator()(const std::complex<double> &x);
        };

        struct V_1D
        {
            V_1D() = default;
            const std::complex<double>
            operator()(const std::complex<double> &x, const double &t);
        };

        struct V_2D
        {
            V_2D() = default;
            const std::complex<double>
            operator()(const std::complex<double> &x, const std::complex<double> &y, const double &t);
        };

        struct V_3D
        {
            V_3D() = default;
            const std::complex<double>
            operator()(const std::complex<double> &x,
                                   const std::complex<double> &y,
                                   const std::complex<double> &z,
                                   const double &t);
        };

    } // harmosc
} // qsystems
