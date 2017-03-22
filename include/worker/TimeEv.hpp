#pragma once 

#include <vector>
#include <complex>

#include "grid/Localgrid.hpp"
#include "timeconf/Timeconf.hpp"
#include "math/FourierCoeff.hpp"
#include "math/CoeffEv.hpp"
#include "math/ValsEv.hpp"
#include "testfunctors/Gaussian.hpp"
#include "config/Config1D.hpp"
#include "communication/Ring.hpp"

namespace Worker {

    using Grid::Localgrid1D;


    template<typename T_CONF>
    void ev_step(std::vector<std::complex<double>>& val,
                 std::vector<std::complex<double>>& coef,
                 const Localgrid1D& lgrid,
                 const T_CONF& c,
                 int rank,
                 int size
                 )
    {
        double dx = config::get_dx(c);
        
    }

    template<typename T_CONF>
    void time_ev(const Localgrid1D& lgrid,
                 std::vector<std::complex<double>>& val,
                 std::vector<std::complex<double>>& coef,
                 T_CONF& c, 
                 int rank,
                 int size)
    {
        const double tmin = c.tmin;
        const double tmax = c.tmax;
        const double nt = c.nt;
        
        for(int i = 0; i < nt; i++)
        {
            
        }
    }
} // Worker
