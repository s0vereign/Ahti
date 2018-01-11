#pragma once

#include<boost/math/constants/constants.hpp>
#include<complex>
#include<cmath>

namespace math
{
    double theta(const std::complex<double>& x, const std::complex<double>& y, const std::complex<double>& z)
    {
        double r = sqrt(x.real()*x.real()+y.real()*y.real()+z.real()+z.real());
        double t = acos(z.real()/r);
        return t;
    }

    double phi(const std::complex<double>& x_, const std::complex<double>& y_, const std::complex<double>& z_)
    {
        double x = x_.real();
        double y = y_.real();
        double z = z_.real();
        if(x > 0.0)
        {
            return atan(y/x);
        }

        if(x == 0.0)
        {
            return y / fabs(y) * boost::math::constants::pi<double>() / 2.0;
        }

        if(x < 0 && y >= 0 )
        {
            return atan(y/x) + boost::math::constants::pi<double>();
        }

        if(x < 0 && y < 0)
        {
            return atan(y/x) - boost::math::constants::pi<double>();
        }
    }
}