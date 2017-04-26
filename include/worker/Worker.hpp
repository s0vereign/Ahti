#pragma once

#include <complex>
#include <vector>


#include "grid/Grid.hpp"
#include "grid/LocalGrid.hpp"
#include "StaticCalcs.hpp"

namespace Worker
{
    using std::complex;

    Grid::LocalGrid<1> init_lgrid(Grid::Grid<1> grid, int mpi_s, int mpi_r)
    {
        // Assumptions: nx%2=0 and mpi_s%2=0, (s=size) so each MPI Rank gets an equal
        // sized chunk out of simplicity reasons(no dynamical scheduling)
        int lgsize = grid.nx/mpi_s;
        int ind0 = lgsize * mpi_r;
        int ind1 = ind0 + lgsize - 1;
        double x0 = ind0 * grid.dx;
        double x1 = ind1 * grid.dx;
        return Grid::LocalGrid<1>(x0, x1, ind0, ind1);
    };
    
    
    template<typename DIST, typename POT>
    void start_worker(Grid::Grid<1> grid, int mpi_s, int mpi_r, DIST d, POT p)
    {
        Grid::LocalGrid<1> lgrid = init_lgrid(grid, mpi_s, mpi_r);
        DEBUG(mpi_r << ": " << lgrid.nx0 << " " << lgrid.nx1);
        std::vector<complex<double> > psi_0(lgrid.nx1 - lgrid.nx0);
        std::vector<complex<double> > psi_coeff(lgrid.nx1 - lgrid.nx0);
        
        calc_coeff(lgrid, grid, d, psi_coeff);
        
        DEBUG(mpi_r << ": " << "finished!");
        
        
    }
}

