#pragma once

#include <boost/math/constants/constants.hpp>
#include <complex>
#include <cmath>
#include <debug/DebugDef.h>
#include <vector>


#define DEBUG_ENABLED
namespace math
{
    double theta(const std::complex<double>& x, const std::complex<double>& y, const std::complex<double>& z)
    {
        double r = sqrt(x.real()*x.real()+y.real()*y.real()+z.real()*z.real());

        double t = acos(z.real()/r);
        return t;
    }

    double phi(const std::complex<double>& x_, const std::complex<double>& y_, const std::complex<double>& z_)
    {
        double x = x_.real();
        double y = y_.real();
        double z = z_.real();
        double pi = boost::math::constants::pi<double>();
        double res = 0;
        if(x > 0.0)
        {
            res = atan(y/x);
            if(res < 0.0)
            {
                res += 2*pi;
            }

            return res;
        }

        if(x == 0.0)
        {
            res = y / fabs(y) * boost::math::constants::pi<double>() / 2.0;
            if(res < 0.0)
            {
                res += 2*pi;
            }

            return res;
        }

        if(x < 0 && y >= 0 )
        {
            res = atan(y/x) + boost::math::constants::pi<double>();
            if(res < 0.0)
            {
                res += 2*pi;
            }

            return res;
        }

        if(x < 0 && y < 0)
        {
            res = atan(y/x) - boost::math::constants::pi<double>();
            if(res < 0.0)
            {
                res += 2*pi;
            }

            return res;
        }
    }

    std::vector<double> sp_to_cart(double r, double phi, double theta)
    {
        std::vector<double> res(3);
        res[0] = r * sin(theta) * cos(phi);
        res[1] = r * sin(theta) * sin(phi);
        res[2] = r * cos(theta);

        return res;
    }
}