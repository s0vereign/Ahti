#pragma once

#include "../grid/Grid.hpp"
#include "../containers/Array3D.hpp"

namespace Worker
{
    template<typename DIST>
    void init_psi(containers::Array3D<fftw_complex> &psi,
                      Grid::Grid<3> g,
                      DIST f,
                      containers::Array3D<fftw_complex> &psi_ks)
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

        for(int i = 0; i < g.nx; i++)
        {
            for(int j = 0; j < g.ny; j++)
            {
                for(int k = 0; k < g.nz; k++)
                {
                    psi.set_compl(i,j,k, f(x,y,z));
                    psi_ks.set_compl(i,j,k,0.0);
                    z +=  dx;
                }
                z = g.z0;
                y += dy;
            }
            y  = g.y0;
            x += dy;
        }
    }
}