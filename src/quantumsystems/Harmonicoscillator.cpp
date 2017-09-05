#include "../../include/quantumsystems/Harmonicoscillator.hpp"

const std::complex<double> qsystems::harmosc::Psi0::operator()(const std::complex<double> &x)
{
    return std::complex<double>(inv_fthsqrt_pi * std::exp(- x * x / 2.0));
}

const std::complex<double>  qsystems::harmosc::Psi1::operator()(const std::complex<double> &x)
{
    return std::complex<double>(p0(x) * inv_sqrt_two * (2.0 * x));
}

const std::complex<double>  qsystems::harmosc::Psi2::operator()(const std::complex<double> &x)
{
    return std::complex<double>(p0(x) * inv_sqrt_eight * (4.0 * x * x - 2.0));
}

const std::complex<double>  qsystems::harmosc::V_1D::operator()(const std::complex<double> &x)
{

    return std::complex<double>(0.5 * x.real() * x.real());
}

const std::complex<double>  qsystems::harmosc::V_2D::operator()(const std::complex<double> &x,
                                                                 const std::complex<double> &y)
{
    return std::complex<double>(0.5 * (x*x + y*y));
}

const std::complex<double>  qsystems::harmosc::V_3D::operator()(const std::complex<double> &x,
                                                                 const std::complex<double> &y,
                                                                 const std::complex<double> &z)
{
    return std::complex<double>(0.5 * (x*x + y*y + z*z));
}