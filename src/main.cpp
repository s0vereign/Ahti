#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// Alpaka for Kernel Acceleration
#include <alpaka/alpaka.hpp>

// MPI
#include <mpi.h>

// Include Gridinformation
#include "grid/SimConf.h"
#include "grid/GridControl.h"
#include "grid/Globalgrid.h"
#include "grid/Localgrid.h"

int
main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	
	int size;
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Datatype LGrid1D;
	commit_Localgrid1D(&LGrid1D);
	
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank == 0)
	{
	  
	  Localgrid1D* l = create_Localgrid1D(10, 0.0, 2.0);
	  MPI_Send(l, 1, LGrid1D, 15, 1, MPI_COMM_WORLD);
	  printf("Localgrid1D sent! \n");
	  destroy_Localgrid1D(l);
	}
	
	if(rank == 15)
	{
		
		Localgrid1D* l = create_Localgrid1D(0, 0.0, 0.0);
		MPI_Status status;
		int src = 0;
		MPI_Recv(l, 1, LGrid1D, 0, 1, MPI_COMM_WORLD,&status);
		printf("Localgrid revcieved!\n");
		printf("nx = %i, xmax = %f, xmin = %f \n", l->nx, l->xmax, l->xmin);
		destroy_Localgrid1D(l);
	}
	
	MPI_Finalize();
	
	return EXIT_SUCCESS;
}
