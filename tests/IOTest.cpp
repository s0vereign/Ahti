#include <vector>

#include "../include/containers/Array2D.hpp"
#include "../include/output/SaveGrid2D.hpp"

#include "gtest/gtest.h"

TEST(IOTest, CastingTest)
{
    int nx = 2;
    int ny = 2;

    containers::Array2D<fftw_complex > a(nx,ny);
    containers::Array2D<double> b(nx,ny);
    containers::Array2D<double> c(nx,ny);

    for(int i = 0; i < nx; i ++)
    {
        for(int j = 0; j < ny; j++)
        {
            a.set_real(i+j, i, j);
            a.set_imag(-i-j, i, j);
        }
    }

    IO::cast_fftw_to_double(a, b, c);

    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            ASSERT_EQ(b.get(i, j), i + j);
            ASSERT_EQ(c.get(i,j), -i-j);
        }
    }
}