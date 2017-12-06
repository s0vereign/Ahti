#pragma once

#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
#include <fftw3.h>
#include <stdlib.h>
#include <array>

#include "hdf5.h"
#include "hdf5_hl.h"

#include "grid/CGrid.hpp"
#include "grid/LocalGrid.hpp"
#include "math/CoeffEv.hpp"
#include "math/FourierCoeff.hpp"
#include "math/ValsEv.hpp"
#include "math/ScalarProd.h"
#include "math/TimeFt.h"
#include "math/RecontructWV.hpp"
#include "solvers/StaticCalcs1D.hpp"
#include "output/SaveStep.hpp"
#include "../containers/Array1D.hpp"
#include "../math/Operators1D.hpp"


namespace solvers
{
    using std::complex;
    using std::vector;
    using Grid::LocalGrid;
    using Grid::CGrid;
    using containers::Array1D;

    template <typename DIST, typename POT>
    void solve(CGrid<1> g, DIST psi, POT V, int num_threads)
    {

        Array1D<fftw_complex > psi_rs(g.nx);
        Array1D<fftw_complex > psi_ks(g.nx);

        init_psi(g, psi, psi_rs);
        init_psi(g, [](double x){ return std::complex<double>(0,0);}, psi_ks);

        fftw_init_threads();

        fftw_plan_with_nthreads(num_threads);
        fftw_plan ft = fftw_plan_dft_1d(g.nx, psi_rs.get_raw_ptr(), psi_ks.get_raw_ptr(), FFTW_FORWARD, FFTW_ESTIMATE);

        fftw_plan ift = fftw_plan_dft_1d(g.nx, psi_ks.get_raw_ptr(), psi_rs.get_raw_ptr(), FFTW_BACKWARD, FFTW_ESTIMATE);

        IO::save_step(g, psi_rs, 0);
        double t = g.t0;
        double dt = g.dt;
        for(uint i = 0; i < g.nt; i++)
        {

            std::cout << "Currently in timestep " << i << std::endl;
            math::spatial_step(g, psi_rs, V, t);
            fftw_execute(ft);
            math::fourier_step(g, psi_ks);
            fftw_execute(ift);
            math::spatial_step(g, psi_rs, V, t);
            math::norm_ft(g, psi_rs);
            t += dt;

        }

        IO::save_step(g, psi_rs, 1);

    }
}
