#pragma once

#include <stdlib.h>
#include <math.h>
#include "Localgrid.h"

namespace Grid{


	// The master threat distributes parameters
	// to the corresponding workers
	void control_sim_init(const Sim1D* params,
					  const int mpi_size,
					  const int mpi_id,
					  MPI_Datatype* LGrid1D,
					  Localgrid1D* mas_LGrid
					 )
{

	int ppw = 0;
	const int nx = params->nx;
	Localgrid1D* send;

	if( nx % mpi_size != 0)
	{
	  // Define number of full workers
	  int nworker = mpi_size - 1;

	  ppw = (nx - nx%nworker)/nworker;
	  int nxr = nx % nworker;

	  printf("ppw = %i, nxr = %i \n", ppw, nxr);
	  mas_LGrid->nx = ppw;
	  mas_LGrid->xmax = ppw-1;
	  mas_LGrid->xmin = 0;


	  for(int i = 1; i < nworker; i++)
		{

			send = create_Localgrid1D(ppw, i*ppw+ppw-1, i*ppw);
			MPI_Send(send, 1, *LGrid1D, i, 0, MPI_COMM_WORLD);
			destroy_Localgrid1D(send);

		}

	  if(nxr == 0)
	  {
		// Create a dead worker!
			send = create_Localgrid1D(-1,-1,-1);
	  }

	  else
	  {
	  	send = create_Localgrid1D(nxr, nx-1, nx-nxr);
	  }

	  MPI_Send(send, 1, *LGrid1D, mpi_size-1, 0, MPI_COMM_WORLD);
	  destroy_Localgrid1D(send);

	}

	else
	{

		ppw = params->nx/mpi_size;
	  mas_LGrid->nx = ppw;
	  mas_LGrid->xmax = ppw-1;
	  mas_LGrid->xmin = 0;

		for(int i = 1; i < mpi_size; ++i)
		{
			send = create_Localgrid1D(ppw, i*ppw+ppw-1, i*ppw);
			MPI_Send(send, 1, *LGrid1D, i, 0, MPI_COMM_WORLD);
			destroy_Localgrid1D(send);
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
} // Namespace Grid
