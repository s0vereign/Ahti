#pragma once

#include <complex>
#include "grid/Localgrid.hpp"
#include "timeconf/Timeconf.hpp"
#include "math/FourierCoeff.hpp"
#include "testfunctions/Gaussian.hpp"
#include "config/Config1D.hpp"


namespace Worker {

    using namespace Grid;
    template<typename T_CONF>
    void start_worker(MPI_Datatype* LGrid1D,
                      T_CONF& c,
                      int mpi_id)
    {

        auto tf = c.tf;
        MPI_Status status;
        Grid::Localgrid1D* lgrid = Grid::create_Localgrid1D(0,0,0);
        MPI_Recv(lgrid, 1,*LGrid1D, 0, 0, MPI_COMM_WORLD, &status);
        
        std::vector<std::complex<double>> res(lgrid->nx);
        double h = (c.xmax - c.xmin)/lgrid->nx;
        std::complex<double> res1;

        math::fourier_1D_serial(0.0, lgrid->nx, c.tf,h, 0.0, res1);
        printf("res = %f \n", res1.real());
    }


} // Worker
