#include "../../include/quantumsystems/dist-harm-osc.hpp"

qsystems::distosc::VD_1D::VD_1D(double w_, double a) : w(w_), a(a) {};

inline auto qsystems::distosc::VD_1D::operator()(const std::complex<double> &x, const double &t)
-> std::complex<double>
{
    return 0.5*x*x + a * cos(w * t);
}

inline auto qsystems::distosc::VD_2D::operator()(const std::complex<double> &x,
                                          const std::complex<double> &y,
                                          const double &t)
-> std::complex<double>
{
    return 0.5*(x*x + y*y) + a1 * cos(w1*t) + a2 * cos(w2 * t);
}

qsystems::distosc::VD_2D::VD_2D(double w1, double w2, double a1, double a2) : w1(w1), w2(w2), a1(a1), a2(a2) {};

qsystems::distosc::VD_3D::VD_3D(double w1, double w2, double w3, double a1, double a2, double a3)
    : w1(w1), w2(w2), w3(w3), a1(a1), a2(a2), a3(a3) {}

inline auto qsystems::distosc::VD_3D::operator()(const std::complex<double> &x,
                                          const std::complex<double> &y,
                                          const std::complex<double> &z,
                                          const double &t)
-> std::complex<double>
{
    return 0.5 * (x*x + y*y + z*z) + a1 * cos(w1 * t) + a2 * cos(w2 * t) + a3 * cos(w3 *t);
}

qsystems::distosc::VD_lin_1D::VD_lin_1D(double w1, double a1, double l1) : w1(w1), a1(a1), l1(l1) {}

auto qsystems::distosc::VD_lin_1D::operator()(const std::complex<double> &x, const double &t)
-> std::complex<double>
{
    return 0.5*x*x - x * l1 * cos(w1 * t);
}

qsystems::distosc::VD_lin_2D::VD_lin_2D(double w1, double a1, double l1, double w2, double a2, double l2)
    : w1(w1), a1(a1), l1(l1), w2(w2), a2(a2), l2(l2) {}

auto qsystems::distosc::VD_lin_2D::operator()(const std::complex<double> &x,
                                              const std::complex<double> &y,
                                              const double &t)
-> std::complex<double>
{
    return 0.5 * (x*x + y * y) - l1 * x * cos(w1 * t) - l2 * y * cos(w2 * t);
}

qsystems::distosc::VD_lin_3D::VD_lin_3D(double w1, double l1, double w2, double l2, double w3, double l3)
    : w1(w1), l1(l1), w2(w2), l2(l2), w3(w3), l3(l3) {}

inline auto qsystems::distosc::VD_lin_3D::operator()(const std::complex<double> &x,
                                                     const std::complex<double> &y,
                                                     const std::complex<double> &z,
                                                     const double &t)
-> std::complex<double>
{
    return 0.5 * (x * x + y * y + z * z) - l1 * x * cos(w1 * t) - l2 * y * cos(w2 * t) - l3 * z * cos(w3 * t);
}
