#pragma once

#include <memory>
#include <fftw3.h>
#include <complex>


namespace containers
{
    template <typename T>
    class Array1D
    {
        private:
            std::unique_ptr<T[]> data;
            int nx;

        public:
            Array1D(int nx_) : nx(nx_), data(new T[nx_])
            {
            }

            void set(int x, T t);
            void set_stdc(int x, std::complex<double> c);
            T* get(int x);
            int get_nx();
            T* get_raw_ptr();
            void mult_data(int x, T val);

    };

}

template<typename T>
T* containers::Array1D<T>::get(int x)
{
    return &data[x];
}

template<typename T>
void containers::Array1D<T>::set(int x, T t)
{
    data[x] = t;
}

template<typename T>
int containers::Array1D<T>::get_nx()
{
    return nx;
}

template<typename T>
T* containers::Array1D<T>::get_raw_ptr()
{
    return data.get();
}

template<typename T>
void containers::Array1D<T>::mult_data(int x, T val)
{
    double a = data[x][0];
    double b = data[x][1];
    double x1 = val[0];
    double y1 = val[1];
    data[x][0] = a * x1 - b * y1;
    data[x][1] = y1 * a + b * x1;
}

template <typename T>
void containers::Array1D<T>::set_stdc(int x, std::complex<double> c)
{
    data[x][0] = c.real();
    data[x][1] = c.imag();
}