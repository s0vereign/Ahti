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
}
