#include <complex>
#include "gtest/gtest.h"
#include <fftw3.h>
#include <math/Operators2D.hpp>

#include "../include/math/CMultFFTW.hpp"

TEST(OperatorTests, FourierSpaceFreeParticleTest)
{
    using std::complex;
    using math::FreePropFS;
    fftw_complex c = {1.0, 0.0};
    complex<double> a(1.0, 0.0);
    complex<double> iu(0.0,1.0);

    FreePropFS<fftw_complex> p(1.0);

    double px = M_PI;
    double py = 0;
    p(c,px,py);
    a *= std::exp(-iu * M_PI * M_PI / 2.0);
    ASSERT_EQ(a.real(),c[0]);
    ASSERT_EQ(a.imag(),c[1]);
}