#pragma once

#include <vector>
#include <complex>
#include <algorithm>
#include <fftw3.h>
#include <stdlib.h>
#include <array>
#include <memory>



#include "../grid/Grid.hpp"
#include "../grid/LocalGrid.hpp"
#include "StaticCalcs2D.hpp"
#include "../containers/Array2D.hpp"
#include "../output/SaveGrid2D.hpp"

#define DEBUG_ENABLED
#include "../debug/DebugDef.h"

namespace Worker
{
    using std::complex;
    using containers::Array2D;

    template<typename T_DIST, typename T_POT>
    void start_serial_worker(Grid::Grid<2> g, T_DIST p0, T_POT V)
    {

        Array2D<fftw_complex> psi(g.nx, g.ny);
        Array2D<fftw_complex> psi_ks(g.nx, g.ny);

        fftw_plan ft = fftw_plan_dft_2d(g.nx, g.ny, psi.get_raw_ptr(), psi_ks.get_raw_ptr(), FFTW_FORWARD, FFTW_MEASURE);
        fftw_plan ift = fftw_plan_dft_2d(g.nx, g.ny, psi_ks.get_raw_ptr(), psi.get_raw_ptr(), FFTW_BACKWARD, FFTW_MEASURE);
        DEBUG("Initialing testfunction...");
        init_psi(psi, p0, g);

        const int nt = g.nt;

        fftw_execute(ft);

        IO::save_grid_2d(psi,g,"test.h5");


    };


}