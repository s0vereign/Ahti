#pragma once

#include <complex>

#include "grid/CGrid.hpp"


namespace math
{
    using std::complex;
    using std::exp;


    template<typename T>
    inline
    auto
    V_int(double x, double t, double dt, T V)
    ->complex<double>
    {
        return 0.5 * (V(x,t) + V(x, t+dt));
    }

    template<typename T_DATA, typename T_POT>
    void spatial_step(Grid::CGrid<1> g, T_DATA& psi_rs, T_POT V, double t)
    {
        double tau = g.dt;
        double x = g.x0;
        double dx = g.dx;

        complex<double> iu(0.0,1.0);
        complex<double> e(0.0,0.0);
        for(uint i = 0; i < g.nx; i++)
        {
            e = exp(-iu * tau/2.0 * V_int(x,t, tau, V));
            psi_rs.mult_data(i, e);
            x += dx;
        }
    };

    template<typename T_DATA>
    void fourier_step(Grid::CGrid<1> g, T_DATA& psi_ks)
    {
        double tau = g.dt;
        double dp = 2 * M_PI / (g.nx * g.dx);
        double p_off = g.nx / 2 * dp;
        double p = 0;
        complex<double> c(0,0);
        complex<double> iu(0.0,1.0);

        for(uint i = 0; i < g.nx;  i++)
        {
            if(i < g.nx/2)
            {
                p = i * dp;
            }

            else
            {
                p = (i - g.nx/2) * dp - p_off;

            }

            c = exp(-iu * p * p * 0.5 * tau);
            psi_ks.mult_data(i,c);
        }
    }

    template<typename T_DATA>
    void norm_ft(Grid::CGrid<1> g, T_DATA& psi)
    {
        complex<double> n(1.0/g.nx, 0);
        for(uint i = 0; i < g.nx; i++)
        {
            psi.mult_data(i, n);
        }
    }
}