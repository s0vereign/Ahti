#pragma once

#include <fftw3.h>
#include <complex>

#include "../containers/Array2D.hpp"
#include "../grid/Grid.hpp"
#include "../math/CMultFFTW.hpp"
#define DEBUG_ENABLED
#include "../debug/DebugDef.h"

namespace Worker
{

    template <typename T_CONT, typename  T_DIST>
    void init_psi(T_CONT& vals, T_DIST p, Grid::Grid<2> g)
    {
        double x = g.x0;
        double y = g.y0;
        const int nx = g.nx;
        const int ny = g.ny;
        const double dx = g.dx;
        const double dy = g.dy;

        for(int i = 0; i < nx; i++)
        {

            for(int j = 0; j < ny; j++)
            {
                std::complex<double> v = p(x,y);
                vals.set_real(v.real(),i,j);
                vals.set_imag(v.imag(),i,j);
                y += dy;

            }

            x += dx;
            y = g.y0;

        }
    };


    template <typename T_CONT, typename T_POT>
    void mult_phase(T_CONT& vals, T_POT V, Grid::Grid<2> g)
    {
        double x = g.x0;
        double y = g.y0;
        const int nx = g.nx;
        const int ny = g.ny;
        const double dx = g.dx;
        const double dy = g.dy;
        const double dt  = g.dt;
        std::complex<double> iu(0,1);

        double a;
        double b;

        for(int i = 0; i < nx; i++)
        {
            for(int j = 0; j < ny; j++)
            {
                std::complex<double> Vxy = std::exp(iu * V(x,y) * dt);
                a = math::fftw_mult_real(vals.get_real(i,j),vals.get_imag(i,j),Vxy);
                b = math::fftw_mult_real(vals.get_real(i,j),vals.get_imag(i,j),Vxy);
                vals.set_real(a,i,j);
                vals.set_imag(b,i,j);
                y += dy;
            }

            x += dx;
        }
    };

    template<typename T_ARR, typename T>
    void shuffle_2D_freq(T_ARR& vals, Grid::Grid<2> g)
    {
        for(int i = 0; i < g.nx; i++)
        {

        }
    }
}