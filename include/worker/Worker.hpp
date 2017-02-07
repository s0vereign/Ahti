#pragma once

#include <complex>
#include "grid/Localgrid.hpp"
#include "timeconf/Timeconf.hpp"
#include "math/FourierCoeff.hpp"
#include "potentials/HarmOsc1D.hpp"

namespace Worker {


    void start_worker(MPI_Datatype* LGrid1D, MPI_Datatype * TimeType,int mpi_id)
    {

        MPI_Status status;
        Grid::Localgrid1D* lgrid = Grid::create_Localgrid1D(0,0,0);
        MPI_Recv(lgrid, 1,*LGrid1D, 0, 0, MPI_COMM_WORLD, &status);
        
        std::vector<std::complex<double>> res(lgrid->nx);
        double h = (lgrid->xmax - lgrid->xmin)/lgrid->nx;
        math::fourier_1D_serial<double, potential::HarmOsc1D>(0.0, h, (size_t) lgrid->nx, 0.0, res[0]);

    }


} // Worker
