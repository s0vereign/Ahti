#pragma once 

#include <string>
#include <vector>
#include <complex>

#include "mpi.h"
#include "hdf5.h"
#include "hdf5_hl.h"

#include "grid/CGrid.hpp"
#include "grid/LocalGrid.hpp"


namespace IO
{

    using namespace std;
    using Grid::CGrid;

    template<typename T>
    void save_step(CGrid<1> g, T& psi, int fid)
    {
        string fname = "time_evo_" + to_string(fid) + ".h5";

        vector<double> real(g.nx);
        vector<double> imag(g.nx);

        for(uint i = 0; i < g.nx; i++)
        {
            real[i] = psi.get_real(i);
            imag[i] = psi.get_imag(i);
        }

        hid_t file_id = H5Fcreate(fname.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

        hsize_t size = real.size();
        string d_name_real = "/dset" + to_string(fid) + "real";
        string d_name_imag = "/dset" + to_string(fid) + "imag";

        H5LTmake_dataset(file_id, d_name_real.c_str(), 1, &size, H5T_NATIVE_DOUBLE, real.data());
        H5LTmake_dataset(file_id, d_name_imag.c_str(), 1, &size, H5T_NATIVE_DOUBLE, imag.data());

        H5Fclose(file_id);
    }

}