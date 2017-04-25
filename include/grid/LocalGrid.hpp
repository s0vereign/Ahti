#pragma once

namespace Grid
{
    template<int d>
    struct LocalGrid
    {
        
    };
    
    template<>
    struct LocalGrid<1>
    {
        double x0, x1;
        double dx;
        int nx0, nx1;
        LocalGrid(double x0_, double x1_, int nx0_, int nx1_): x0(x0_), x1(x1_), nx0(nx0_), nx1(nx1_)
        {
            dx = (x1-x0)/(nx1-nx0);
        }
      
    };
}
