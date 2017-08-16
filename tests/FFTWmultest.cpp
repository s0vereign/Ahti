#include <complex>
#include <fftw3.h>
#include <iostream>

#include "gtest/gtest.h"

#include "../include/math/CMultFFTW.hpp"

TEST(FFTWtests, FFTWCDmulTest)
{
    using std::complex;

    complex<double> a(8.0,2.0);
    complex<double> c_std(2.0,2.0);
    complex<double> b(2.0,2.0);
    complex<double> d_std(13.0,13.0);
    fftw_complex c = {2.0, 2.0};
    fftw_complex d = {13.0,13.0};

    auto real = math::fftw_mult_real(c[0],c[1], a);
    auto imag = math::fftw_mult_imag(d[0],d[1], b);


    ASSERT_EQ((a*c_std).real(), real);
    ASSERT_EQ((b*d_std).imag(), imag);

    complex<double> a1(123,141.2);
    fftw_complex c1 = {12, 213.2};
    complex<double> b2(12, 213.2);

    b2 *= a1;
    auto imag1 = math::fftw_mult_imag(c1[0],c1[1],a1);
    auto real1 = math::fftw_mult_real(c1[0],c1[1],a1);

    ASSERT_EQ(b2.imag(), imag1);
    ASSERT_EQ(b2.real(), real1);


}

TEST(FFTWtests, FFTWOpTest)
{
    using std::complex;
    using namespace math;
    complex<double> a(5.0,5.0);
    complex<double> b(3.1,8.2);

    fftw_complex c{5.0,5.0};

    a *= b;
    c *= b;

    ASSERT_EQ(a.real(), c[0]);
    ASSERT_EQ(a.imag(), c[1]);
}
