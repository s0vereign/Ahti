#pragma once 


namespace {

typedef struct Simconf1
{

	int nx;
	int xmax, xmin;

} Sim1D;

Sim1D* create_Sim1D(int nx_, int xmax_, int xmin_)
{
	Sim1D* s = (Sim1D*) malloc(sizeof(Sim1D));
	s->nx = nx_;
	s->xmax = xmax_;
	s->xmin = xmin_;
	return s;
}

void destroy_Sim1D(Sim1D* s)
{
	free(s);
}

typedef struct Simconf2
{
	int nx, ny;
	int xmax, xmin, ymax, ymin;
} Sim2D;


Sim2D* create_Sim2D(int nx_, int ny_,
					int xmax_, int xmin_,
					int ymax_, int ymin_)
{
	Sim2D* s = (Sim2D*) malloc(sizeof(Sim2D));
	s->nx = nx_;
	s->ny = ny_;
	s->xmax = xmax_;
	s->xmin = xmin_;
	s->ymax = ymax_;
	s->ymin = ymin_;
	return s;
}


void destroy_Sim2D(Sim2D* s)
{
	free(s);
}


typedef struct Simconf3
{
	int nx, ny, nz;
	int xmax, xmin,
		   ymax, ymin,
		   zmax, zmin;
} Sim3D;


Sim3D* create_Sim3D(int nx_,int ny_,int nz_,
					int xmax_, int xmin_,
					int ymax_, int ymin_,
					int zmax_, int zmin_)
{
	Sim3D* s = (Sim3D*) malloc(sizeof(Sim3D));
	s->nx = nx_;
	s->ny = ny_;
	s->xmax = xmax_;
	s->xmin = xmin_;
	s->ymax = ymax_;
	s->ymin = ymin_;
	s->zmax = zmax_;
	s->zmin = zmin_;

	return s;
}

}
