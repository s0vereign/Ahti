#pragma once
#include <fftw3.h>
#include <hdf5.h>
#include <vector>
#include <string>
#include <iostream>

#include "grid/CGrid.hpp"
#include "../containers/Array3D.hpp"



namespace IO
    {
        using containers::Array3D;
        using std::vector;
        using std::string;


        template<typename T, typename T_ATOMIC>
        void cast_to_double(Array3D<T> &psi, Array3D<T_ATOMIC> &real, Array3D<T_ATOMIC> &imag, Grid::CGrid<3> g)
        {

            for(int i = 0; i < g.nx; i++)
            {
                for(int j = 0; j < g.ny; j++)
                {
                    for(int k = 0; k < g.nz; k++)
                    {
                        auto a = psi.get_compl(i,j,k)[0];
                        auto b = psi.get_compl(i,j,k)[1];
                        real.set(i,j,k,a);
                        imag.set(i,j,k,b);
                    }
                }
            }
        }

        template<typename T>
        void save_grid_3D(Array3D<T>& psi, Grid::CGrid<3> g, string fname)
        {
            Array3D<double> real(g.nx, g.ny, g.nz);
            Array3D<double> imag(g.nx, g.ny, g.nz);

            cast_to_double(psi, real, imag, g);

            // HDF5 boilerplate code
            hid_t file = H5Fcreate(fname.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
            hsize_t dims[1];
            dims[0] = g.nx*g.ny*g.nz;

            hid_t dataspace_id = H5Screate_simple(1,dims,NULL);

            hid_t dataset_id = H5Dcreate2(file, "/real", H5T_NATIVE_DOUBLE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

            herr_t status = H5Dwrite(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, real.get_raw_ptr());

            status = H5Dclose(dataset_id);
            status = H5Sclose(dataspace_id);

            dataspace_id = H5Screate_simple(1, dims, NULL);
            dataset_id = H5Dcreate2(file, "/imag", H5T_NATIVE_DOUBLE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
            status = H5Dwrite(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, imag.get_raw_ptr());
            status = H5Dclose(dataset_id);
            status = H5Sclose(dataspace_id);
            status = H5Fclose(file);

        }
    }