#include <complex>
#include "gtest/gtest.h"
#include <fftw3.h>
#include <math/Operators2D.hpp>

#include "../include/containers/Array2D.hpp"
#include "../include/math/CMultFFTW.hpp"
#include "../include/grid/Grid.hpp"

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


TEST(OperatorTests, ApplyOperatorFourierSpaceTest)
{
    using std::complex;
    using math::apply_2D_TEFS_op;
    using containers::Array2D;

    int nx(4), ny(4);

    Array2D<fftw_complex> a(nx,ny);

    double px = 0;
    double py = 0;
    double dpx = 2*M_PI/1;
    double dpy = dpx;
    double px_off = dpx * nx/2.0;
    double py_off = dpy * ny/2.0;

    Array2D<complex<double>> tst(nx,ny);
    complex<double>* ref;

    std::complex<double> iu(0.0,1.0);

    Grid::Grid<2> g(0.0, 1.0, nx, 0.0, 1.0, ny, 0, 1.0, 1);


    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            a.set_imag(0,i,j);
            a.set_real(1.0,i,j);
            tst.set(complex<double>(1.0,0.0),i,j);
        }
    }





    // (0,0)
    px = px_off;
    py = -py_off;



    apply_2D_TEFS_op(a, 0, g);
    apply_2D_TEFS_op(tst, 0, g);


    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < nx; j++)
        {

            ASSERT_EQ(tst.get(i,j).real(), a.get_real(i,j));
            ASSERT_EQ(tst.get(i,j).imag(), a.get_imag(i,j));
        }
    }



}