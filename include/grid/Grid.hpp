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
        double t0, t1;
        double dt;
        int nt;
        Grid(double x0_,
             double x1_,
             int nx_,
             double tmin_,
             double tmax_,
             int nt_) :
             x0(x0_), x1(x1_), nx(nx_),
             t0(tmin_), t1(tmax_), nt(nt_)
             {
                dx = (x1-x0)/(nx);
                dt = (t1 - t0) / (nt);
             };
    };
    
    template<>
    struct Grid<2>
    {
        double x0, x1, dx;
        double y0, y1, dy;
        int nx, ny;
        double t0, t1, dt;
        int nt;

        Grid(double x0_,
                     double x1_,
                     double y0_,
                     double y1_,
                     int nx_,
                     int ny_,
                     double tmin_,
                     double tmax_,
                     int nt_)
            : x0(x0_), x1(x1_), nx(nx_),
              y0(y0_), y1(y1_), ny(ny_),
              t0(tmin_), t1(tmax_), nt(nt_)
        {
            dx = (x1 - x0) / nx;
            dy = (y1 - y0) / ny;
            dt = (t1 - t0) / nt;
        }
    };
    
    template<>
    struct Grid<3>
    {
        double x0, x1;
        double y0, y1;
        double z0, z1;
        int nx, ny, nz,nt;
        double t0, t1;
        double dt, dx,dy,dz;

        Grid(double x0,
             double x1,
             double y0,
             double y1,
             double z0,
             double z1,
             int nx,
             int ny,
             int nz,
             double tmin,
             double tmax,
             int nt)
            : x0(x0), x1(x1), y0(y0), y1(y1), z0(z0), z1(z1), nx(nx), ny(ny), nz(nz), t0(tmin), t1(tmax), nt(nt)

        {
            dt = (tmax - tmin) / nt;
            dx = (x1 - x0) / nx;
            dy = (y1 - y0) / ny;
            dz = (z1 - z0) / nz;
        }

        
    };

}
