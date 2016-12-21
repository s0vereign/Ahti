#pragma once

#include <stdlib.h>

struct Globalgrid1D
{	
	const int dim = 1;
	int nx;
};


struct Globalgrid2D
{
	const int dim = 2;
	int nx,ny;
};


struct Globalgrid3D
{
	const int dim = 3;
	int nx,ny,nz;
};


Globalgrid1D* make_Globalgid1D(int nx_)
{
	Globalgrid1D* g = (Globalgrid1D*) malloc(sizeof(Globalgrid1D));
	g->nx = nx_;
	return g;
}


Globalgrid2D* make_Globalgid2D(int nx_, int ny_)
{
	Globalgrid2D* g = (Globalgrid2D*) malloc(sizeof(Globalgrid2D));
	g->nx = nx_;
	g->ny = ny_;
	return g;
}


Globalgrid3D* make_Globalgrid3D(int nx_, int ny_, int nz_)
{
	Globalgrid3D* g = (Globalgrid3D*) malloc(sizeof(Globalgrid3D));
	g->nx = nx_;
	g->ny = ny_;
	g->nz = nz_;
	return g;
}


void destroy_Globalgrid1D(Globalgrid1D* g)
{
	free(g);
}


void destroy_Globalgrid2D(Globalgrid2D* g)
{
	free(g);
}


void destroy_Globalgrid3D(Globalgrid3D* g)
{
	free(g);
}



