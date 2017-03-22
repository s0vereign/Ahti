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
    void ev_step(std::vector<std::complex<double>>& vals,
                 std::vector<std::complex<double>>& coef,
                 const Localgrid1D& lgrid,
                 const T_CONF& c,
                 int size,
                 int rank
                 )
    {
        const double dx = config::get_dx(c);
        int n_sends = 0;
        const double l = config::get_l(c);
        const double dt = config::get_dt(c);
        while(n_sends < rank)
        {
            n_sends++;
            math::evolve_coeff(coef, c.gnx, l, lgrid, dt);
            math::vals_ev(vals, coef, lgrid, c, size, rank);
            comm::ring_send(vals, rank, size, lgrid.nx);
            
        }


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
