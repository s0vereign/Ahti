#pragma once

#include <vector>
#include <complex>
#include <algorithm>
#include <fftw3.h>
#include <stdlib.h>
#include <array>

#include "hdf5.h"
#include "hdf5_hl.h"


#include "grid/Grid.hpp"
#include "grid/LocalGrid.hpp"
#include "math/CoeffEv.hpp"
#include "math/FourierCoeff.hpp"
#include "math/ValsEv.hpp"
#include "math/ScalarProd.h"
#include "math/TimeFt.h"
#include "math/RecontructWV.hpp"
#include "worker/StaticCalcs1D.hpp"
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

        vector<complex<double>> corr_fun(g.nt);
        vector<complex<double>> spec_fun(g.nt);



        LocalGrid<1> l(g.x0, g.x1, 0, g.nx);
        DEBUG("Starting to calculate the coefficients...");


		// Init the pst_t vector
		init_psi(l, g, psi, psi_t);

	    //IO::save_coeff(0, psi_t);
        DEBUG("Finished calculating");
        hid_t fl;
        fl = H5Fcreate(FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

		DEBUG("Starting to calculate the time evolution in static potential")

        // This is a framebuffer to save each timestep in memory,
        // This is required when reconstructing the initial wave-functions
        complex<double>** frames;
        frames = (complex<double> **) malloc(sizeof(complex<double>*)*g.nt);

        for(int k = 0; k  < g.nt; k++)
            frames[k] = (complex<double> *) malloc(sizeof(complex<double>)*g.nx);

        for(int i = 0; i < g.nt; i++)
		{

            recalc_coeff(l, g, coeff, psi_t);
			//IO::save_coeff(0, coeff);
			math::evolve_coeff(coeff, g.nx, g.x1-g.x0, l, g.dt);
			std::fill(psi_t.begin(), psi_t.end(), 0);
			math::vals_ev(psi_t, coeff, l, g, V);

			shift_res(psi_t);
			math::phase_fac(l, g, V, psi_t);


			recalc_coeff(l, g, coeff, psi_t);
			math::evolve_coeff(coeff, g.nx, g.x1 - g.x0, l, g.dt);
			std::fill(psi_t.begin(), psi_t.end(), 0);
			math::vals_ev(psi_t, coeff, l, g, V);



			shift_res(psi_t);

            // The implementation currently exchanges
            // real an imaginary part, but solutions
            // are correct, thus ex_im_rl exchanges
            // real and imaginary part of the wave-function
			ex_im_rl(psi_t);
			DEBUG("Currently in timestep " << i);
            if(i % 100 == 0)
			    IO::save_step_serial(g, psi_t, i, fl);
            save_frame(frames, psi_t, i);
            ex_im_rl(psi_t);


		}

        std::cout << "Finished! Cleaning up!" << std::endl;

        for(int k = 0; k < g.nt; k++)
        {
            free(frames[k]);
        }
        free(frames);

    }
}
