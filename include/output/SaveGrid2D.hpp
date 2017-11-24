#pragma once


#include <string>
#include <fftw3.h>
#include "hdf5.h"
#include "hdf5_hl.h"


#include "grid/CGrid.hpp"
#include "../grid/LocalGrid.hpp"
#include "../containers/Array2D.hpp"

namespace IO
{

    void cast_fftw_to_double(containers::Array2D<fftw_complex>& vals,
                             containers::Array2D<double>& rl,
                             containers::Array2D<double>& im)
    {
        for(int i = 0; i < vals.get_nx(); i++)
        {
            for(int j = 0; j < vals.get_ny(); j++)
            {
                rl.set(vals.get_real(i, j), i, j);
                im.set(vals.get_imag(i, j), i, j);
            }
        }
    }

    void save_grid_2d(containers::Array2D<fftw_complex>& vals, Grid::CGrid<2> g, std::string fname)
    {

        containers::Array2D<double> realp(g.nx, g.ny);
        containers::Array2D<double> imagp(g.nx, g.ny);

        cast_fftw_to_double(vals, realp, imagp);
        hid_t file = H5Fcreate(fname.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
        hsize_t dims[1];
        dims[0] = g.nx*g.ny;

        hid_t dataspace_id = H5Screate_simple(1,dims,NULL);

        hid_t dataset_id = H5Dcreate2(file, "/real", H5T_NATIVE_DOUBLE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

        herr_t status = H5Dwrite(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, realp.get_raw_ptr());

        status = H5Dclose(dataset_id);
        status = H5Sclose(dataspace_id);

        dataspace_id = H5Screate_simple(1, dims, NULL);
        dataset_id = H5Dcreate2(file, "/imag", H5T_NATIVE_DOUBLE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        status = H5Dwrite(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, imagp.get_raw_ptr());
        status = H5Dclose(dataset_id);
        status = H5Sclose(dataspace_id);

        status = H5Fclose(file);


    }
}