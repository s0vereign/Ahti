#include <iostream>
#include <complex>
#include <vector>

#include "math/FourierCoeff.hpp"

#define PI 3.141592653589793

#define BOOST_TEST_MODULE "FourierTest"

#include "boost/test/included/unit_test.hpp"





BOOST_AUTO_TEST_CASE(FouriertCoeff1D)
{
    using std::cout; 
    using std::endl;
    using std::complex;
    using std::exp;
    using math::fourier_1D_serial;
    cout << "Running 1D CoefficientTest!" << endl;
    
    auto psi = [](const complex<double>& x) -> complex<double>
                {
                    return complex<double> (1,0);
                };
    
    const double alpha = 1.0;
    const double h = 1.0;
    const int nx = 3.0;
    double nx1 = static_cast<double>(nx);

    complex<double> res_analytical(0,0);
    complex<double> res_test(0,0);
    complex<double> j(0,1);
    res_analytical = exp(0.0) + exp(-2*M_PI*1*j*h/ nx1) + exp(-2*M_PI*2*j*h/nx1);
    fourier_1D_serial(alpha,nx, psi, h, 0, res_test);

    BOOST_REQUIRE_CLOSE(res_test.real(), res_analytical.real(), 1e-2);
    BOOST_REQUIRE_CLOSE(res_test.imag(), res_analytical.imag(), 1e-2);

}
