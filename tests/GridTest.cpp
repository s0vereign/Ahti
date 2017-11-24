#include "grid/CGrid.hpp"

#include "gtest/gtest.h"


TEST(GridTest, ContructorTest)
{
    int nx = 100;
    int ny = 20;
    int nt = 44;

    double x0  = 0;
    double x1 = 213;

    double y0 = 54;
    double y1 = 134;

    double t0 = 0.0;
    double t1 = 241;
    Grid::CGrid<2> g(x0, x1, y0, y1, nx, ny, t0, t1, nt);

    ASSERT_EQ(g.x0, x0);
    ASSERT_EQ(g.x1, x1);
    ASSERT_EQ(g.nx, nx);
    ASSERT_EQ(g.y0, y0);
    ASSERT_EQ(g.y1, y1);

}


TEST(GridTest, ContructorTest3D)
{
    int nx = 20;
    int ny = 5;
    int nz = 50;
    int nt = 231;

    double x0 = 0.0;
    double x1 = 1.0;
    double y0 = 51.0;
    double y1 = 10.023;
    double z0 = 231.5;
    double z1 = 23;
    double t1 = 41;
    double t0 = 23;
    double dx = (x1 - x0) / nx;
    double dy = (y1 - y0) / ny;
    double dz = (z1 - z0) / nz;
    double dt = (t1 - t0) / nt;
    Grid::CGrid<3> g(x0, x1, y0, y1, z0, z1, nx, ny, nz, t0, t1, nt);
    ASSERT_EQ(g.x0, x0);
    ASSERT_EQ(g.x1, x1);
    ASSERT_EQ(g.y0, y0);
    ASSERT_EQ(g.y1, y1);
    ASSERT_EQ(g.z0, z0);
    ASSERT_EQ(g.z1, z1);
    ASSERT_EQ(g.t0, t0);
    ASSERT_EQ(g.t1, t1);
    ASSERT_EQ(g.nx, nx);
    ASSERT_EQ(g.ny, ny);
    ASSERT_EQ(g.nz, nz);
    ASSERT_EQ(g.nt, nt);
    ASSERT_EQ(g.dx, dx);
    ASSERT_EQ(g.dy, dy);
    ASSERT_EQ(g.dz, dz);
    ASSERT_EQ(g.dt, dt);


}