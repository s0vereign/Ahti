#pragma once

#include <array>

//! Namespace containing the Grid specifications
namespace Grid 
{
    /**
     * Dummy Struct of the Grid.
     *
     * @tparam d spatial Dimension of the grid
     */
    template<int d>
    struct Grid
    {
    };

    /**
     * @brief Template specification of the 1D Grid
     *
     *
     * This is the partial template implementation of the 1D Grid.
     *
     */
    template<>
    struct Grid<1>
    {
        double x0, x1;
        double dx;
        int nx;
        double t0, t1;
        double dt;
        int nt;

       /**
        * @brief Constructor for a 1D grid
        *
        * @param x0_ start of the spatial interval
        * @param x1_ end of the spatial interval
        * @param nx_ number of spatial steps
        * @param tmin_ start time
        * @param tmax_ end time
        * @param nt_  number of timesteps
        */
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

    /**
     * @brief Template specification of the 2D grid
     */
    template<>
    struct Grid<2>
    {
        double x0, x1, dx;
        double y0, y1, dy;
        int nx, ny;
        double t0, t1, dt;
        int nt;

        /**
         * @brief Constructor which specifies a 2D Grid
         * x_0_i is always the starting point of the spatial time Interval
         * x_1_i is always the end point of the interval in dimension i
         * n_i is alwas the number of gridpoints in the interval. IMPORTANT: The endpoint is not included!
         * @param x0_
         * @param x1_
         * @param y0_
         * @param y1_
         * @param nx_
         * @param ny_
         * @param tmin_
         * @param tmax_
         * @param nt_
         */
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

    /**
     * @brief Template specification of the 3D grid
     */
    template<>
    struct Grid<3>
    {
        double x0, x1;
        double y0, y1;
        double z0, z1;
        int nx, ny, nz,nt;
        double t0, t1;
        double dt, dx,dy,dz;

        /**
         *@brief Constructor which specifies a 3D Grid
         * x_0_i is always the starting point of the spatial time Interval
         * x_1_i is always the end point of the interval in dimension i
         * n_i is alwas the number of gridpoints in the interval. IMPORTANT: The endpoint is not included!
         * @param x0
         * @param x1
         * @param y0
         * @param y1
         * @param z0
         * @param z1
         * @param nx
         * @param ny
         * @param nz
         * @param tmin
         * @param tmax
         * @param nt
         */
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
