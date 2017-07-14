#pragma once


#include <complex>
#include <vector>

#include "../grid/Grid.hpp"


namespace math
{
    using std::complex;
    using std::vector;


    void reconstruct_wv(complex<double>** frames, vector<complex<double> >& res, Grid<1>& g, double E)
    {
        const double dt = g.dt;
        const int nt = g.nt;

        double t = g.tmin;
        double T = g.tmax;
        complex<double> iu(0,1);
        for(int n = 0; n < g.nx; n++)
        {
            for(int i = 0; i < g.nt; i++)
            {
                res[n] += frames[i][n]*(1-cos(2*M_PI*t/T))*std::exp(iu*E*t);
                t += dt;
            }

            // Watch out w(0) = 0 thus neither the first nor the last sum delivers anything
            res[n] -= 0.5 * (frames[0][n]*(1-cos(0))*std::exp(iu*E*0.0)+frames[g.nt-1][n]*(1-cos(2*M_PI*t/T))*std::exp(iu*E*T));
            res[n] *= dt;
        }
    }
}