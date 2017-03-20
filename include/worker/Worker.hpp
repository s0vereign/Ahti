#pragma once

#include <complex>
#include <math.h>
#include "grid/Localgrid.hpp"
#include "timeconf/Timeconf.hpp"
#include "math/FourierCoeff.hpp"
#include "testfunctors/Gaussian.hpp"
#include "config/Config1D.hpp"
#include "communication/Ring.hpp"


namespace Worker {

    using namespace Grid;

    template<typename T_CONF>
    void calc_coeff(const Localgrid1D& lgrid,
                    std::vector<std::complex<double>>& res,
                    T_CONF& c
                    )
    {
        DEBUG("Calculating coeff")
        double h = (c.xmax - c.xmin)/c.gnx;

        double alpha = 2*M_PI/c.xmax;

        int index = 0;
        for(int i = lgrid.xmin; i < lgrid.xmax; i++)
            {

                index = i - c.gnx/2 + 1;
                math::fourier_1D_serial(alpha*index, c.gnx, c.tf, h, c.xmin, res[i-lgrid.xmin]);

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

        std::vector<std::complex<double>> res(lgrid->nx);
        calc_coeff(*lgrid, res, c);

        DEBUG("Worker " << mpi_id << " has finished calculating coefficients!");

        comm::ring_send<std::vector<std::complex<double>>>(res, mpi_id, size, lgrid->nx);

        
    }

} // Worker
