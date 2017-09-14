#pragma once

#include <vector>
#include <complex>
#include <algorithm>
#include <cstdlib>
#include <array>
#include <memory>


#include <omp.h>
#include <fftw3.h>


#include "../grid/Grid.hpp"
#include "../grid/LocalGrid.hpp"
#include "StaticCalcs2D.hpp"
#include "../containers/Array2D.hpp"
#include "../output/SaveGrid2D.hpp"
#include "../math/Operators2D.hpp"
#include "../math/NormGrid.hpp"

#define DEBUG_ENABLED
#include "../debug/DebugDef.h"

namespace Worker
{
    using std::complex;
    using containers::Array2D;

    template<typename T_DIST, typename T_POT>
    void start_serial_worker(Grid::Grid<2> g, T_DIST p0, T_POT V)
    {

        fftw_init_threads();
        fftw_plan_with_nthreads(2);
        Array2D<fftw_complex> psi(g.nx, g.ny);
        Array2D<fftw_complex> psi_ks(g.nx, g.ny);

        fftw_plan ft = fftw_plan_dft_2d(g.nx, g.ny, psi.get_raw_ptr(), psi_ks.get_raw_ptr(), FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_plan ift = fftw_plan_dft_2d(g.nx, g.ny, psi_ks.get_raw_ptr(), psi.get_raw_ptr(), FFTW_BACKWARD, FFTW_ESTIMATE);
        DEBUG("Initializing testfunction...");

        init_psi(psi, p0, g);


        const int nt = g.nt;

        double t = g.t0;
        const double dt = g.dt;
        IO::save_grid_2d(psi, g, "init.h5");
        for(int i = 0; i < nt; i++)
        {
            std::cout << "Currently in step " << i << std::endl;
            math::apply_spatial_operator(psi, g, V, t);
            fftw_execute(ft);
            math::norm_grid(g, psi_ks);
            math::apply_2D_TEFS_op(psi_ks,i, g);
            fftw_execute(ift);
            math::apply_spatial_operator(psi, g, V, t);
            t += dt;
        }

        IO::save_grid_2d(psi, g, "first.h5");


        fftw_destroy_plan(ft);
        fftw_destroy_plan(ift);
        fftw_cleanup_threads();

    };


}