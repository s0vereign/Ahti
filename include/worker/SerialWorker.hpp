#pragma once

#include <vector>
#include <complex>
#include <algorithm>

#include "hdf5.h"
#include "hdf5_hl.h"


#include "grid/Grid.hpp"
#include "grid/LocalGrid.hpp"
#include "math/CoeffEv.hpp"
#include "math/FourierCoeff.hpp"
#include "math/ValsEv.hpp"
#include "worker/StaticCalcs.hpp"
#include "output/SaveStep.hpp"
#include "output/SaveCoeff.hpp"

namespace Worker 
{
    using std::complex;
    using std::vector;
    using Grid::LocalGrid; 
    using Grid::Grid;
    

    template <typename DIST, typename POT>
    void start_serial_worker(Grid<1> g, DIST psi, POT V)
    {
        vector<complex<double>> coeff(g.nx);
        vector<complex<double>> psi_t(g.nx);

        LocalGrid<1> l(g.x0, g.x1, 0, g.nx);
        DEBUG("Starting to calculate the coefficients...");
        calc_coeff(l, g, psi ,coeff );
        IO::save_coeff(0, coeff);
        DEBUG("Finished calculating");
        int index = l.nx0 - g.nx / 2 + 1;
        hid_t fl;
        fl = H5Fcreate(FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

		DEBUG("Starting to calculate the time evolution in static potential")
        for(int i = 0; i < g.nt; i++)
		{

		  math::evolve_coeff(coeff, g.nx, (g.x1 - g.x0), l, (g.tmax - g.tmin) / double(g.nt));
		  std::fill(psi_t.begin(), psi_t.end(), 0);
		  math::vals_ev(psi_t, coeff, l, g, index, V);
		  math::phase_fac(l, g, V, psi_t);
		  shift_res(psi_t);
		  ex_im_rl(psi_t);
		  IO::save_step_serial(g, psi_t, i, fl);

		}

	  	DEBUG("Finished, cleaning up.")
        H5Fclose(fl);
    }
}