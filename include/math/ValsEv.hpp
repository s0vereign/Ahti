#pragma once

#include <complex>
#include <vector>

#include "grid/Localgrid.hpp"

#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif


namespace math{

    using std::complex;
    using std::vector;
    using std::exp;
    using Grid::Localgrid1D;

    template<typename T_CONF>
    void vals_ev(vector<complex<double> >& vals,
                 vector<complex<double> >& coeff,
                 const Localgrid1D& lgrid,
                 const T_CONF& conf,
                 int size, 
                 int rank)
    {
        
    }
}