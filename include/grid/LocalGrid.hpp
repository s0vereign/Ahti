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

    template<>
    struct LocalGrid<2>
    {
        double x0, x1;
        int nx0, nx1;
        double dx;

        double y0, y1;
        int ny0, ny1;
        double dy;

        LocalGrid(double x0_, double x1_, int nx0_, int nx1_,
                  double y0_, double y1_, int ny0_, int ny1_)
            :
            x0(x0_), x1(x1_), nx0(nx0_), nx1(nx1_),
            y0(y0_), y1(y1_), ny0(ny0_), ny1(ny1_)
        {
            dx = (x1 - x0) / (nx1 - nx0);
            dy = (y1 - y0) / (ny1 - ny0);
        }
    };
}
