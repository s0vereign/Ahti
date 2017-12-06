#include <iostream>

#include "../include/containers/Array1D.hpp"
#include "../include/containers/Array2D.hpp"
#include "../include/containers/Array3D.hpp"
#include "gtest/gtest.h"
#include <fftw3.h>



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


TEST(ContainerTest, Array3DGetSetTest)
{
    containers::Array3D<fftw_complex> tcont(10,10,10);
    fftw_complex a={1.0,2.0};
    tcont.set_compl(3,2,1,a);
    ASSERT_EQ(tcont.get_compl(3,2,1)[0],1.0);
    ASSERT_EQ(tcont.get_compl(3,2,1)[1],2.0);
}

TEST(ContainerTest, Array3DFFTWTest)
{
    containers::Array3D<fftw_complex> f(3,3,3);
    fftw_complex c = {1.0,2.0};

    containers::Array3D<fftw_complex> ft(3,3,3);
    for(auto* i : f.get_cont_ref())
    {
        i[0] = c[0];
        i[1] = c[1];
    }
    fftw_plan p = fftw_plan_dft_3d(3, 3, 3, f.get_raw_ptr(), ft.get_raw_ptr(), FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);

    fftw_plan p_inv = fftw_plan_dft_3d(3,3,3, ft.get_raw_ptr(), f.get_raw_ptr(), FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(p_inv);

    double N = 3*3*3;

    fftw_complex a = {1./N,0.0};
    f.norm(a);

    for(auto &i : f.get_cont_ref())
    {
        ASSERT_EQ(1.0, i[0]);
        ASSERT_EQ(2.0, i[1]);
    }
}

TEST(ContainerTest, Array1DFFTWTest)
{
    int NX = 10;
    containers::Array1D<fftw_complex> a(NX);

    std::complex<double> c(1.0,1.3);
    for(int i = 0; i < NX; i++)
    {
        a.set_stdc(i,c);
    }
    for(int i = 0; i< NX; i++)
    {
        ASSERT_EQ(1.0, a.get_real(i));
        ASSERT_EQ(1.3, a.get_imag(i));
    }
}