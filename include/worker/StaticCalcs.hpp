#pragma once 


#include <complex>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <fftw3.h>

#include "grid/Grid.hpp"
#include "grid/LocalGrid.hpp"
#include "math/FourierCoeff.hpp"
#include "math/CoeffEv.hpp"
#include "math/ValsEv.hpp"


#include "debug/DebugDef.h"
//#include "communication/Ring.hpp"
#include "output/SaveStep.hpp"



#define FILE "wf_out.h5"

namespace Worker 
{
    using std::complex;
    using std::vector;


    void shift_res(vector<complex<double>>& res)
    {
        // This function shifts the real spaced function
        // to the right index position in 1D

        vector<complex<double>> cpy(res.size());
        std::copy(res.begin()+res.size()/2, res.end(), cpy.begin());
        std::copy(res.begin(), res.begin() + res.size()/2 , cpy.begin()+cpy.size()/2);
        std::copy(cpy.begin(), cpy.end(), res.begin());
    };

	void ex_im_rl(vector<complex<double>>& res)
	{
	  	// This function is a temporary hack in order to
	  	// solve the sign question


		std::transform(res.begin(), res.end(), res.begin(),
					   [](complex<double> a)
					   {
		  					return complex<double>(a.imag(), a.real());
						});
	};

    template<typename DIST>
    void calc_coeff(Grid::LocalGrid<1> lgrid, Grid::Grid<1> g, DIST d,vector<complex<double> >& res)
    {
        const int n0 = lgrid.nx0  - g.nx / 2 + 1;
        double dx = lgrid.dx;
        double ind0 = double(n0);
        for( int i = 0; i < res.size(); i++)
        {
            math::fourier_1D_init(ind0, g.nx, d, dx, g.x0, res[i]);
            ind0++;

        }
    };

    template<typename T_VAL, typename T_IN>
    void recalc_coeff(Grid::LocalGrid<1> lgrid, Grid::Grid<1> g, T_VAL& coef, T_IN psi)
    {
        const int n0 = lgrid.nx0 - g.nx / 2 + 1;
        double dx = lgrid.dx;
        double ind0 = double(n0);

        for(size_t i = 0; i  < coef.size(); i++)
        {
            math::fourier_1D(ind0, g.nx, psi, dx, g.x0, coef[i]);
            ind0++;
        }
    };

    template<typename T_VAL, typename DIST>
    void init_psi(Grid::LocalGrid<1> lgrid, Grid::Grid<1> g, DIST d, T_VAL& psi)
    {
        double x = lgrid.x0;
        double dx = g.dx;


        for(size_t i = 0; i < psi.size(); i++)
        {
            psi[i] = d(x);
            x += dx;
        }
    };

    void norm_function(vector<complex<double>>& res, Grid::Grid<1> g)
    {
        // Uses trapezoidal rule in order to norm res
        const double dx = g.dx;
        std::complex<double> vol(0,0);
        for( unsigned int i = 1; i < res.size()-1; i++)
        {
            vol += res[i] * std::conj(res[i]);
        }
        vol += 0.5 * (res[0] + res[res.size()-1]);
        vol *= dx;
        double v1 = 1/std::sqrt(vol.real());


        for(auto& j : res)
        {
            j *= v1;
        }
    }

    template<typename DIST, typename POT>
    void time_evo(  Grid::LocalGrid<1> lgrid, 
                    Grid::Grid<1> g,
                    DIST d,
                    POT p,
                    vector<complex<double>>& vals, 
                    vector<complex<double>>& psi0,
                    vector<complex<double>>& corr_func,
                    vector<complex<double>>& psi_coeff, 
                    int mpi_s, 
                    int mpi_r)
    {
        int nt = g.nt;
        int n_curr = lgrid.nx0;
        int ind_curr = n_curr - g.nx/2 + 1;
        const int psize = lgrid.nx1 - lgrid.nx0 + 1;
        const double dt = (g.tmax-g.tmin)/(nt);
        hid_t fl;
        if(mpi_r == 0)
            fl = H5Fcreate(FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

        for(int i = 0; i < nt; i++)
        {
            math::evolve_coeff(psi_coeff, g.nx, (g.x1-g.x0), lgrid, dt);
            
            for(int j = 0; j < mpi_s; j++)
            {
                // First evolve coefficients

                //DEBUG(mpi_r << ": Starting to calculate!");
                math::vals_ev(vals, psi_coeff, lgrid, g, ind_curr, p);

                //DEBUG(mpi_r << ": Finished!");
                // Since the index always increases after an send 
                // except when the coefficients with N/2-1 have been sent
                // we need to update our current index!
                ind_curr += psize;
                
                // If the - N / 2 + 1 package will be recieved, we need to reset 
                // our index
                
                if(ind_curr >= g.nx/2)
                {
                    //DEBUG("Index was: "<<ind_curr);
                    ind_curr = -g.nx/2+1;
                    //DEBUG("Index now:" << ind_curr);
                }
                MPI_Barrier(MPI_COMM_WORLD);
                //comm::ring_send(psi_coeff, mpi_r, mpi_s, psi_coeff.size());
                
            }

            // Account for final phase factor
            //phase_fac(lgrid, g, p, vals);

            IO::save_step(mpi_r, mpi_s, g, vals, i, fl);

            for(auto& it : vals)
            {
                it = 0;
            }
        }

        if(mpi_r == 0)
            H5Fclose(fl);
    };

    template<typename T_VAL>
    void weigh_corr_fun(T_VAL& corr_fun, Grid::Grid<1> g)
    {
        for(unsigned int i = 0; i < g.nt; i ++)
        {
            corr_fun[i] *= 1 - cos(2*M_PI*g.tmax*i*g.dt);
        }
    }


    template<typename T_VAL>
    void cast_std_to_fftw(const T_VAL& vals, fftw_complex* in)
    {

        for(unsigned int i = 0; i < vals.size(); i++)
        {
            in[i][0] = vals[i].real();
            in[i][1] = vals[i].imag();
        }
    }


    template<typename T_VAL>
    void cast_fftwc_to_stdc(fftw_complex* out, T_VAL& vals)
    {
        for(unsigned int i = 0; i < vals.size(); i++)
        {
            vals[i] = std::complex<double>(out[i][0],out[i][1]);
        }
    }


    void save_frame(complex<double>** arr, vector<complex<double>>& res, int step)
    {
        for(int j = 0; j < res.size(); j++)
        {
            arr[step][j] = res[j];
        }
    };
}
