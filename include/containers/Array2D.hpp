#pragma once

#include <complex>
#include <memory>
#include <fftw3.h>

#include "../math/CMultFFTW.hpp"

namespace containers
{
    template<typename T>
    class Array2D
    {
        private:
            std::unique_ptr<T[]> data;
            int nx, ny;

        public:

            typedef T type;
            static const type t;

            Array2D(int nx_, int ny_)
            : data(new T[nx_*ny_]), nx(nx_), ny(ny_)
            {
            };

            void set(T t, int x, int y)
            {
                data[x*nx + y] = t;
            }

            T get(int x, int y)
            {
                return data[x*nx + y];
            }

            T* get_raw_ptr()
            {
                return data.get();
            }

            int get_nx()
            {
                return nx;
            }

            int get_ny()
            {
                return ny;
            }

            T* get_val_ptr(int x, int y)
            {
                T* ptr = &data[nx*x+y];
                return ptr;
            }

            T* get_arr_ptr(int x, int y)
            {
                return get_val_ptr(x,y);
            }

    };

    template <>
    class Array2D<fftw_complex>
    {
        private:
            std::unique_ptr<fftw_complex[]> data;
            int nx, ny;

        public:


            Array2D(int nx_, int ny_)
            : data(new fftw_complex[nx_*ny_]), nx(nx_), ny(ny_)
            {};

            void set(fftw_complex t, int x, int y)
            {
                data[x*nx + y][0] = t[0];
                data[x*nx + y][1] = t[1];
            }

            void set_real(double t, int x, int y)
            {
                data[x*nx + y][0] = t;
            }

            void set_imag(double t, int x, int y)
            {

                data[x*nx + y][1] = t;
            }

            double get_real(int x, int y)
            {
                return data[x*nx + y][0];

            }

            double get_imag(int x, int y)
            {
                return data[x * nx + y][1];
            }

            fftw_complex* get_raw_ptr()
            {
                return data.get();
            }

            int get_nx()
            {
                return nx;
            }

            int get_ny()
            {
                return ny;
            }

            double* get_val_ptr(int x, int y)
            {
                double* ptr = data[nx*x + y];
                return ptr;
            }

            fftw_complex* get_arr_ptr(int x, int y)
            {
                fftw_complex* ptr = &data[nx*x,y];
                return ptr;
            }

            void mult_data(int x, int y, std::complex<double> z)
            {
                double a = data[nx*x + y][0];
                double b = data[nx*x + y][1];
                x = z.real();
                y = z.imag();
                data[nx*x + y][0] = a * x - b * y;
                data[nx*x + y][1] = y * a + b * x;
            }
    };
}