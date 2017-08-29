#pragma once

#include <vector>
#include <complex>
#include <iostream>
#include <fftw3.h>

#define DEBUG_ENABLED
#include "../debug/DebugDef.h"

#include "../grid/Grid.hpp"
#include "StaticCalcs3D.hpp"
#include "../output/SaveGrid3D.hpp"
#include "../containers/Array3D.hpp"
#include "../math/Operators3D.hpp"


namespace Worker
{
    using std::complex;
    using containers::Array3D;

    template<typename T_DIST, typename T_POT>
    void start_serial_worker(Grid::Grid<3> g, T_DIST p0, T_POT V)
    {
        Array3D<fftw_complex > psi(g.nx, g.ny, g.nz);
        Array3D<fftw_complex > psi_ks(g.nx, g.ny, g.nz);

        fftw_plan ft = fftw_plan_dft_3d(g.nx, g.ny, g.nz, psi.get_raw_ptr(), psi_ks.get_raw_ptr(), FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_plan ift = fftw_plan_dft_3d(g.ny, g.ny, g.nz, psi_ks.get_raw_ptr(), psi.get_raw_ptr(), FFTW_BACKWARD, FFTW_ESTIMATE);

        std::cout << "Initializing Psi" << std::endl;
        init_psi(psi, g, p0);
        std::cout << "Finished!" << std::endl;
        const int nt = g.nt;

        IO::save_grid_3D(psi, g, "test.h5");

        fftw_destroy_plan(ft);
        fftw_destroy_plan(ift);
    };
}