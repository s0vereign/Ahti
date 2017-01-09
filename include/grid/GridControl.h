#ifndef GRIDCONTROL_H
#define GRIDCONTROL_H

#include "Localgrid.h"

// The master threat distributes parameters 
// to the corresponding workers
void control_sim_init(const Sim1D& params, 
					  const int mpi_size,
					  const int mpi_id)
{
	const double dx = (params.xmax - params.xmin)/params.nx;
	const double xmax = params.xmax;
	const double xmin = params.xmin;
	const double nx = params.nx;
	const double nxloc = params.nx / mpi_size;
	
	const double wsize = (xmax - xmin)/ mpi_size;
	
	
	
	for(int i = 1; i < mpi_size; i++)
	{
		Localgrid1D lg = create_Localgrid1D();
	}
}


void control_sim_init(const Sim2D& params,
					  const int mpi_size,
					  const int mpi_id)
{
	
}

void control_sim_init(const Sim3D& params,
					  const int mpi_size,
					  const int mpi_id)
{
	
}
#endif 
