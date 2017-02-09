#pragma once

namespace config {

    template<typename T_DIST>
    struct Config1D
    {

        double xmax, xmin;
        double tmax, tmin;
        int gnx;
        T_DIST tf;

        Config1D(double xmax_,
                 double xmin_,
                 double tmax_,
                 double tmin_,
                 int gnx_,
                 T_DIST tf_)
                 : xmax(xmax_),
                   xmin(xmin_),
                   tmax(tmax_),
                   gnx(gnx_),
                   tf(tf_) {};
    };

}
