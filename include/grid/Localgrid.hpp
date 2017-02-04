#pragma once

#include <stdlib.h>

namespace Grid {

    typedef struct Localgrid1D
    {
        int nx;
        int xmin, xmax;
        const int dim = 1;
    } Localgrid1D;


    typedef struct Localgrid2D
    {

        int nx, ny;
        int xmax, xmin;
        int ymax, ymin;
        const int dim = 2;
    
    } Localgrid2D;


    typedef struct Localgrid3D
    {
        int nx, ny, nz;
        int xmax, xmin;
        int ymax, ymin;
        int zmax, zmin;
        const int dim = 3;
    } Localgrid3D;


    void commit_Localgrid1D(MPI_Datatype* mpi_lg_type)
    {
        const int nitems = 4;
        int blength[4] = {1, 1, 1, 1};
        MPI_Datatype types[4]={
                            MPI_INT,
                            MPI_DOUBLE,
                            MPI_DOUBLE,
                            MPI_INT
                            };
        MPI_Aint offsets[4];
        offsets[0] = offsetof(Localgrid1D, nx);
        offsets[1] = offsetof(Localgrid1D, xmin);
        offsets[2] = offsetof(Localgrid1D, xmax);
        offsets[3] = offsetof(Localgrid1D, dim);
        MPI_Type_create_struct(nitems,blength, offsets, types, mpi_lg_type);
        MPI_Type_commit(mpi_lg_type);

}

Localgrid1D* create_Localgrid1D(int nx_,
								int xmax_,
								int xmin_)
{
	Localgrid1D* l = (Localgrid1D*) malloc(sizeof(Localgrid1D));
	l->nx = nx_;
	l->xmax = xmax_;
	l->xmin = xmin_;
	return l;
};


Localgrid2D* create_Localgrid2D(int nx_, int ny_,
							    int xmax_, int xmin_,
							    int ymax_, int ymin_)
{
	Localgrid2D* l = (Localgrid2D*) malloc(sizeof(Localgrid2D));
	l->nx = nx_;
	l->ny = ny_;
	l->xmax = xmax_;
	l->xmin = xmin_;
	l->ymax = ymax_;
	l->ymin = ymin_;
	return l;
};


Localgrid3D* create_Localgrid3D(int nx_, int ny_, int nz_,
								int xmax_, int xmin_,
								int ymax_, int ymin_,
								int zmax_, int zmin_)
{
	Localgrid3D* l = (Localgrid3D*) malloc(sizeof(Localgrid3D));
	l->nx = nx_;
	l->ny = ny_;
	l->nz = nz_;
	l->xmax = xmax_;
	l->xmin = xmin_;
	l->ymax = ymax_;
	l->ymin = ymin_;
	l->zmax = zmax_;
	l->zmin = zmin_;
	return l;

};


void destroy_Localgrid1D(Localgrid1D* l)
{
	free(l);
}


void destroy_Localgrid2D(Localgrid2D* l)
{
	free(l);
}


void destroy_Localgrid3D(Localgrid3D* l)
{
	free(l);
}

}
