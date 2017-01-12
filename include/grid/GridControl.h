#ifndef GRIDCONTROL_H
#define GRIDCONTROL_H

#include <stdlib.h>
#include <math.h>
#include "Localgrid.h"

// The master threat distributes parameters 
// to the corresponding workers
void control_sim_init(const Sim1D* params, 
					  const int mpi_size,
					  const int mpi_id)
{
	
	// For convenience copy params in local variables
	const int nx = params->nx;
	const double xmax = params->xmax;
	const double xmin = params->xmin;
	
	const double dx = xmax - xmin;
	
	// Master Thread is not a worker
	int nworker = mpi_size - 1;
	
	// Points per worker
	int ppw = 0;
	
	// rest points if unevenly distributed intervalls occur
	int rp = 0;
	
	// Check the given grid parameters
	double grid_check;
	
	if(nx % nworker == 0)
	{
		ppw = nx / nworker;
		
	}
	else
	{
		// Use one worker less as the "modulo worker"
		nworker--;
		
		// Compute the number of Gridpoints for each worker
		ppw = nx / nworker;
		rp = nx % nworker;
		
		// Distribute the local grids to all workers
		// 
		for(int i = 0; i < nworker; i++)
		{
			Localgrid1D* l = create_Localgrid1D(ppw,
												dx * i * ppw,
												dx * i * ppw + dx * (ppw - 1));
			
			
		}
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
