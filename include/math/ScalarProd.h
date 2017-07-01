#pragma once

#include <complex>
#include <vector>


#include "../grid/Grid.hpp"
#include "../grid/LocalGrid.hpp"

namespace math
{

    using std::complex;
    using namespace Grid;

    template<typename T_CONT, typename T_DIST>
    auto scalar_prod(const T_CONT& psi_t, T_DIST psi, Grid<1> g, LocalGrid<1> l)
    -> complex<double>
    {
        double h = g.dx;
        double x = l.x0;
        using std::complex;

        complex<double> res(0,0);

        for(size_t i = 0; i < psi_t.size(); i++)
        {
            res += std::conj(psi(x))*psi_t[i];
            x+= h;
        }

        res -= 0.5 * std::conj(psi(l.x0)) * psi_t[0];
        res -= 0.5 * std::conj(psi(l.x1)) * psi_t[g.nx-1];
        res *= h;

        return res;

    };
}