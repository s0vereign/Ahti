#pragma once

#include <complex>
#include <math.h>
#include "grid/Localgrid.hpp"
#include "timeconf/Timeconf.hpp"
#include "math/FourierCoeff.hpp"
#include "math/CoeffEv.hpp"
#include "testfunctors/Gaussian.hpp"
#include "config/Config1D.hpp"
#include "communication/Ring.hpp"


namespace Worker {

    using namespace Grid;

    template<typename T_CONF>
    void calc_vals(const Localgrid1D& lgrid,
                   std::vector<std::complex<double>>& res,
                   T_CONF& c)
    {
        double xmax = c.xmax;
        double xmin = c.xmin;
        double nx = lgrid.nx;
        double dx = (xmax - xmin) / nx;
        double x = 0; 
        auto tdist = c.tf;
        for(int i = 0; i < nx; i++)
        {
            x += dx;
            res[i] = tdist(x);
        }
    }

    template<typename T_CONF>
    void calc_coeff(const Localgrid1D& lgrid,
                    std::vector<std::complex<double>>& res,
                    T_CONF& c
                    )
    {
        DEBUG("Calculating coeff")
        const double h = (c.xmax - c.xmin)/c.gnx;

        const double alpha = 2*M_PI/c.xmax;

        int index = 0;
        for(int i = lgrid.xmin; i < lgrid.xmax; i++)
            {

                index = i - c.gnx/2 + 1;
                math::fourier_1D_serial(alpha*index, c.gnx, c.tf, h, c.xmin, res[i-lgrid.xmin]);

            }
    }

    template<typename T_CONF>
    void ev_step(std::vector<std::complex<double>>& val,
                 std::vector<std::complex<double>>& coef,
                 const Localgrid1D& lgrid,
                 const T_CONF& c,
                 int rank,
                 int size
                 )
    {
        
    }

    template<typename T_CONF>
    void time_ev(const Localgrid1D& lgrid,
                 std::vector<std::complex<double>>& val,
                 std::vector<std::complex<double>>& coef,
                 T_CONF& c, 
                 int rank,
                 int size)
    {
        const double tmin = c.tmin;
        const double tmax = c.tmax;
        const double nt = c.nt;
        
        for(int i = 0; i < nt; i++)
        {
            
        }
    }

    template<typename T_CONF>
    void start_worker(MPI_Datatype* LGrid1D,
                      T_CONF& c,
                      int mpi_id,
                      int size)
    {

        MPI_Status status;
        Grid::Localgrid1D* lgrid = Grid::create_Localgrid1D(0,0,0);
        MPI_Recv(lgrid, 1,*LGrid1D, 0, 0, MPI_COMM_WORLD, &status);

        DEBUG("Recieved local grid with: " << lgrid->xmax << " "<< lgrid-> xmin<< " " << lgrid->nx)

        if(lgrid->nx == -1)
        {
            DEBUG("Terminating..." )
            return;
        }

        std::vector<std::complex<double>> vals(lgrid->nx);
        std::vector<std::complex<double>> coef(lgrid->nx);
        calc_vals(*lgrid, vals, c);
        calc_coeff(*lgrid, coef, c);
        
        DEBUG("Rank " << mpi_id << " finished calculations!")
    }

} // Worker
