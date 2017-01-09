#ifndef SIMCONF_H
#define SIMCONF_H


template<typename T_PREC, int Sdim>
struct Simconf 
{
	size_t dim = Sdim;
	
	T_PREC xmin, xmax;
	T_PREC ymin, ymax;
	T_PREC zmin, zmax;
	
	size_t nx;
	size_t ny;
	size_t nz;

};

typedef struct Simconf<double, 1> Sim1D;
typedef struct Simconf<double, 2> Sim2D;
typedef struct Simconf<double, 3> Sim3D;
#endif
