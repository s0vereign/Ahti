#pragma once

#include <complex>
#include <boost/math/special_functions/laguerre.hpp>
#include <boost/math/special_functions/spherical_harmonic.hpp>
#include <boost/math/constants/constants.hpp>



namespace qsystems
{
    namespace hydrogen
    {
        /*
         * Definition of the Hydrogen Potential.
         * The potential is a simple functor which simply returns the Coulomb
         * potential
         */
        class Hplus_Pot
        {
        public:
            const std::complex<double> operator()(const std::complex<double> &x,
                                                  const std::complex<double> &y,
                                                  const std::complex<double> &z,
                                                  double t);
            Hplus_Pot() = default;

        };


        /*
         * Definition of the spehrical harmonics which
         * correspond to the angular factors in the solution
         * for the hydrogen solution.
         */
        class Y_lm
        {
        public:
            Y_lm(int l_, int m_) : l(l_),m(m_) {};


            const std::complex<double>
                    operator()(const std::complex<double>& x,
                               const std::complex<double>& y,
                               const std::complex<double>& z);
        private:
            int l,m;

        };

        /*
         * Radial wavefunction functor
         */
        class R_nl
        {
        public:
            R_nl(int n_, int l_): n(n_), l(l_){};

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