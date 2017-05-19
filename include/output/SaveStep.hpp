#pragma once 

#include <string>
#include <vector>
#include <complex>

#include "mpi.h"
#include "hdf5.h"
#include "hdf5_hl.h"

#include "grid/Grid.hpp"
#include "grid/LocalGrid.hpp"


namespace IO
{

    using namespace std;
    using Grid::Grid;

    void recast( vector<complex < double > >& recv_buf, 
                 vector<double>& real, 
                 vector<double>& imag)
                 {
                     auto it_real = real.begin();
                     auto it_imag = imag.begin();
                     for(auto& j : recv_buf)
                     {
                         *it_real = j.real();
                         *it_imag = j.imag();
                         it_real++;
                         it_imag++;
                     }
                 }


    void save_step       (
                          int mpi_r,
                          int mpi_s,
                          Grid<1> g,
                          vector<complex<double>>& lres,
                          int step,
                          hid_t& floc
                          )
    {

        vector<complex < double > > recv_buf(1);
        vector<double> real(1);
        vector<double> imag(1);
        if(mpi_r == 0)
        {
            recv_buf.resize(g.nx);
            
            DEBUG("Starting gather opertaion!");
        }
        MPI_Gather(lres.data(), lres.size(), MPI::DOUBLE_COMPLEX, recv_buf.data(), lres.size(), MPI::DOUBLE_COMPLEX, 0, MPI_COMM_WORLD);
        
        if(mpi_r == 0)
        {
            real.resize(g.nx);
            imag.resize(g.nx);
            recast(recv_buf, real, imag);
            string d_name_real = "/dset"+to_string(step)+"real";
            string d_name_imag = "/dset"+to_string(step)+"imag";
            hsize_t size = recv_buf.size();
            H5LTmake_dataset(floc, d_name_real.c_str(), 1, &size, H5T_NATIVE_DOUBLE, real.data());
            
            H5LTmake_dataset(floc, d_name_imag.c_str(), 1, &size, H5T_NATIVE_DOUBLE, imag.data());
        }

    };

    void save_step_serial(Grid<1> g, vector<complex<double>>& res, int step, hid_t floc)
    {
        vector<double> real(g.nx);
        vector<double> imag(g.nx);
        recast(res, real, imag);
        hsize_t size = res.size();
        string d_name_real = "/dset"+to_string(step)+"real";
        string d_name_imag = "/dset"+to_string(step)+"imag";
        H5LTmake_dataset(floc, d_name_real.c_str(), 1, &size, H5T_NATIVE_DOUBLE, real.data());
        H5LTmake_dataset(floc, d_name_imag.c_str(), 1, &size, H5T_NATIVE_DOUBLE, imag.data());
    }
    

}