#pragma once

#include <complex>
#include <vector>

#include "grid/Localgrid.hpp"
#include "grid/GridControl.hpp"
#include "config/Config1D.hpp"
#include "worker/Worker.hpp"




namespace Master {

    using namespace Grid;
    template<typename T_CONF>
    void start_master(  MPI_Datatype* LGrid1D,
                        T_CONF& c,
                        Sim1D* params,
                        int mpi_size,
                        int mpi_id
                        )
                        {

                            Localgrid1D mlgrid = *create_Localgrid1D(0,0,0);
                            control_sim_init(params, mpi_size, mpi_id, LGrid1D, &mlgrid);
                            DEBUG("Recieved local grid with: " << mlgrid.xmax << " " << mlgrid.xmin << " " <<mlgrid.nx)

                            std::vector<std::complex<double>> res(mlgrid.nx);

                            Worker::calc_coeff(mlgrid, res, c);
                            comm::ring_send(res, mpi_id, mpi_size, mlgrid.nx);
                            DEBUG("Master finished")

                        }

} // MASTER
