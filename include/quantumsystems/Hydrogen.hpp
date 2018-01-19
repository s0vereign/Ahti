#pragma once

#include <complex>
#include <boost/math/special_functions/laguerre.hpp>
#include <boost/math/special_functions/spherical_harmonic.hpp>
#include <boost/math/constants/constants.hpp>

#include "../math/Factorial.hpp"
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
            Y_lm(int l_, int m_) : l(l_),m(m_) {};
            const std::complex<double>
                    operator()( int l1, int m1,
                                const std::complex<double>& x,
                                const std::complex<double>& y,
                                const std::complex<double>& z);
            const std::complex<double>
                    operator()(const std::complex<double>& x,
                               const std::complex<double>& y,
                               const std::complex<double>& z);
        private:
            double
            NLM(int l, int m);
            int m,l;
            const double N = NLM(l,m);

        };

        struct R_nl
        {
        public:
            R_nl(int n_, int l_): n(n_), l(l_){};
            const std::complex<double> operator()(  int n, int l,
                                                    const std::complex<double>& x_,
                                                    const std::complex<double>& y_,
                                                    const std::complex<double>& z_);

            const std::complex<double> operator()(  const std::complex<double>& x_,
                                                    const std::complex<double>& y_,
                                                    const std::complex<double>& z_);

        private:
            const int n;
            const int l;
        };

        struct Psi_nlm
        {
            public:

            std::complex<double> operator()(const std::complex<double>& x,
                                            const std::complex<double>& y,
                                            const std::complex<double>& z);
            Psi_nlm(int n_, int l_, int m_);
        private:
            R_nl rad;
            Y_lm ang;
            int n,l,m;
        };


    }
}