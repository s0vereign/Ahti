#ifndef GRIDCONTROL_H
#define GRIDCONTROL_H

#include <stdlib.h>
#include <math.h>
#include "Localgrid.h"

// The master threat distributes parameters 
// to the corresponding workers
void control_sim_init(const Sim1D* params, 
					  const int mpi_size,
					  const int mpi_id,
					  MPI_Datatype* LGrid1D
					 )
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
		for(int i = 0; i < nworker-1; i++)
		{
			Localgrid1D* l = create_Localgrid1D(ppw,
												xmin + (i+1) * (ppw-1) * dx,
												xmin + i * ppw * dx);
			MPI_Send(l, 1, *LGrid, i+1, 1, MPI_COMM_WORLD);
			free(l);
		}
		Localgrid1D* l = create_Localgrid1D(ppw,
											xmin + nworker * ppw * dx,
											xmin + (nworker-1) * ppw * dx);
		MPI_Send(l, 1, *LGrid1D, nworker+1, 1, MPI_COMM_WORLD);
		free(l);		
	}
	else
	{
		// Use one worker less as the "modulo worker"
		nworker--;
		
		// Compute the number of Gridpoints for each worker
		ppw = nx / nworker;
		rp = nx % nworker;
		
		// Distribute the local grids to all workers
		
		for(int i = 0; i < nworker; i++)
		{
			
			Localgrid1D* l = create_Localgrid1D(ppw,
												xmin + dx * i * ppw + dx * (ppw - 1),
												xmin + dx * i * ppw);
			MPI_Send(l, 1, *LGrid1D, i+1, 1, MPI_COMM_WORLD);	
			free(l);
		
		}
		
		Localgrid1D* l = create_Localgrid1D(rp,
											xmin + dx * nworker * ppw + dx * rp,
											xmin + dx * nworker * ppw
											);		
		MPI_Send(l, 1, *LGrid1D, nworker+1, 1, MPI_COMM_WORLD);
		free(l);
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
