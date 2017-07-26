#include <iostream>
#include <cassert>

#include "../include/containers/Array2D.hpp"
#include "gtest/gtest.h"


TEST(ContainerTest, Array2DGetSetTest)
{
    containers::Array2D<int> a(20,20);

    a.set(3,10,10);
    ASSERT_EQ(a.get(10,10),3);
}


TEST(Array2DComplex, FFTWGetSetTest)
{
    containers::Array2D<fftw_complex > ca(10,10);
    ca.set_imag(3.141,5,5);
    ca.set_real(1.336,5,5);

    ASSERT_EQ(ca.get_imag(5,5), 3.141);
    ASSERT_EQ(ca.get_real(5,5), 1.336);

}


