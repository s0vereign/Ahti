#pragma once

#include <complex>
#include <cmath>

namespace qsystems
{
    namespace distosc
    {
        class VD_1D
        {
            private:
            double w;
            double a;

            public:
            VD_1D() = default;
            VD_1D(double w_, double a);
            auto operator()(const std::complex<double> &x, const double &t) -> std::complex<double>;
        };

        class VD_2D
        {
            private:
            double w1,w2;
            double a1, a2;

            public:
            VD_2D(double w1, double w2, double a1, double a2);
            auto operator()(const std::complex<double> &x,
                            const std::complex<double> &y,
                            const double &t) -> std::complex<double>;
        };

        class VD_3D
        {
            private:
            double w1,w2,w3;
            double a1,a2,a3;

            public:
            VD_3D(double w1, double w2, double w3, double a1, double a2, double a3);
            auto operator()(const std::complex<double> &x,
                                   const std::complex<double> &y,
                                   const std::complex<double> &z,
                                   const double &t)
                -> std::complex<double>;
        };

        class VD_lin_1D
        {
            private:
            double w1 , a1, l1;

            public:
            VD_lin_1D(double w1, double a1, double l1);
            auto operator()(const std::complex<double>& x,
                                   const double& t)
            -> std::complex<double>;
        };

        class VD_lin_2D
        {
            private:
            double w1, a1, l1;
            double w2, a2, l2;

            public:
            VD_lin_2D(double w1, double a1, double l1, double w2, double a2, double l2);
            auto operator()(const std::complex<double> &x,
                                   const std::complex<double> &y,
                                   const double &t)
            -> std::complex<double>;

        };

        class VD_lin_3D
        {
            private:
            double w1, l1;
            double w2, l2;
            double w3, l3;

            public:
            VD_lin_3D(double w1, double l1, double w2, double l2, double w3, double l3);
            auto operator()(const std::complex<double> &x,
                                   const std::complex<double> &y,
                                   const std::complex<double> &z,
                                   const double &t)
            -> std::complex<double>;
        };
    } // distosc
} // qsystems