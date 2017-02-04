#pragma once

#include <array>
#include <stdlib.h>

namespace TimeConf {

    struct TimeConf
    {
        double tmax, tmin;
        size_t nt;

        TimeConf(double tmax_, double tmin_, size_t nt_)
                 : tmax(tmax_), tmin(tmin_), nt(nt_) {}; 
    };

    void commit_TimeConf(MPI_Datatype* time_type)
    {

        int nitems = 3;
        int blength[3] =  {1,1,1};

        MPI_Datatype types[4]={
                                MPI_DOUBLE,
                                MPI_DOUBLE,
                                MPI_INT
                              } ;
        MPI_Aint offsets[3];
        offsets[0] = offsetof(TimeConf, tmax);
        offsets[1] = offsetof(TimeConf, tmin);
        offsets[2] = offsetof(TimeConf, nt);

        MPI_Type_create_struct(nitems , blength, offsets, types, time_type);
        MPI_Type_commit(time_type);

    }
}