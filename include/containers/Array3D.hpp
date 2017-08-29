#pragma once
#include <memory>
#include <array>
#include <vector>
#include <fftw3.h>

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


        void set_compl(int x, int y, int z, const T& val)
        {
            data[x*nx+y*ny+z][0] = val[0];
            data[x*nx+y*ny+z][1] = val[1];
        }

        T& get_compl(int x, int y, int z)
        {
            return data[x * nx + y * ny + z];
        }

        T* get_raw_ptr()
        {
            return data.data();
        }

        std::vector<T>& get_cont_ref()
        {
            return data;
        }

        void mult_compl(const T& fak)
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
    };
}