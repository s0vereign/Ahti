#pragma once

#include <vector>
#include <complex>
#include <iostream>
#include <fftw3.h>
#include <omp.h>

#define DEBUG_ENABLED
#include "../debug/DebugDef.h"

#include "grid/CGrid.hpp"
#include "StaticCalcs3D.hpp"
#include "../output/SaveGrid3D.hpp"
#include "../containers/Array3D.hpp"
#include "../math/Operators3D.hpp"


namespace solvers
{
    using std::complex;
    using containers::Array3D;

    template<typename T_DIST, typename T_POT>
    void solve(Grid::CGrid<3> g, T_DIST p0, T_POT V, int num_threads)
    {
        Array3D<fftw_complex > psi(g.nx, g.ny, g.nz);
        Array3D<fftw_complex > psi_ks(g.nx, g.ny, g.nz);
        fftw_init_threads();
        fftw_plan_with_nthreads(num_threads);
        std::cout << "Using FFTW with " << num_threads << " threads" << std::endl;
        fftw_complex* a = psi_ks.get_raw_ptr();
        fftw_complex* b = psi.get_raw_ptr();
        fftw_plan ft = fftw_plan_dft_3d(g.nx, g.ny, g.nz, b, a, FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_plan ift = fftw_plan_dft_3d(g.nx, g.ny, g.nz, a, b, FFTW_FORWARD, FFTW_ESTIMATE);

        std::cout << "Initializing Psi" << std::endl;

        init_psi(psi, g, p0, psi_ks);
        std::cout << "Finished!" << std::endl;
        const int nt = g.nt;

        double t = g.t0;
        const double dt = g.dt;

        IO::save_grid_3D(psi, g, "init.h5");
        fftw_complex norm = {1.0/(g.nx*g.ny*g.nz),0};
        for(int i = 0;  i < g.nt; i++)
        {
            std::cout << "Calculating timestep " << i << std::endl;
            math::apply_spatial_op(psi, V, g, t);

            fftw_execute(ft);
            math::apply_FT_op(psi_ks, g);
            fftw_execute(ift);

            psi.norm(norm);
            math::apply_spatial_op(psi, V, g, t);
            t += dt;
        }

        IO::save_grid_3D(psi, g, "test.h5");

        fftw_destroy_plan(ft);
        fftw_destroy_plan(ift);
        fftw_cleanup_threads();

    };
}