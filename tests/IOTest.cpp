#include <vector>

#include "../include/containers/Array2D.hpp"
#include "../include/containers/Array3D.hpp"
#include "../include/output/SaveGrid2D.hpp"
#include  "../include/output/SaveGrid3D.hpp"
#include "../include/grid/Grid.hpp"

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


TEST(IOTest, Casting3DTest)
{
     int nx = 2;
     int ny = 2;
     int nz = 2;

    containers::Array3D<fftw_complex > a(nx,ny,nz);
    containers::Array3D<double> b(nx,ny,nz);
    containers::Array3D<double> c(nx,ny,nz);
    std::cout << std::endl;

    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            for(int k = 0; k < nz; k++)
            {
                fftw_complex complex1 = {i+j+k, i+k-j};
                a.set_compl(i,j,k, complex1);
            }
        }
    }

    Grid::Grid<3> g(0,0,0,0,0,0,nx,ny,nz,0,0,0);

    IO::cast_to_double(a, b, c, g);
    std::cout << (c.get(0,0,0)) << std::endl;
    std::cout << a.get_compl(0,0,0)[1] << std::endl;
    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            for(int k = 0; k < nz; k++)
            {

                ASSERT_EQ(b.get(i,j,k), i + k + j);
                ASSERT_EQ(c.get(i,j,k), i + k - j);
            }
        }
    }
}