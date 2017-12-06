#pragma once

#include <memory>
#include <fftw3.h>
#include <complex>
#include <cassert>

#include "../debug/DebugDef.h"

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
            void mult_data(int x, std::complex<double> z);
            double get_real(int x);
            double get_imag(int x);
    };

}
template<typename T>
double containers::Array1D<T>::get_real(int x)
{
    fftw_complex* temp = &data[x];
    return (*temp)[0];
}

template<typename T>
double containers::Array1D<T>::get_imag(int x)
{
    fftw_complex* temp = &data[x];
    return (*temp)[1];
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
    return &data[0];
}

template<typename T>
void containers::Array1D<T>::mult_data(int x, T val)
{
    double a = (data[x])[0];
    double b = (data[x])[1];
    double x1 = val[0];
    double y1 = val[1];
    (data[x])[0] = a * x1 - b * y1;
    (data[x])[1] = y1 * a + b * x1;
}

template<typename T>
void containers::Array1D<T>::mult_data(int x, std::complex<double> z)
{
    std::complex<double> f = {(data[x])[0], (data[x])[1]};
    f *= z;
    (data[x])[0] = f.real();
    (data[x])[1] = f.imag();
}

template <typename T>
void containers::Array1D<T>::set_stdc(int x, std::complex<double> c)
{
    (data[x])[0] = c.real();
    (data[x])[1] = c.imag();
    assert((data[x])[0] == c.real());
    assert((data[x])[1] == c.imag());
}