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

#define DEBUG_ENABLED
#include "../debug/DebugDef.h"

namespace Worker
{
    using std::complex;
    using namespace Grid;
    using containers::Array2D;

    template<typename T_DIST, typename T_POT>
    void start_serial_worker(Grid<2> g, T_DIST p0, T_POT V)
    {

        Array2D<complex<double>> psi(g.nx, g.ny);
        Array2D<complex<double>> psi_t(g.nx, g.ny);

        DEBUG("Initialing testfunction...");
        init_psi(psi, p0, g);



    };


}