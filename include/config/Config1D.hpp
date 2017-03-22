#pragma once

namespace config {

    template<typename T_DIST>
    struct Config1D
    {

        double xmax, xmin;
        double tmax, tmin;
        int gnx;
        int nt;
        T_DIST tf;

        Config1D(double xmax_,
                 double xmin_,
                 double tmax_,
                 double tmin_,
                 int gnx_,
                 int nt_,
                 T_DIST tf_)
                 : xmax(xmax_),
                   xmin(xmin_),
                   tmax(tmax_),
                   gnx(gnx_),
                   tf(tf_),
                   nt(nt_) {};
    };

    template<typename T_CONF> 
    double get_dx(T_CONF c)
    {
        return (c.xmax - c.xmin)/c.gnx;
    }

    template<typename T_CONF>
    double get_l(T_CONF c)
    {
        return (c.xmax - c.xmin);
    }

    template<typename T_CONF>
    double get_dt(T_CONF c)
    {
        return (c.tmax - c.tmin)/c.nt;
    }
} // config
