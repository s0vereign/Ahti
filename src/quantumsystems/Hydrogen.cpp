
#include <boost/math/special_functions/laguerre.hpp>
#include <cmath>
#include "../../include/quantumsystems/Hydrogen.hpp"
#include "../../include/math/Factorial.hpp"
#include "../../include/math/CartToSpherical.hpp"
const std::complex<double> qsystems::hydrogen::Hplus_Pot::operator()(const std::complex<double>& x,
                                                                   const std::complex<double>& y,
                                                                   const std::complex<double>& z)
{
    return - 1.0 / sqrt(x.real()*x.real() + y.real() * y.real() + z.real() * z.real());
};

const std::complex<double> qsystems::hydrogen::R_nl::operator()( int n, int l,
                                                                const std::complex<double>& x_,
                                                                const std::complex<double>& y_,
                                                                const std::complex<double>& z_)
{
    double x = x_.real();
    double y = y_.real();
    double z = z_.real();


    double r = sqrt(x*x+y*y+z*z);
    double pref = sqrt(pow(2/n,3)*math::fac(n-l-1)/(2 * n * math::fac(n +l)));
    double roh = 2.0*r/n;
    double L = boost::math::laguerre(unsigned(n-l-1), unsigned(2*l+1), roh);

    return pref*std::exp(-roh/2.0)*pow(roh,l)*L;

};