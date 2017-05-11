#pragma once

#include <vector>
#include <complex>
#include <string>

#include "hdf5.h"
#include "hdf5_hl.h"

#include "output/SaveStep.hpp"

namespace IO {

    using std::vector;
    using std::complex;
    using std::string;
    using std::to_string;

    void save_coeff(int mpi_r, 
                    vector<complex<double> >& lres)
    {

        string fname = "coeff_out_"+to_string(mpi_r)+".h5";
        string dname_real = "/dreal";
        string dname_imag = "/dimag";

        hid_t f = H5Fcreate(fname.c_str(),H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

        vector<double> real(lres.size());
        vector<double> imag(lres.size());
        hsize_t size = lres.size();

        recast(lres, real, imag);

        H5LTmake_dataset(f, dname_real.c_str(), 1, &size, H5T_NATIVE_DOUBLE, real.data());
        H5LTmake_dataset(f, dname_imag.c_str(), 1, &size, H5T_NATIVE_DOUBLE, imag.data());

        H5Fclose(f);

    } 


}