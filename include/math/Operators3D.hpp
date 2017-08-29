#pragma once

#include <complex>

#include "../grid/Grid.hpp"

namespace math
{
    template<typename T_CONT, typename POT>
    void apply_spatial_op(T_CONT& data, POT V, Grid::Grid<3> g)
    {
        using std::complex;

        const double dx = g.dx;
        const double dy = g.dy;
        const double dz = g.dz;
        const double dt = g.dt;
        const complex<double> iu(0.0,-1.0);

        double x = g.x0;
        double y = g.y0;
        double z = g.z0;

        for(int i = 0; i < data.getNx(); i++)
        {
            for(int j = 0; j < data.getNy(); j++)
            {
                for(int k = 0; k < data.getNz(); k++)
                {
                    data.mul_by_compl(i,j,k, std::exp(-iu * dt/2 * V(x,y,z)));
                    z+=dz;
                }
                z = g.z0;
                y += dy;
            }

            y = g.y0;
            x += dx;
        }
    };

    template<typename T_CONT>
    void apply_FT_op(T_CONT& data, Grid::Grid<3> g)
    {
        using std::complex;

        const int nx = g.nx;
        const int ny = g.ny;
        const int nz = g.nz;
        const double dt = g.dt;

        const double dpx = 2 * M_PI/(g.x1 - g.x0);
        const double dpy = 2 * M_PI/(g.y1 - g.y0);
        const double dpz = 2 * M_PI/(g.z1 - g.z0);

        double px(0),py(0),pz(0);

        const double px_offset = nx / 2 * dpx;
        const double py_offset = ny / 2 * dpy;
        const double pz_offset = nz / 2 * dpz;

        complex<double> iu(0.0,1.0);

        for(int i = 0; i < nx; i++)
        {
            for(int j = 0; j < ny; j++)
            {
                for(int k = 0; k < nz; k++)
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
                        py = j * dpy;
                    }
                    else
                    {
                        py = (j - ny/2) * dpy - py_offset;
                    }

                    if(k < nz/2)
                    {
                        pz = k * dpz;
                    }
                    else
                    {
                        pz = (k - nz/2) * dpz - pz_offset;
                    }

                    data.mul_by_compl(i,j,k, std::exp(-iu * dt/2.0 * (px*px + py*py + pz*pz)));
                }
            }
        }
    }
}