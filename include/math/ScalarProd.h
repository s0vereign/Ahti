#pragma once

#include <complex>
#include <vector>


#include "grid/CGrid.hpp"
#include "../grid/LocalGrid.hpp"

namespace math
{

    using std::complex;

    template<typename T_CONT, typename T_DIST>
    auto scalar_prod(const T_CONT& psi_t, T_DIST psi, CGrid<1> g)
    -> complex<double>
    {
        double h = g.dx;
        double x = g.x0;
        using std::complex;

        complex<double> res(0,0);

        for(size_t i = 0; i < psi_t.size(); i++)
        {
            res += std::conj(psi(x))*psi_t[i];
            x+= h;
        }

        res -= 0.5 * std::conj(psi(g.x0)) * psi_t[0];
        res -= 0.5 * std::conj(psi(g.x1)) * psi_t[g.nx-1];
        res *= h;

        return res;

    };
}