#include <boost/math/special_functions/laguerre.hpp>
#include <cmath>
#include "../../include/quantumsystems/Hydrogen.hpp"
#include "../../include/math/CartToSpherical.hpp"
#include "../../include/math/Factorial.hpp"

const std::complex<double>
qsystems::hydrogen::Hplus_Pot::operator()(const std::complex<double> &x, const std::complex<double> &y,
                                          const std::complex<double> &z, double t)
{
    return - 1.0 / sqrt(x.real()*x.real() + y.real() * y.real() + z.real() * z.real());
};



const std::complex<double> qsystems::hydrogen::Y_lm::operator()(const std::complex<double> &x,
                                                                const std::complex<double> &y,
                                                                const std::complex<double> &z)
{
    double theta;
    double phi;

    theta = math::theta(x, y, z);
    phi = math::phi(x, y, z);

    return boost::math::spherical_harmonic(l, m, theta, phi);
}

qsystems::hydrogen::Psi_nlm::Psi_nlm(int n_, int l_, int m_) : n(n_), l(l_), m(m_), rad(n_, l_), ang(l_, m_) {};

const std::complex<double> qsystems::hydrogen::R_nl::operator()(const std::complex<double> &x_,
                                                                const std::complex<double> &y_,
                                                                const std::complex<double> &z_)
{
    double x = x_.real();
    double y = y_.real();
    double z = z_.real();


    double r = sqrt(x*x+y*y+z*z);
    double pref = std::sqrt(std::pow(2.0/n,3.0)* math::fac(n - l - 1)/(2 * n * math::fac(n + l)));
    double roh = 2.0*r/n;
    double L = boost::math::laguerre(unsigned(n-l-1), unsigned(2*l+1), roh);
    return pref*std::exp(-roh/2.0)*pow(roh,l)*L;

}

std::complex<double> qsystems::hydrogen::Psi_nlm::operator()(const std::complex<double> &x,
                                                             const std::complex<double> &y,
                                                             const std::complex<double> &z)
{
    auto  a = rad(x,y,z);
    a *= ang(x,y,z);
    return  a;
}