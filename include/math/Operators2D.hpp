#pragma once

#include <complex>
#include <memory>
#include <omp.h>
#include <fftw3.h>


#include "grid/CGrid.hpp"
#include "CMultFFTW.hpp"
namespace math
{
    // Free propagation function
    template<typename T_DATA>
    struct FreePropFS
    {
        const double dt;
        std::complex<double> iu = {0.0,1.0};
        FreePropFS(double dt_) : dt(dt_){};


        // Follows the time evolution scheme in Bauke et al.
        void operator()(T_DATA& data, double px, double py)
        {
            data *= std::exp(-iu * dt / 2.0 * (px*px + py*py));
        }
    };

    // Application of the free propagation function in
    template<typename T_CONT>
    void apply_2D_TEFS_op(T_CONT& data, int step, Grid::CGrid<2> g)
    {
        using std::complex;

        complex<double> iu(0.0,1.0);

        const int nx = g.nx;
        const int ny = g.ny;
        const double dt = g.dt;
        //decltype(T_CONT::type) T_DATA;

        const double dpx = 2*M_PI/(g.x1 - g.x0);
        const double dpy = 2*M_PI/(g.y1 - g.y0);

        double px = 0;
        double py = 0;

        const double px_offset = nx / 2 * dpx;
        const double py_offset = ny / 2 * dpy;




        /*
         * Iterate of the first half of the CGrid
         * thus adding the offset to the momentum
         * space values.
         */
#pragma omp parallel
        {
#pragma omp for
        for(int i = 0; i < nx; i++)
        {
            for(int j = 0; j < ny; j++)
            {
                if(i < nx/2)
                {
                    px = i * dpx;
                }
                else
                {
                    px = (i-nx/2) * dpx - px_offset;
                }

                if(j < ny/2)
                {
                    py = j*dpy;
                }
                else
                {
                    py = (j-ny/2) * dpy - py_offset;
                }
                data.mult_data(i,j,std::exp(-iu * dt/2.0 * (px*px + py*py)));

            }
        }

        }; // OMP PARALLEL

    }

    template<typename POT>
    inline
    auto
    V_int(const double& x, const double& y, POT& V,const double& t, const double& dt)
    -> std::complex<double>
    {
        return dt * 0.5 * (V(x,y,t) + V(x,y,t+dt));
    }

    template<typename T_CONT, typename POT>
    void apply_spatial_operator(T_CONT &data, Grid::CGrid<2> g, POT V, const double &t)
    {
        using std::complex;

        complex<double> iu(0.0,1.0);



        const double dx = g.dx;
        const double dy = g.dy;
        const double dt = g.dt;

#pragma omp parallel
        {
            int id = omp_get_thread_num();
            double x = g.x0;
            double y = g.y0;

#pragma omp for
            for (int i = 0; i < g.nx; i++)
            {
                x = i * dx + g.x0;
                for (int j = 0; j < g.ny; j++)
                {
                    data.mult_data(i, j, std::exp(-iu * 0.5 * V_int(x, y, V, t, dt)));
                    y += dy;
                }
                y = g.y0;

            }
        }; // OMP PARALLEL
    };
}