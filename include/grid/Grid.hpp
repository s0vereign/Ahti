#pragma once

#include <array>


namespace Grid 
{
    template<int d>
    struct Grid
    {};
    
    template<>
    struct Grid<1>
    {
        double x0, x1;
        double dx;
        int nx;
        double tmin, tmax;
        double dt;
        int nt;
        Grid(double x0_, double x1_, int nx_, 
             double tmin_, double tmax_, int nt_
              ) :
             x0(x0_), x1(x1_), nx(nx_),
             tmin(tmin_), tmax(tmax_), nt(nt_)
             {
                dx = (x1-x0)/(nx);
                dt = (tmax - tmin) / (nt);
             };
    };
    
    template<>
    struct Grid<2>
    {
        double x0, x1, dx;
        double y0, y1, dy;
        int nx, ny;
        double tmin, tmax, dt;
        int nt;

        Grid(double x0_, double x1_, int nx_,
             double y0_, double y1_, int ny_,
             double tmin_, double tmax_, int nt_)
            : x0(x0_), x1(x1_), nx(nx_),
              y0(y0_), y1(y1_), ny(ny_),
              tmin(tmin_), tmax(tmax_), nt(nt_)
        {
            dx = (x1 - x0) / nx;
            dy = (y1 - y0) / ny;
            dt = (tmax - tmin) / nt;
        }
    };
    
    template<>
    struct Grid<3>
    {
        double x0, x1;
        double y0, y1;
        double z0, z1;
        int nx, ny, nz;
        double tmin, tmax;
        int nt;
        
    };

}
