#pragma once 


#include <complex>
#include <vector>
#include <algorithm>

#include "grid/Grid.hpp"
#include "grid/LocalGrid.hpp"
#include "math/FourierCoeff.hpp"
#include "math/CoeffEv.hpp"
#include "math/ValsEv.hpp"
#include "communication/Ring.hpp"


namespace Worker 
{
    using std::complex;
    using std::vector;
    
    template<typename DIST>
    void calc_coeff(Grid::LocalGrid<1> lgrid, Grid::Grid<1> g, DIST d,vector<complex<double> >& res)
    {
        const int n0 = lgrid.nx0 - g.nx/2 + 1;
        const int n1 = lgrid.nx1 - g.nx/2 + 1;
        
        double dx = lgrid.dx;
        
        int ind0 = n0;
        
        for( complex<double> & c : res)
        {
            math::fourier_1D_serial(ind0, g.nx, d, dx, lgrid.x0, c);
            ind0 += 1;
        }
        
    };
    
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
        int t = 0;
        int nt = g.nt;
        int n_curr = lgrid.nx0;
        int ind_curr = n_curr - g.nx/2 + 1;
        const int psize = lgrid.nx1 - lgrid.nx0;
        const double dt = (g.tmax-g.tmin)/(nt);
        
        for(int i = 0; i < nt; i++)
        {
            math::evolve_coeff(psi_coeff, g.nx, (g.x1-g.x0), lgrid, dt);
            
            MPI_Barrier(MPI_COMM_WORLD);
            for(int j = 0; j < mpi_s; j++)
            {
                // First evolve coeeficients

                DEBUG(mpi_r << ": Starting to calculate!");
                math::vals_ev(vals, psi_coeff, lgrid, g, ind_curr, p);

                DEBUG(mpi_r << ": Finished!");
                // Since the index always increases after an send 
                // except when the coefficients with N/2-1 have been sent
                // we need to update our current index!
                ind_curr += psize;
                
                // If the -N/2+1 package will be recieved, we need to reset 
                // our index
                
                if(ind_curr >= g.nx/2)
                {
                    DEBUG("Index was: "<<ind_curr);
                    ind_curr = -g.nx/2+1;
                    DEBUG("Index now:" << ind_curr);
                }
                MPI_Barrier(MPI_COMM_WORLD);
                comm::ring_send(psi_coeff, mpi_r, mpi_s, psi_coeff.size());
                
            }
        }
        
    };
}
