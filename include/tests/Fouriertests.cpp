#include <iostream>
#include <complex>
#include <vector>

#include "math/FourierCoeff.hpp"

#define PI 3.141592653589793

#define BOOST_TEST_MODULE "FourierTest"

#include "boost/test/included/unit_test.hpp"





BOOST_AUTO_TEST_CASE(FouriertCoeff1D)
{
    std::cout << "Running 1D CoefficientTest!" << std::endl;
    double alpha = 1.0;
    int nx = 1000;
    testfunctions::Gaussian g();
    double x0 = 0.0;
    double x1 = PI/2.0;

    double h = (x1-x0)/(double)nx;
    std::complex<double> res = {0.0,0.0};
    auto psit = [](std::complex<double> x) -> std::complex<double>
    {
       return std::complex<double>(1.0,0);
    };

    math::fourier_1D_serial(alpha, nx, psit, h, x0, res);
    std::cout << res.real() << std::endl;
    std::cout << res.imag() << std::endl;
    BOOST_REQUIRE_CLOSE(res.real(), 1.0, 1e-2);
    BOOST_REQUIRE_CLOSE(res.imag(), 1.0, 1e-2);


}
