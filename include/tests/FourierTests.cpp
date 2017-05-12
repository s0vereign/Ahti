
#define BOOST_TEST_MODULE "DynTest"
#include "boost/test/included/unit_test.hpp"

#include <complex>
#include <vector>

#include "math/FourierCoeff.hpp"

using namespace std;

BOOST_AUTO_TEST_CASE(Fourier)
{
    double alpha = 0.0;
    int nx = 5;
    double h = 1.0;
    complex<double> res(0.0,0.0);
    auto psi = [](complex<double> x) { return complex<double>(1.0,0);};
    
    math::fourier_1D_serial(alpha, nx, psi, h, 0.0, res);
    cout << res.real() << endl;
    BOOST_REQUIRE_CLOSE(res.real(), 5.0, 0.01);
}

