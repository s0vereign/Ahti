#pragma once
#include <memory>
#include <array>
#include <vector>
#include <complex>
#include <fftw3.h>


#define DEBUG_ENABLED
#include "../debug/DebugDef.h"


namespace containers
{

    /*
     * This class provides a 3D Arraylike interface
     * with focus on fftw_complex like datatypes. It is
     * here to simplify gets, sets and multiplications.
     * The class will only compile for fftw_complex like
     * datatypes.
     */
    template<typename T>
    class Array3D
    {
        private:
        const size_t nx,ny,nz;
        std::vector<T> data;

        public:
        Array3D(const size_t nx, const size_t ny, const size_t nz) : nx(nx), ny(ny), nz(nz), data(nx*ny*nz)
        {

        }


        void set_compl(int x, int y, int z, T& val)
        {
            (data[nx * ny * x + nx * y + z])[0] = val[0];
            (data[nx * ny * x + nx * y + z])[1] = val[1];
        }

        void set_compl(int x, int y, int z, std::complex<double> c)
        {
            (data[nx * ny * x + nx * y + z])[0] = c.real();
            (data[nx * ny * x + nx * y + z])[1] = c.imag();
        }

        T& get_compl(int x, int y, int z)
        {
            return data[nx * ny * x + nx * y + z];
        }

        decltype(data.data()) get_raw_ptr()
        {
            return data.data();
        }

        std::vector<T>& get_cont_ref()
        {
            return data;
        }

        void norm(const T &fak)
        {
            auto a = fak[0];
            auto b = fak[1];

            for(auto& i : data)
            {
                auto x = i[0];
                auto y = i[1];
                i[0] = a * x - b * y;
                i[1] = y * a + x * b ;
            }
        }

        void mul_by_compl(int x, int y, int z, std::complex<double> c)
        {
            auto a = (data[nx*ny * x + nx * y + z])[0];
            auto b = (data[nx*ny * x + nx * y +z])[1];
            auto l = c.real();
            auto m = c.imag();
            (data[nx*ny * x + nx * y + z])[0] = a * l - m * b;
            (data[nx*ny * x + nx * y + z])[1] = a * m + b * l;

        }

        const size_t getNx() const
        {
            return nx;
        }

        const size_t getNy() const
        {
            return ny;
        }

        const size_t getNz() const
        {
            return nz;
        }


    };

    /*
     * Partial tempate specification for
     * double to get same interface for 3D
     * dataextraction
     */
    template<>
    class Array3D<double>
    {
        private:
        const size_t nx,ny,nz;
        std::vector<double> data;

        public:
        const size_t getNx() const { return nx; };
        const size_t getNy() const { return ny; };
        const size_t getNz() const { return nz; };



        Array3D(const size_t nx, const size_t ny, const size_t nz) : nx(nx), ny(ny), nz(nz), data(nx*ny*nz)
        {

        }

        void set(int x, int y, int z, const double& d)
        {
            data[nx * ny * x + nx * y + z] = d;
        }

        double get(int x, int y, int z)
        {
            return data[nx * ny * x + nx * y + z];
        }

        double* get_raw_ptr()
        {
            return data.data();
        }
    };



}