#include "../../include/quantumsystems/Hydrogen.hpp"
#include <cmath>

const std::complex<double> qsystems::hydrogen::Hplus_Pot::operator(const std::complex<double>& x,
                                                                   const std::complex<double>& y,
                                                                   const std::complex<double>& z)
{
    return - 1 / sqrt(x.real()*x.real() + y.real() * y.real() + z.real() * z.real());
}