#pragma once

#include <vector>
#include <complex>
#include <algorithm>
#include <fftw3.h>

#include "hdf5.h"
#include "hdf5_hl.h"


#include "grid/Grid.hpp"
#include "grid/LocalGrid.hpp"
#include "math/CoeffEv.hpp"
#include "math/FourierCoeff.hpp"
#include "math/ValsEv.hpp"
#include "math/ScalarProd.h"
#include "math/TimeFt.h"
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

        vector<complex<double>> corr_fun(g.nt);


        LocalGrid<1> l(g.x0, g.x1, 0, g.nx);
        DEBUG("Starting to calculate the coefficients...");


		// Init the pst_t vector
		init_psi(l, g, psi, psi_t);

	    //IO::save_coeff(0, psi_t);
        DEBUG("Finished calculating");
        hid_t fl;
        fl = H5Fcreate(FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

		DEBUG("Starting to calculate the time evolution in static potential")

        for(int i = 0; i < g.nt; i++)
		{


		  	recalc_coeff(l, g, coeff, psi_t);
			IO::save_coeff(0, coeff);
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
			//ex_im_rl(psi_t);
			DEBUG("Currently in timestep " << i);
			//IO::save_step_serial(g, psi_t, i, fl);
			//ex_im_rl(psi_t);
            ex_im_rl(psi_t);
            corr_fun[i] = math::scalar_prod(psi_t, psi, g, l);
            ex_im_rl(psi_t);
		}

	  	DEBUG("Finished, cleaning up.");
        H5Fclose(fl);
        DEBUG("Saving Correlation function...");
        //fl = H5Fcreate("corr_fun.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
        //IO::save_step_serial(g, corr_fun, 0, fl);
        //H5Fclose(fl);

        weigh_corr_fun(corr_fun, g);
        vector<complex<double>> spec_fun(g.nt);


        DEBUG("Calculating Spectrum...");
        // Create Spectral function with FFTW
        fftw_complex* in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*corr_fun.size());
        fftw_complex* out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*corr_fun.size());
        cast_std_to_fftw(corr_fun, in);
        fftw_plan p = fftw_plan_dft_1d(spec_fun.size(), in, out, FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_execute(p);

        cast_fftwc_to_stdc(out, spec_fun);
        fftw_free(in);
        fftw_free(out);
        DEBUG("Done! Saving Spectrum...");
        fl = H5Fcreate("spec_fun.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
        DEBUG("In saving step!");
        IO::save_corr_serial(g, spec_fun, 0, fl);

        DEBUG("In closing step!");
        H5Fclose(fl);
        DEBUG("Done!")



    }
}
