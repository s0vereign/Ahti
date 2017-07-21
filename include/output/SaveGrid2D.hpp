#pragma once


#include <string>
#include <fftw3.h>
#include "hdf5.h"
#include "hdf5_hl.h"
#include "H5Cpp.h"


#include "../grid/Grid.hpp"
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

    void save_grid_2d(containers::Array2D<fftw_complex>& vals, Grid::Grid<2> g, std::string fname)
    {

        containers::Array2D<double> realp(g.nx, g.ny);
        containers::Array2D<double> imagp(g.nx, g.ny);

        cast_fftw_to_double(vals, realp, imagp);
        H5::H5File file(fname.c_str(), H5F_ACC_TRUNC);
        hsize_t dims[1];
        dims[0] = g.nx*g.ny;
        H5::DataSpace dsprl(1, dims);
        H5::DataSpace dspim(1, dims);

        //@TODO Finish Grid output with C++ Interface
    }
}