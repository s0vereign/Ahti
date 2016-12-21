#pragma once


#include <stdlib.h>


struct Localgrid1D
{
	int nx;
	int xmin, xmax;
	const int dim = 1;
};


struct Localgrid2D
{
	int nx, ny;
	int xmax, xmin;
	int ymax, ymin;
	const int dim = 2; 
};


struct Localgrid3D
{
	int nx, ny, nz;
	int xmax, xmin;
	int ymax, ymin;
	int zmax, zmin;
	const int dim = 3;
};


Localgrid1D* create_Localgrid1D(int nx_,
								int xmax_, int xmin_)
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


