#include "../include/grid/Grid.hpp"

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
    Grid::Grid<2> g(x0, x1, nx, y0, y1, ny, t0, t1, nt);

    ASSERT_EQ(g.x0, x0);
    ASSERT_EQ(g.x1, x1);
    ASSERT_EQ(g.nx, nx);
    ASSERT_EQ(g.y0, y0);
    ASSERT_EQ(g.y1, y1);

}
